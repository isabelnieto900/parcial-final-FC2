// main_montecarlo_integral.cpp
// Programa principal para la Parte B2: Integración de e^(-x^2) por Monte Carlo
#include "IntegradorMonteCarlo.h" // Se espera que el Makefile configure la ruta
#include <iostream>
#include <vector>
#include <cmath>     // Para std::exp, std::pow, M_PI (puede necesitar -D_USE_MATH_DEFINES en Windows)
#include <fstream>   // Para std::ofstream
#include <iomanip>   // Para std::setprecision
#include <string>    // Para std::string
#include <numeric>   // Para std::accumulate (si se necesita para algo más)
#include <algorithm> // Para std::sort (si se usa para ordenar lista_n_muestras)

// Definir M_PI si no está disponible (común en MSVC sin _USE_MATH_DEFINES)
#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

// Función a integrar: f(x) = e^(-x^2)
double funcion_a_integrar_exp_neg_x_cuadrado(double x) {
    return std::exp(-x * x);
}

int main(int argc, char *argv[]) {
    double limite_inferior = 0.0;
    double limite_superior = 1.0;
    unsigned int semilla = std::random_device{}(); // Semilla aleatoria por defecto

    // Permitir cambiar la semilla desde la línea de comandos (opcional)
    if (argc > 1) {
        try {
            semilla = std::stoul(argv[1]);
        } catch (const std::exception& e) {
            std::cerr << "Advertencia: No se pudo parsear la semilla '" << argv[1] << "'. Usando semilla aleatoria por defecto." << std::endl;
        }
    }

    std::cout << "Problema B2.4: Cálculo de la integral de e^(-x^2) de "
              << limite_inferior << " a " << limite_superior
              << " usando Monte Carlo." << std::endl;
    std::cout << "  Usando semilla: " << semilla << std::endl;

    IntegradorMonteCarlo integrador(funcion_a_integrar_exp_neg_x_cuadrado, limite_inferior, limite_superior, semilla);

    std::string nombre_archivo_salida = "ParteB2/results/integral_error_Nmax_1e7.dat";
    std::ofstream archivo_resultados(nombre_archivo_salida);

    if (!archivo_resultados.is_open()) {
        std::cerr << "Error fatal: No se pudo abrir el archivo de salida: " << nombre_archivo_salida << std::endl;
        // Intentar en el directorio actual como fallback para pruebas locales.
        nombre_archivo_salida = "integral_error_Nmax_1e7.dat";
        archivo_resultados.open(nombre_archivo_salida);
        if (!archivo_resultados.is_open()) {
            std::cerr << "Error fatal: No se pudo abrir el archivo de salida en la raíz tampoco: " << nombre_archivo_salida << std::endl;
            return 1;
        }
        std::cout << "Advertencia: Guardando resultados en " << nombre_archivo_salida << " (directorio actual)." << std::endl;
    }

    archivo_resultados << "# N_muestras Valor_Integral_Estimado Error_Estimado Valor_Teorico Diferencia_Absoluta" << std::endl;

    // Configurar precisión para la salida
    std::cout << std::fixed << std::setprecision(8);
    archivo_resultados << std::fixed << std::setprecision(8);

    // Valor de referencia (Analítico/Tabla) para la integral de 0 a 1 de e^(-x^2) dx = (sqrt(pi)/2) * erf(1)
    double valor_teorico = (std::sqrt(M_PI) / 2.0) * std::erf(1.0); // erf() está en <cmath> desde C++17
                                                                  // Si erf no está disponible, usar valor precalculado.
    // double valor_teorico_precalculado = 0.7468241328124271; // Usar si erf(1) no compila

    std::cout << "Valor de referencia (Teórico) para la integral: " << valor_teorico << std::endl << std::endl;
    std::cout << "N_muestras | Valor Estimado | Error Estimado | Diferencia Abs." << std::endl;
    std::cout << "----------------------------------------------------------------" << std::endl;

    std::vector<long long> lista_n_muestras;
    for (int i = 1; i <= 7; ++i) { // Desde 10^1 (10) hasta 10^7 (10,000,000)
        lista_n_muestras.push_back(static_cast<long long>(std::pow(10, i)));
    }
    // Podrían añadirse más puntos para una gráfica más suave si se desea:
    // long long N_actual = 10;
    // while (N_actual <= 10000000) {
    //     lista_n_muestras.push_back(N_actual);
    //     if (N_actual < 100) N_actual += 10;
    //     else if (N_actual < 1000) N_actual += 100;
    //     else if (N_actual < 100000) N_actual += 1000;
    //     else N_actual *= 2; // o N_actual *= 10 para menos puntos
    // }


    for (long long n_muestras : lista_n_muestras) {
        double error_calc = 0.0;
        double valor_integral_calc = integrador.CalcularIntegralSimple(n_muestras, error_calc);
        double diferencia_abs = std::abs(valor_integral_calc - valor_teorico);

        std::cout << std::setw(10) << n_muestras << " | "
                  << std::setw(14) << valor_integral_calc << " | "
                  << std::setw(14) << error_calc << " | "
                  << std::setw(14) << diferencia_abs << std::endl;

        archivo_resultados << n_muestras << " "
                           << valor_integral_calc << " "
                           << error_calc << " "
                           << valor_teorico << " "
                           << diferencia_abs << std::endl;
    }

    archivo_resultados.close();
    std::cout << "\nResultados de la convergencia guardados en: " << nombre_archivo_salida << std::endl;

    std::cout << "\n--- Fin del Problema B2.4 (Integración de e^-x^2) ---" << std::endl;
    std::cout << "El documento 'montecarlo_fisica_estadistica.tex' contendrá la discusión teórica y el análisis de estos resultados." << std::endl;

    return 0;
}
