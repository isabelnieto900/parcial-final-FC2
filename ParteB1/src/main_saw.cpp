// main_saw.cpp
#include "SAWSimulador.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream> // Para std::ofstream
#include <chrono>  // Para medir el tiempo

int main() {
    int N_max_pasos = 50; // Máximo número de pasos para una caminata
    int num_simulaciones = 1000; // Número de caminatas a simular para estadísticas

    std::cout << "Iniciando simulación de Caminata Aleatoria Autoevitante (SAW)..." << std::endl;
    std::cout << "Max pasos por caminata (N): " << N_max_pasos << std::endl;
    std::cout << "Número de simulaciones: " << num_simulaciones << std::endl;

    SAWSimulador simulador_saw(N_max_pasos);

    long long total_pasos_exitosos = 0;
    double suma_R2 = 0.0;
    int caminatas_exitosas = 0; // Caminatas que alcanzaron N_max_pasos

    std::ofstream archivo_resultados_saw("results/saw_resultados.dat");
    if (!archivo_resultados_saw.is_open()) {
        std::cerr << "Error: No se pudo abrir results/saw_resultados.dat" << std::endl;
        return 1;
    }
    archivo_resultados_saw << "# N_pasos_intentados Longitud_Real_Camino R^2 Exito(1_o_0)" << std::endl;

    auto t_inicio = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < num_simulaciones; ++i) {
        bool exito = simulador_saw.SimularUnaCaminata();
        int longitud_actual = simulador_saw.GetLongitudCamino();
        double r2_actual = simulador_saw.GetDistanciaExtremoAExtremoCuadrada();

        archivo_resultados_saw << N_max_pasos << " "
                               << longitud_actual << " "
                               << r2_actual << " "
                               << (exito ? 1 : 0) << std::endl;

        if (exito) {
            caminatas_exitosas++;
            suma_R2 += r2_actual;
        }
        total_pasos_exitosos += longitud_actual; // Suma la longitud real de la caminata (puede ser menor a N_max_pasos si se atascó)

        // Opcional: Guardar una caminata de ejemplo
        if (i == 0) { // Guardar la primera caminata
            simulador_saw.GuardarCamino("results/saw_camino_ejemplo.dat");
        }
    }

    auto t_fin = std::chrono::high_resolution_clock::now();
    auto duracion_ms = std::chrono::duration_cast<std::chrono::milliseconds>(t_fin - t_inicio);

    archivo_resultados_saw.close();

    std::cout << "\n--- Resultados de la Simulación SAW ---" << std::endl;
    std::cout << "Tiempo total de CPU: " << duracion_ms.count() << " ms" << std::endl;
    std::cout << "Número de caminatas que alcanzaron N_max_pasos: " << caminatas_exitosas << " de " << num_simulaciones << std::endl;
    if (caminatas_exitosas > 0) {
        std::cout << "Promedio de R^2 para caminatas exitosas: " << suma_R2 / caminatas_exitosas << std::endl;
    }
    std::cout << "Promedio de longitud de camino (para todas las caminatas): " << static_cast<double>(total_pasos_exitosos) / num_simulaciones << std::endl;
    std::cout << "Datos guardados en results/saw_resultados.dat" << std::endl;
    std::cout << "Camino de ejemplo guardado en results/saw_camino_ejemplo.dat" << std::endl;

    // Aquí se podría añadir la investigación sobre algoritmos más eficientes
    // y la descripción solicitada en el problema B1.2.

    return 0;
}
