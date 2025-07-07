// SimuladorBrowniano.cpp
#include "SimuladorBrowniano.h"
#include <iostream> // Para std::cerr, std::endl
#include <iomanip>  // Para std::fixed, std::setprecision

SimuladorBrowniano::SimuladorBrowniano() : tiempo_actual(0.0), dt_simulacion(0.01) {
    // El constructor por defecto. El archivo se abre en Inicializar.
}

SimuladorBrowniano::~SimuladorBrowniano() {
    if (archivo_salida.is_open()) {
        archivo_salida.close();
    }
}

void SimuladorBrowniano::AgregarParticula(const ParticulaBrowniana &nueva_particula) {
    particulas.push_back(nueva_particula);
}

void SimuladorBrowniano::Inicializar(double paso_tiempo, const std::string& _nombre_archivo_salida) {
    dt_simulacion = paso_tiempo;
    tiempo_actual = 0.0;
    nombre_archivo_salida_str = _nombre_archivo_salida;

    if (archivo_salida.is_open()) {
        archivo_salida.close(); // Cerrar si ya estaba abierto por alguna razón
    }
    archivo_salida.open(nombre_archivo_salida_str);
    if (!archivo_salida.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo de salida: " << nombre_archivo_salida_str << std::endl;
    } else {
        // Escribir cabecera en el archivo de datos
        // Formato: tiempo x1 y1 z1 vx1 vy1 vz1 x2 y2 z2 vx2 vy2 vz2 ...
        archivo_salida << "# Tiempo";
        for (size_t i = 0; i < particulas.size(); ++i) {
            archivo_salida << " x" << i+1 << " y" << i+1 << " z" << i+1
                           << " Vx" << i+1 << " Vy" << i+1 << " Vz" << i+1;
        }
        archivo_salida << std::endl;
        archivo_salida << std::fixed << std::setprecision(8); // Formato para los datos numéricos
    }
}

void SimuladorBrowniano::IntegrarPaso() {
    for (size_t i = 0; i < particulas.size(); ++i) {
        // Para el movimiento Browniano, la "fuerza" (aleatoria y de arrastre)
        // está incorporada en el método de actualización de la partícula.
        particulas[i].ActualizarPosicionEulerMaruyama(dt_simulacion);
    }
    tiempo_actual += dt_simulacion;
}

void SimuladorBrowniano::GuardarEstadoSistema() {
    if (!archivo_salida.is_open()) {
        return;
    }
    archivo_salida << tiempo_actual;
    for (size_t i = 0; i < particulas.size(); ++i) {
        archivo_salida << " ";
        particulas[i].ImprimirEstado(archivo_salida);
    }
    archivo_salida << std::endl;
}

void SimuladorBrowniano::Simular(double tiempo_total_simulacion, int pasos_entre_guardado) {
    if (!archivo_salida.is_open()) {
        std::cerr << "Error: El archivo de salida no está inicializado. Llama a Inicializar() primero." << std::endl;
        return;
    }
    if (particulas.empty()){
        std::cerr << "Advertencia: No hay partículas en el simulador." << std::endl;
        return;
    }

    // Si Inicializar no fue llamado después de agregar partículas, la cabecera podría ser incorrecta.
    // Podríamos reabrir y reescribir cabecera aquí, o asegurar que Inicializar se llame después de agregar partículas.
    // Por ahora, se asume que Inicializar se llama con el estado correcto de `particulas.size()`.

    long long pasos_simulacion_total = 0;
    GuardarEstadoSistema(); // Guardar estado inicial en t=0

    while (tiempo_actual < tiempo_total_simulacion) {
        IntegrarPaso();
        pasos_simulacion_total++;
        if (pasos_simulacion_total % pasos_entre_guardado == 0) {
            GuardarEstadoSistema();
        }
    }

    // Asegurarse de guardar el último estado si no coincidió exactamente con un paso de guardado
    // y si el tiempo actual es significativamente diferente del último guardado.
    if ((pasos_simulacion_total % pasos_entre_guardado != 0) && tiempo_total_simulacion > 0) {
         GuardarEstadoSistema();
    }

    if (archivo_salida.is_open()) {
        archivo_salida.close();
    }
    std::cout << "Simulación finalizada. Tiempo total simulado: " << tiempo_actual << " s. Pasos totales: " << pasos_simulacion_total << std::endl;
}
