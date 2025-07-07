// main_montecarlo_integral.cpp
#include "IntegradorMonteCarlo.h" // Asumiendo que está en ../include/ o que el Makefile maneja la ruta
#include <iostream>
#include <vector>
#include <cmath>     // Para std::exp, std::pow
#include <fstream>   // Para std::ofstream
#include <iomanip>   // Para std::setprecision
#include <string>    // Para std::string

// Función a integrar: e^(-x^2)
double funcion_exp_neg_x_cuadrado(double x) {
    return std::exp(-x * x);
}

int main() {
    double limite_inferior = 0.0;
    double limite_superior = 1.0;

    std::cout << "Iniciando cálculo de la integral de e^(-x^2) de "
              << limite_inferior << " a " << limite_superior
              << " usando Monte Carlo..." << std::endl;

    // Usar una semilla fija para reproducibilidad durante el desarrollo,
    // luego se puede cambiar a std::random_device{}() para corridas diferentes.
    int semilla = 12345;
    IntegradorMonteCarlo integrador(funcion_exp_neg_x_cuadrado, limite_inferior, limite_superior, semilla);

    // Crear el directorio results si no existe (una forma simple, puede requerir C++17 o ser manejado por Makefile)
    // Para este entorno, asumiremos que el directorio 'results' dentro de 'ParteB2' ya existe o se crea manualmente/Makefile.
    std::string nombre_archivo_salida = "ParteB2/results/integral_error.dat";
    std::ofstream archivo_resultados(nombre_archivo_salida);

    if (!archivo_resultados.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo de salida: " << nombre_archivo_salida << std::endl;
        // Intentar crear en la raíz si falla en el subdirectorio (para pruebas locales si la estructura aún no está completa)
        nombre_archivo_salida = "integral_error.dat";
        archivo_resultados.open(nombre_archivo_salida);
        if(!archivo_resultados.is_open()){
            std::cerr << "Error: No se pudo abrir el archivo de salida en la raíz tampoco: " << nombre_archivo_salida << std::endl;
            return 1;
        }
        std::cout << "Advertencia: Guardando " << nombre_archivo_salida << " en el directorio actual en lugar de ParteB2/results/" << std::endl;
    }

    archivo_resultados << "# N_muestras Valor_Integral Error_Estimado" << std::endl;

    std::cout << std::fixed << std::setprecision(8);
    archivo_resultados << std::fixed << std::setprecision(8);

    std::vector<long long> lista_n_muestras;
    for (int i = 1; i <= 7; ++i) { // Desde 10^1 hasta 10^7
        lista_n_muestras.push_back(static_cast<long long>(std::pow(10, i)));
    }

    for (long long n_muestras : lista_n_muestras) {
        double error = 0.0;
        double valor_integral = integrador.CalcularIntegralSimple(n_muestras, error);

        std::cout << "N = " << n_muestras
                  << ", Integral = " << valor_integral
                  << ", Error Est. = " << error << std::endl;

        archivo_resultados << n_muestras << " "
                           << valor_integral << " "
                           << error << std::endl;
    }

    archivo_resultados.close();
    std::cout << "\nResultados de la convergencia guardados en " << nombre_archivo_salida << std::endl;

    // Valor de referencia (aproximado) para erf(1) * sqrt(pi)/2
    // erf(1) ~= 0.8427007929497149
    // sqrt(pi)/2 ~= 0.886226925452758
    // Integral de 0 a 1 de e^(-x^2) dx = (sqrt(pi)/2) * erf(1) ~= 0.7468241328124271
    std::cout << "Valor de referencia (Analítico/Tabla) para la integral: ~0.74682413" << std::endl;

    std::cout << "\n--- Fin del Problema B2.4 ---" << std::endl;
    std::cout << "La sección de 'Investigación Final: Método de Monte Carlo y Física Estadística'" << std::endl;
    std::cout << "en el informe se centrará en los conceptos generales y esta aplicación específica." << std::endl;

    return 0;
}
