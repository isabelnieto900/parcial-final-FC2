// main_browniano.cpp
#include <iostream>
#include <string>
#include <cmath> // Para M_PI si no está definido de otra forma, y std::sqrt, std::pow
#include <vector>
#include "SimuladorBrowniano.h" // Espera encontrarlo en ../include/ o a través de las rutas del Makefile
#include "ParticulaBrowniana.h"
#include "Vector3D.h"

// Definir M_PI si no está disponible (común en MSVC)
#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

const double KB = 1.380649e-23; // Constante de Boltzmann J/K

int main(int argc, char *argv[]) {
    // Parámetros por defecto
    double x0 = 0.0, y0 = 0.0, z0 = 0.0;
    double vx0 = 0.0, vy0 = 0.0, vz0 = 0.0;
    double masa = 1.0e-15;           // kg (ej: micropartícula)
    double radio_particula = 1.0e-6; // m (1 micrómetro)
    double temperatura_kelvin = 300.0; // K
    double viscosidad_medio = 0.85e-3; // Pa*s (agua a ~300K)

    double dt = 0.001;                 // s (paso de tiempo)
    double tiempo_total = 10.0;        // s (tiempo total de simulación)
    int pasos_entre_guardado = 100;   // Guardar datos cada N pasos
    unsigned int semilla = std::random_device{}(); // Semilla aleatoria por defecto

    // (Opcional) Parsear argumentos de línea de comandos para cambiar parámetros
    // Ejemplo: ./movimiento_browniano <tiempo_total> <dt> <semilla>
    if (argc > 1) tiempo_total = std::stod(argv[1]);
    if (argc > 2) dt = std::stod(argv[2]);
    if (argc > 3) semilla = std::stoul(argv[3]);
    if (argc > 4) temperatura_kelvin = std::stod(argv[4]);
    if (argc > 5) radio_particula = std::stod(argv[5]);
    if (argc > 6) pasos_entre_guardado = std::stoi(argv[6]);


    // Coeficiente de fricción (Ley de Stokes)
    double gamma = 6 * M_PI * viscosidad_medio * radio_particula;

    // Crear la partícula
    ParticulaBrowniana particula;
    particula.Inicie(x0, y0, z0, vx0, vy0, vz0, masa, gamma, temperatura_kelvin, semilla);

    // Crear el simulador
    SimuladorBrowniano simulador;
    // Asegurarse que el directorio ParteA/results existe
    std::string nombre_archivo = "ParteA/results/browniano_T" + std::to_string((int)temperatura_kelvin)
                                + "_r" + std::to_string((int)(radio_particula*1e6)) + "um"
                                + "_seed" + std::to_string(semilla) + ".dat";

    simulador.AgregarParticula(particula); // Agregar antes de inicializar para que la cabecera del archivo sea correcta
    simulador.Inicializar(dt, nombre_archivo);

    std::cout << "Iniciando simulación de Movimiento Browniano..." << std::endl;
    std::cout << "  Parámetros:" << std::endl;
    std::cout << "    Masa: " << masa << " kg" << std::endl;
    std::cout << "    Radio Partícula: " << radio_particula << " m" << std::endl;
    std::cout << "    Temperatura: " << temperatura_kelvin << " K" << std::endl;
    std::cout << "    Viscosidad Medio: " << viscosidad_medio << " Pa.s" << std::endl;
    std::cout << "    Gamma (calculado): " << gamma << std::endl;
    std::cout << "    kB*T: " << KB * temperatura_kelvin << " J" << std::endl;
    std::cout << "    Paso de tiempo (dt): " << dt << " s" << std::endl;
    std::cout << "    Tiempo Total: " << tiempo_total << " s" << std::endl;
    std::cout << "    Pasos entre guardado: " << pasos_entre_guardado << std::endl;
    std::cout << "    Semilla aleatoria: " << semilla << std::endl;
    std::cout << "    Guardando datos en: " << nombre_archivo << std::endl;

    simulador.Simular(tiempo_total, pasos_entre_guardado);

    std::cout << "Simulación completada." << std::endl;

    return 0;
}
