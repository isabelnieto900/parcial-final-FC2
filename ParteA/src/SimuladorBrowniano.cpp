// SimuladorBrowniano.cpp
#include "SimuladorBrowniano.h"
#include <iostream> // Para std::cerr

SimuladorBrowniano::SimuladorBrowniano() : tiempo_actual(0.0), dt_simulacion(0.01) {}

SimuladorBrowniano::~SimuladorBrowniano() {
    if (archivo_salida.is_open()) {
        archivo_salida.close();
    }
}

void SimuladorBrowniano::AgregarParticula(const ParticulaBrowniana &nueva_particula) {
    particulas.push_back(nueva_particula);
}

void SimuladorBrowniano::Inicializar(double paso_tiempo, const std::string& nombre_archivo_salida) {
    dt_simulacion = paso_tiempo;
    tiempo_actual = 0.0;

    archivo_salida.open(nombre_archivo_salida);
    if (!archivo_salida.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo de salida: " << nombre_archivo_salida << std::endl;
    } else {
        // Opcional: escribir cabecera en el archivo de datos
        // archivo_salida << "tiempo x1 y1 z1 vx1 vy1 vz1 x2 y2 z2 vx2 vy2 vz2 ..." << std::endl;
    }
}

void SimuladorBrowniano::IntegrarPaso() {
    for (size_t i = 0; i < particulas.size(); ++i) {
        particulas[i].ActualizarPosicionEulerMaruyama(dt_simulacion);
    }
    tiempo_actual += dt_simulacion;
}

void SimuladorBrowniano::GuardarEstadoSistema() {
    if (!archivo_salida.is_open()) {
        return; // No hacer nada si el archivo no está abierto
    }
    archivo_salida << tiempo_actual;
    for (size_t i = 0; i < particulas.size(); ++i) {
        archivo_salida << " ";
        particulas[i].ImprimirEstado(archivo_salida); // Asumiendo que ParticulaBrowniana tiene este método
    }
    archivo_salida << std::endl;
}

void SimuladorBrowniano::Simular(double tiempo_total_simulacion, int pasos_entre_guardado) {
    if (!archivo_salida.is_open()) {
        std::cerr << "Error: El archivo de salida no está inicializado. Llama a Inicializar() primero." << std::endl;
        return;
    }

    int pasos_simulacion = 0;
    GuardarEstadoSistema(); // Guardar estado inicial

    while (tiempo_actual < tiempo_total_simulacion) {
        IntegrarPaso();
        pasos_simulacion++;
        if (pasos_simulacion % pasos_entre_guardado == 0) {
            GuardarEstadoSistema();
        }
    }
    // Asegurarse de guardar el último estado si no coincidió exactamente
    if ((pasos_simulacion -1) % pasos_entre_guardado != 0) {
         GuardarEstadoSistema();
    }

    archivo_salida.close(); // Cerrar el archivo al final de la simulación
}
