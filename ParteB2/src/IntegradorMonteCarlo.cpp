// IntegradorMonteCarlo.cpp
#include "IntegradorMonteCarlo.h" // Se espera que el Makefile configure la ruta de inclusión
#include <cmath>     // Para std::sqrt, std::pow
#include <numeric>   // Para std::accumulate (útil si se guardaran los f_xi en un vector)
#include <stdexcept> // Para std::runtime_error
#include <iostream>  // Para posibles mensajes de depuración o error

IntegradorMonteCarlo::IntegradorMonteCarlo(FuncionUnivariable func, double a, double b, unsigned int semilla)
    : func_a_integrar(func), limite_inferior(a), limite_superior(b), gen(semilla), distribucion_uniforme(a, b) {
    if (a >= b) {
        // Lanzar una excepción o manejar el error de alguna manera
        throw std::runtime_error("Error en IntegradorMonteCarlo: El límite inferior 'a' debe ser estrictamente menor que el límite superior 'b'.");
    }
}

double IntegradorMonteCarlo::CalcularIntegralSimple(long long numero_muestras, double& error_estimado) {
    if (numero_muestras <= 0) {
        error_estimado = 0.0; // O un valor indicativo de error como NaN o infinito
        // std::cerr << "Advertencia: numero_muestras debe ser positivo." << std::endl;
        return 0.0; // O NaN
    }

    double suma_f = 0.0;
    double suma_f_cuadrado = 0.0;

    for (long long i = 0; i < numero_muestras; ++i) {
        double x_aleatorio = distribucion_uniforme(gen); // Genera x_i uniformemente en [a, b)
        double valor_f_xi = func_a_integrar(x_aleatorio);
        suma_f += valor_f_xi;
        suma_f_cuadrado += valor_f_xi * valor_f_xi;
    }

    // Estimación de la integral I = (b-a) * <f>
    // donde <f> es el promedio de f(x_i)
    double promedio_f = suma_f / static_cast<double>(numero_muestras);
    double valor_integral = (limite_superior - limite_inferior) * promedio_f;

    // Estimación del error (error estándar de la media de la integral)
    // Error = (b-a) * sqrt( ( <f^2> - <f>^2 ) / N )
    //       = (b-a) * sigma_f / sqrt(N)
    if (numero_muestras > 1) {
        double promedio_f_cuadrado = suma_f_cuadrado / static_cast<double>(numero_muestras);
        double varianza_f = promedio_f_cuadrado - (promedio_f * promedio_f);

        // La varianza no puede ser negativa, esto puede ocurrir por errores de precisión numérica.
        if (varianza_f < 0) {
            varianza_f = 0.0;
        }
        error_estimado = (limite_superior - limite_inferior) * std::sqrt(varianza_f / static_cast<double>(numero_muestras));
    } else {
        // No se puede estimar la varianza (y por lo tanto el error) con una sola muestra.
        // Se podría devolver NaN o un valor grande para indicar esto.
        error_estimado = 0.0; // O std::numeric_limits<double>::quiet_NaN(); si se incluye <limits>
    }

    return valor_integral;
}
