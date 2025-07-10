#include <iostream>
#include <string>
#include <stdexcept>
#include <cmath>
#include "ParticulaBrowniana.h"
#include "SimuladorBrowniano.h"

// Función para mostrar cómo usar el programa
void imprimir_uso(const char* nombre_programa) {
    std::cerr << "Uso: " << nombre_programa << " <tiempo_total> <dt> <semilla> [nombre_archivo_base]" << std::endl;
    std::cerr << "Ejemplo: " << nombre_programa << " 100.0 0.01 12345 browniano_sim" << std::endl;
}

int main(int argc, char* argv[]) {
    // --- 1. Procesar argumentos de la línea de comandos ---
    if (argc < 4 || argc > 5) {
        imprimir_uso(argv[0]);
        return 1;
    }

    double tiempo_total;
    double dt;
    unsigned int semilla;
    std::string nombre_archivo_base = "browniano_sim"; // Valor por defecto

    try {
        tiempo_total = std::stod(argv[1]);
        dt = std::stod(argv[2]);
        semilla = std::stoul(argv[3]);
        if (argc == 5) {
            nombre_archivo_base = argv[4];
        }
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: Argumento inválido. Asegúrate de que los números son correctos." << std::endl;
        imprimir_uso(argv[0]);
        return 1;
    }

    std::cout << "Configuración de la simulación (Modelo Estable):" << std::endl;
    std::cout << " - Tiempo total: " << tiempo_total << std::endl;
    std::cout << " - Paso de tiempo (dt): " << dt << std::endl;
    std::cout << " - Semilla aleatoria: " << semilla << std::endl;
    std::cout << "------------------------------------------" << std::endl;

    // --- 2. Configurar la partícula con parámetros estables (orden 1) ---
    // Estos parámetros garantizan la estabilidad numérica y permiten observar
    // el comportamiento cualitativo del movimiento browniano.
    ParticulaBrowniana particula;

    double masa_particula = 1.0;
    double gamma = 0.1; // Coeficiente de arrastre
    
    // Se usa una temperatura artificial para que el término k_B * T sea igual a 1.0.
    // Esto simplifica el análisis de la ecuación de Langevin.
    const double K_BOLTZMANN = 1.380649e-23; // J/K
    double temperatura_artificial = 1.0 / K_BOLTZMANN;

    particula.Inicie(
        0.0, 0.0, 0.0,          // Posición inicial (x0, y0, z0)
        0.0, 0.0, 0.0,          // Velocidad inicial (Vx0, Vy0, Vz0)
        masa_particula,         // Masa
        gamma,                  // Coeficiente de arrastre
        temperatura_artificial, // Temperatura tal que kT = 1.0
        semilla
    );

    // --- 3. Configurar y ejecutar el simulador ---
    SimuladorBrowniano simulador;
    simulador.Inicializar(tiempo_total, dt, particula, nombre_archivo_base);
    simulador.CorrerSimulacion();

    std::cout << "------------------------------------------" << std::endl;
    std::cout << "Programa finalizado correctamente." << std::endl;

    return 0;
}

