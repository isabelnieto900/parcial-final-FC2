// main_browniano.cpp
#include <iostream>
#include "SimuladorBrowniano.h"
#include "ParticulaBrowniana.h"
#include "Vector3D.h" // Asegurarse de que esté disponible si ParticulaBrowniana lo usa directamente en su interfaz pública

int main() {
    // Parámetros de la simulación (ejemplos, ajustar según sea necesario)
    double x0 = 0.0, y0 = 0.0, z0 = 0.0; // Posición inicial
    double vx0 = 0.0, vy0 = 0.0, vz0 = 0.0; // Velocidad inicial
    double masa = 1.0e-15; // kg (ej: partícula de polen)
    double radio_particula = 1.0e-6; // m (ej: 1 micrómetro)
    double temperatura_kelvin = 300.0; // K (temperatura ambiente)

    // Viscosidad del medio (ej: agua a 300K)
    // Para agua a 27C (300K) eta ~ 0.85 mPa.s = 0.85e-3 Pa.s
    double viscosidad_medio = 0.85e-3; // Pa*s

    // Coeficiente de fricción (Stokes' law: gamma = 6 * pi * eta * R)
    double gamma = 6 * M_PI * viscosidad_medio * radio_particula;

    double dt = 0.001; // s (paso de tiempo)
    double tiempo_total = 10.0; // s (tiempo total de simulación)
    int pasos_entre_guardado = 10; // Guardar datos cada N pasos

    // Crear la partícula
    ParticulaBrowniana particula;
    particula.Inicie(x0, y0, z0, vx0, vy0, vz0, masa, gamma, temperatura_kelvin);

    // Crear el simulador
    SimuladorBrowniano simulador;
    simulador.Inicializar(dt, "results/browniano.dat"); // El archivo se guardará en la carpeta results
    simulador.AgregarParticula(particula);

    // Ejecutar la simulación
    std::cout << "Iniciando simulación de Movimiento Browniano..." << std::endl;
    std::cout << "Parámetros:" << std::endl;
    std::cout << "  Masa: " << masa << " kg" << std::endl;
    std::cout << "  Radio Partícula: " << radio_particula << " m" << std::endl;
    std::cout << "  Temperatura: " << temperatura_kelvin << " K" << std::endl;
    std::cout << "  Viscosidad Medio: " << viscosidad_medio << " Pa.s" << std::endl;
    std::cout << "  Gamma (calculado): " << gamma << std::endl;
    std::cout << "  dt: " << dt << " s" << std::endl;
    std::cout << "  Tiempo Total: " << tiempo_total << " s" << std::endl;
    std::cout << "  Guardando datos en: results/browniano.dat" << std::endl;

    simulador.Simular(tiempo_total, pasos_entre_guardado);

    std::cout << "Simulación completada." << std::endl;

    return 0;
}
