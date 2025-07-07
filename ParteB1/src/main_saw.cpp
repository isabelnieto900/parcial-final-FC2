// main_saw.cpp
// Programa principal para la simulación de Caminata Aleatoria Autoevitante (SAW)
#include "SAWSimulador.h" // Se espera que el Makefile configure la ruta de inclusión
#include <iostream>
#include <vector>
#include <string>
#include <fstream>   // Para std::ofstream
#include <chrono>    // Para medir el tiempo
#include <iomanip>   // Para std::setprecision
#include <numeric>   // Para std::accumulate
#include <cmath>     // Para std::sqrt

int main(int argc, char *argv[]) {
    // Parámetros por defecto
    int N_max_pasos = 50;       // Longitud objetivo de las caminatas
    int num_simulaciones = 10000; // Número de caminatas a generar para estadísticas
    unsigned int semilla = std::random_device{}(); // Semilla aleatoria por defecto

    if (argc > 1) N_max_pasos = std::stoi(argv[1]);
    if (argc > 2) num_simulaciones = std::stoi(argv[2]);
    if (argc > 3) semilla = std::stoul(argv[3]);

    std::cout << "Iniciando simulación de Caminata Aleatoria Autoevitante (SAW)..." << std::endl;
    std::cout << "  Longitud objetivo por caminata (N_max_pasos): " << N_max_pasos << std::endl;
    std::cout << "  Número de simulaciones: " << num_simulaciones << std::endl;
    std::cout << "  Semilla aleatoria: " << semilla << std::endl;

    SAWSimulador simulador_saw(N_max_pasos, semilla);

    std::vector<double> R2_exitosas; // Almacena R^2 para caminatas que alcanzaron N_max_pasos
    std::vector<int> longitudes_reales; // Almacena la longitud real de todas las caminatas

    std::string resultados_fname = "ParteB1/results/saw_resultados_N" + std::to_string(N_max_pasos) + "_sim" + std::to_string(num_simulaciones) + ".dat";
    std::ofstream archivo_resultados_saw(resultados_fname);

    if (!archivo_resultados_saw.is_open()) {
        std::cerr << "Error: No se pudo abrir " << resultados_fname << std::endl;
        return 1;
    }
    archivo_resultados_saw << "# N_objetivo Longitud_Real R2 Exito(1_o_0)" << std::endl;
    archivo_resultados_saw << std::fixed << std::setprecision(4);

    auto t_inicio = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < num_simulaciones; ++i) {
        bool exito = simulador_saw.SimularUnaCaminata();
        int longitud_actual = simulador_saw.GetLongitudRealCamino();
        double r2_actual = simulador_saw.GetDistanciaExtremoAExtremoCuadrada();

        archivo_resultados_saw << N_max_pasos << " "
                               << longitud_actual << " "
                               << r2_actual << " "
                               << (exito ? 1 : 0) << std::endl;

        longitudes_reales.push_back(longitud_actual);
        if (exito) {
            R2_exitosas.push_back(r2_actual);
        }

        if (i == 0) { // Guardar la primera caminata como ejemplo
            std::string camino_fname = "ParteB1/results/saw_camino_ejemplo_N" + std::to_string(N_max_pasos) + ".dat";
            simulador_saw.GuardarCamino(camino_fname);
            std::cout << "  Camino de ejemplo guardado en: " << camino_fname << std::endl;
        }
        if ((i + 1) % (num_simulaciones / 10 == 0 ? 1 : num_simulaciones/10) == 0) { // Imprimir progreso
             std::cout << "  Progreso: " << (i + 1) * 100 / num_simulaciones << "% completado." << std::endl;
        }
    }

    auto t_fin = std::chrono::high_resolution_clock::now();
    auto duracion_ms = std::chrono::duration_cast<std::chrono::milliseconds>(t_fin - t_inicio);

    archivo_resultados_saw.close();

    // Calcular estadísticas
    double promedio_longitud = 0;
    if (!longitudes_reales.empty()) {
        promedio_longitud = static_cast<double>(std::accumulate(longitudes_reales.begin(), longitudes_reales.end(), 0LL)) / longitudes_reales.size();
    }

    double promedio_R2 = 0;
    double std_dev_R2 = 0;
    if (!R2_exitosas.empty()) {
        promedio_R2 = std::accumulate(R2_exitosas.begin(), R2_exitosas.end(), 0.0) / R2_exitosas.size();
        double suma_cuadrados_R2_diff = 0.0;
        for (double r2_val : R2_exitosas) {
            suma_cuadrados_R2_diff += (r2_val - promedio_R2) * (r2_val - promedio_R2);
        }
        if (R2_exitosas.size() > 1) {
            std_dev_R2 = std::sqrt(suma_cuadrados_R2_diff / (R2_exitosas.size() - 1));
        }
    }
    double fraccion_exitosas = static_cast<double>(R2_exitosas.size()) / num_simulaciones;

    std::cout << "\n--- Resultados Finales de la Simulación SAW ---" << std::endl;
    std::cout << "Tiempo total de CPU: " << duracion_ms.count() << " ms" << std::endl;
    std::cout << "Fracción de caminatas exitosas (alcanzaron N_max_pasos): " << fraccion_exitosas * 100.0 << "% (" << R2_exitosas.size() << "/" << num_simulaciones << ")" << std::endl;
    std::cout << "Promedio de longitud real de camino (todas las caminatas): " << promedio_longitud << std::endl;
    if (!R2_exitosas.empty()) {
        std::cout << "Promedio de R^2 para caminatas exitosas: " << promedio_R2 << std::endl;
        std::cout << "Desviación estándar de R^2 para caminatas exitosas: " << std_dev_R2 << std::endl;
    }
    std::cout << "Datos detallados guardados en: " << resultados_fname << std::endl;

    // Aquí se podría añadir la investigación sobre algoritmos más eficientes
    // y la descripción solicitada en el problema B1.2, como texto en la consola o
    // refiriendo al documento LaTeX.
    std::cout << "\nInvestigación sobre algoritmos más eficientes para SAW:" << std::endl;
    std::cout << "  Un algoritmo más eficiente para generar SAW largas y calcular propiedades es el algoritmo de Rosenbluth y Rosenbluth (Enrichment method) o algoritmos basados en pivotes como el de Madras-Slade. Estos métodos intentan evitar el 'atrapamiento' temprano de las caminatas simples." << std::endl;
    std::cout << "  El algoritmo de Rosenbluth pondera cada caminata generada por el número de opciones disponibles en cada paso, corrigiendo el sesgo de las caminatas más cortas." << std::endl;
    std::cout << "  Los algoritmos de pivote transforman una SAW existente mediante rotaciones o reflexiones de una subcadena alrededor de un 'pivote', aceptando la transformación si no crea intersecciones." << std::endl;
    std::cout << "  Para una descripción detallada, por favor refiérase al documento 'investigacion_aleatorios.tex'." << std::endl;


    return 0;
}
