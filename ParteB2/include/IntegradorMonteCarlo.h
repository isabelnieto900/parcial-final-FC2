// IntegradorMonteCarlo.h
#ifndef INTEGRADOR_MONTE_CARLO_H
#define INTEGRADOR_MONTE_CARLO_H

#include <functional> // Para std::function
#include <random>     // Para generadores de números aleatorios
#include <vector>     // Para almacenar resultados si es necesario

class IntegradorMonteCarlo {
public:
    // Typedef para la función a integrar (double -> double)
    using FuncionUnivariable = std::function<double(double)>;

private:
    FuncionUnivariable func_a_integrar;
    double limite_inferior;
    double limite_superior;

    std::mt19937 gen; // Generador Mersenne Twister
    std::uniform_real_distribution<> distribucion_uniforme;

public:
    IntegradorMonteCarlo(FuncionUnivariable func, double a, double b, int seed = std::random_device{}());

    // Método para calcular la integral usando muestreo simple
    // Devuelve el valor estimado de la integral y opcionalmente el error
    double CalcularIntegralSimple(long long numero_muestras, double& error_estimado);

    // Podrían añadirse otros métodos de Monte Carlo (ej. importance sampling) si se requiere
    // double CalcularIntegralImportanceSampling(long long numero_muestras, FuncionUnivariable g, FuncionUnivariable p, double& error_estimado);
};

#endif // INTEGRADOR_MONTE_CARLO_H
