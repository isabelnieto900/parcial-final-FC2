// IntegradorMonteCarlo.h
#ifndef INTEGRADOR_MONTE_CARLO_H
#define INTEGRADOR_MONTE_CARLO_H

#include <functional> // Para std::function
#include <random>     // Para generadores de números aleatorios
#include <string>     // Para std::string (aunque no se usa directamente en la interfaz aquí)

class IntegradorMonteCarlo {
public:
    // Typedef para la función a integrar (debe tomar un double y devolver un double)
    using FuncionUnivariable = std::function<double(double)>;

private:
    FuncionUnivariable func_a_integrar; // La función f(x)
    double limite_inferior;             // Límite inferior de integración 'a'
    double limite_superior;             // Límite superior de integración 'b'

    std::mt19937 gen; // Generador de números aleatorios Mersenne Twister
    std::uniform_real_distribution<> distribucion_uniforme; // Para generar x en [a, b)

public:
    // Constructor
    // func: la función f(x) a integrar.
    // a: límite inferior de integración.
    // b: límite superior de integración.
    // semilla: semilla para el generador de números aleatorios.
    IntegradorMonteCarlo(FuncionUnivariable func, double a, double b, unsigned int semilla = std::random_device{}());

    // Calcula la integral de func_a_integrar desde limite_inferior hasta limite_superior
    // utilizando el método de muestreo simple de Monte Carlo.
    // numero_muestras: el número de puntos aleatorios (N) a generar.
    // error_estimado: referencia a una variable donde se almacenará el error estándar de la media.
    // Devuelve el valor estimado de la integral.
    double CalcularIntegralSimple(long long numero_muestras, double& error_estimado);

    // Podrían añadirse otros métodos de Monte Carlo aquí si fuera necesario,
    // como muestreo por importancia (importance sampling).
};

#endif // INTEGRADOR_MONTE_CARLO_H
