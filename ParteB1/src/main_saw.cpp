// -------------------------------------------------------------------------
// 1. INCLUSIONES DE LIBRERÍAS
// -------------------------------------------------------------------------
#include "SAWSimulador.h" // La clase que hace todo el trabajo.

#include <iostream>     // Para imprimir en la consola (std::cout, std::cerr).
#include <vector>       // Para almacenar los resultados de las simulaciones.
#include <string>       // Para manejar los nombres de archivo.
#include <fstream>      // Para escribir en archivos (std::ofstream).
#include <chrono>       // Para medir el tiempo de ejecución.
#include <iomanip>      // Para formatear la salida (ej. std::setprecision).
#include <numeric>      // Para std::accumulate (sumar elementos de un vector).
#include <cmath>        // Para std::sqrt.
#include <random>       // Para std::random_device, la semilla por defecto.

// -------------------------------------------------------------------------
// 2. FUNCIONES AUXILIARES PARA GUARDAR ARCHIVOS
// -------------------------------------------------------------------------

/**
 * @brief Guarda la trayectoria de una caminata en un archivo para Gnuplot.
 * @param filename El nombre del archivo de salida.
 * @param path El vector de puntos que componen la caminata.
 */
void guardar_camino(const std::string& filename, const std::vector<Point2D>& path) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo para escribir: " << filename << std::endl;
        return;
    }
    // Encabezado para Gnuplot, útil para leyendas y para saber qué contiene el archivo.
    file << "# x y step\n";
    for (size_t i = 0; i < path.size(); ++i) {
        file << path[i].x << " " << path[i].y << " " << i << "\n";
    }
}

/**
 * @brief Guarda los resultados estadísticos y los datos para el histograma.
 * @param filename Nombre del archivo de salida.
 * @param lengths Vector con las longitudes de todas las caminatas.
 * @param successful_R2s Vector con los R^2 de las caminatas exitosas.
 * @param N_max Longitud objetivo de las caminatas.
 * @param num_sims Número total de simulaciones.
 */
void guardar_resultados(const std::string& filename, const std::vector<int>& lengths, const std::vector<double>& successful_R2s, int N_max, int num_sims) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo para escribir: " << filename << std::endl;
        return;
    }

    // --- Calcular estadísticas ---
    // Usamos long long para la suma para evitar desbordamiento con muchas simulaciones.
    long long sum_lengths = std::accumulate(lengths.begin(), lengths.end(), 0LL);
    double avg_length = static_cast<double>(sum_lengths) / lengths.size();
    
    double sum_R2 = std::accumulate(successful_R2s.begin(), successful_R2s.end(), 0.0);
    double avg_R2 = successful_R2s.empty() ? 0.0 : sum_R2 / successful_R2s.size();

    // --- Escribir resumen como comentarios (Gnuplot ignora las líneas con #) ---
    file << "# Resultados de la simulación de Caminata Aleatoria Autoevitante (SAW)\n";
    file << "# N_max_pasos: " << N_max << "\n";
    file << "# num_simulaciones: " << num_sims << "\n";
    file << "# ----------------\n";
    file << "# Longitud promedio de todas las caminatas: " << avg_length << "\n";
    file << "# Numero de caminatas exitosas (longitud == N_max): " << successful_R2s.size() << "\n";
    file << "# R^2 promedio para caminatas exitosas: " << avg_R2 << "\n";
    file << "# ----------------\n";
    file << "# Datos de longitud de cada caminata (para histograma):\n";
    file << "# longitud\n";

    // --- Escribir datos crudos para el histograma ---
    // Una longitud por línea, formato ideal para Gnuplot.
    for (const auto& length : lengths) {
        file << length << "\n";
    }
}

// -------------------------------------------------------------------------
// 3. FUNCIÓN PRINCIPAL (main)
// -------------------------------------------------------------------------
int main(int argc, char *argv[]) {
    // --- Parámetros de la simulación con valores por defecto ---
    int N_max_pasos = 50;
    int num_simulaciones = 10000;
    // Genera una semilla verdaderamente aleatoria si no se especifica una.
    unsigned int semilla = std::random_device{}();

    // --- Lectura de argumentos de la línea de comandos ---
    if (argc > 1) N_max_pasos = std::stoi(argv[1]);
    if (argc > 2) num_simulaciones = std::stoi(argv[2]);
    if (argc > 3) semilla = std::stoul(argv[3]);

    std::cout << "Iniciando simulación SAW...\n";
    std::cout << "  N_max_pasos = " << N_max_pasos << "\n";
    std::cout << "  num_simulaciones = " << num_simulaciones << "\n";
    std::cout << "  semilla = " << semilla << "\n";
    
    // --- Inicialización ---
    SAWSimulador simulator(N_max_pasos, semilla);

    // Vectores para almacenar los resultados de todas las simulaciones.
    std::vector<int> all_lengths;
    all_lengths.reserve(num_simulaciones); // Optimización.
    std::vector<double> successful_R2s;
    
    auto t_start = std::chrono::high_resolution_clock::now();

    // --- Bucle principal de simulación ---
    for (int i = 0; i < num_simulaciones; ++i) {
        bool success = simulator.runWalk();
        
        // Almacenar resultados en memoria.
        all_lengths.push_back(simulator.getPathLength());
        if (success) {
            successful_R2s.push_back(simulator.getEndToEndDistanceSq());
        }
        
        // Imprimir progreso a la consola de forma robusta.
        if (num_simulaciones >= 10 && (i + 1) % (num_simulaciones / 10) == 0) {
            std::cout << "  Progreso: " << (i + 1) * 100 / num_simulaciones << "%\n";
        }
    }
    
    auto t_end = std::chrono::high_resolution_clock::now();
    auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(t_end - t_start);

    // --- Guardado de archivos de resultados (DESPUÉS del bucle) ---
    
    // 1. Guardar un camino de ejemplo (el último generado).
    std::string path_fname = "results/saw_camino_ejemplo_N" + std::to_string(N_max_pasos) + ".dat";
    guardar_camino(path_fname, simulator.getPath());
    std::cout << "Camino de ejemplo guardado en: " << path_fname << std::endl;

    // 2. Guardar los resultados agregados y datos para el histograma.
    std::string results_fname = "results/saw_resultados_N" + std::to_string(N_max_pasos) + "_sim" + std::to_string(num_simulaciones) + ".dat";
    guardar_resultados(results_fname, all_lengths, successful_R2s, N_max_pasos, num_simulaciones);
    std::cout << "Resultados de la simulación guardados en: " << results_fname << std::endl;
    
    // --- Impresión de resumen final en la consola ---
    double success_fraction = successful_R2s.empty() ? 0.0 : static_cast<double>(successful_R2s.size()) / num_simulaciones;

    std::cout << "\n--- Resumen Final ---\n";
    std::cout << "Tiempo total: " << duration_ms.count() << " ms\n";
    std::cout << "Fracción de caminatas exitosas: " << std::fixed << std::setprecision(2) << success_fraction * 100.0 << "% (" << successful_R2s.size() << "/" << num_simulaciones << ")\n";
    if (!successful_R2s.empty()) {
        double avg_R2 = std::accumulate(successful_R2s.begin(), successful_R2s.end(), 0.0) / successful_R2s.size();
        std::cout << "Promedio de R^2 para caminatas exitosas: " << avg_R2 << std::endl;
    }
    std::cout << "Simulación completada.\n";

    return 0; 
}

