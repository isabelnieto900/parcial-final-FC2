// IntegradorMonteCarlo.cpp
#include "IntegradorMonteCarlo.h"
#include <cmath>     // Para std::exp, std::sqrt, std::pow
#include <numeric>   // Para std::accumulate (si se usa para sumas)
#include <stdexcept> // Para std::runtime_error

IntegradorMonteCarlo::IntegradorMonteCarlo(FuncionUnivariable func, double a, double b, int seed)
    : func_a_integrar(func), limite_inferior(a), limite_superior(b), gen(seed), distribucion_uniforme(a, b) {
    if (a >= b) {
        throw std::runtime_error("Límite inferior 'a' debe ser menor que el límite superior 'b'.");
    }
}

double IntegradorMonteCarlo::CalcularIntegralSimple(long long numero_muestras, double& error_estimado) {
    if (numero_muestras <= 0) {
        error_estimado = 0;
        return 0;
    }

    double suma_f = 0.0;
    double suma_f_cuadrado = 0.0;

    for (long long i = 0; i < numero_muestras; ++i) {
        double x_aleatorio = distribucion_uniforme(gen); // Genera x en [a, b)
        double valor_f = func_a_integrar(x_aleatorio);
        suma_f += valor_f;
        suma_f_cuadrado += valor_f * valor_f;
    }

    double promedio_f = suma_f / numero_muestras;
    double promedio_f_cuadrado = suma_f_cuadrado / numero_muestras;

    double valor_integral = (limite_superior - limite_inferior) * promedio_f;

    // Estimación del error: Varianza de f(x) es <f^2> - <f>^2
    // Error de la integral es (b-a) * sqrt(Var(f) / N)
    if (numero_muestras > 1) {
        double varianza_f = promedio_f_cuadrado - (promedio_f * promedio_f);
        // Asegurarse de que la varianza no sea negativa debido a errores de precisión
        if (varianza_f < 0) varianza_f = 0;
        error_estimado = (limite_superior - limite_inferior) * std::sqrt(varianza_f / numero_muestras);
    } else {
        error_estimado = 0; // No se puede estimar el error con una sola muestra
    }

    return valor_integral;
}
