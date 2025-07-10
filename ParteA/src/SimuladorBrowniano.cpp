#include "SimuladorBrowniano.h"
#include <iostream>
#include <iomanip>      // Para std::setprecision
#include <filesystem>   // Para crear directorios

// Constructor
SimuladorBrowniano::SimuladorBrowniano() : tiempo_total_sim(0.0), paso_tiempo(0.0) {
}

// Destructor: se asegura de que el archivo se cierre correctamente.
SimuladorBrowniano::~SimuladorBrowniano() {
    if (archivo_salida.is_open()) {
        archivo_salida.close();
    }
}

// Implementación de Inicializar
void SimuladorBrowniano::Inicializar(double t_total, double dt, const ParticulaBrowniana& p_inicial, const std::string& nombre_base_archivo) {
    this->tiempo_total_sim = t_total;
    this->paso_tiempo = dt;
    this->particula = p_inicial;

    std::string nombre_archivo = "results/" + nombre_base_archivo + ".dat";

    try {
        std::filesystem::path dir_path("results");
        if (!std::filesystem::exists(dir_path)) {
            std::filesystem::create_directory(dir_path);
        }
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error creando el directorio 'results': " << e.what() << std::endl;
    }

    archivo_salida.open(nombre_archivo);
    if (!archivo_salida.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo de salida: " << nombre_archivo << std::endl;
        return;
    }

    archivo_salida << "# t x y z Vx Vy Vz E_cinetica\n";
    archivo_salida << std::fixed << std::setprecision(6);
}

// Implementación de CorrerSimulacion
void SimuladorBrowniano::CorrerSimulacion() {
    if (!archivo_salida.is_open()) {
        std::cerr << "Error: La simulación no puede correr. Llama a Inicializar() primero." << std::endl;
        return;
    }

    int pasos_totales = static_cast<int>(tiempo_total_sim / paso_tiempo);
    int pasos_entre_guardado = 100;

    GuardarEstado(0.0);

    for (int i = 1; i <= pasos_totales; ++i) {
        particula.ActualizarPosicionEulerMaruyama(paso_tiempo);

        if (i % pasos_entre_guardado == 0) {
            double tiempo_actual = i * paso_tiempo;
            GuardarEstado(tiempo_actual);
        }
    }

    if (pasos_totales % pasos_entre_guardado != 0) {
        GuardarEstado(tiempo_total_sim);
    }
}

// --- FUNCIÓN CORREGIDA ---
void SimuladorBrowniano::GuardarEstado(double tiempo) {
    if (!archivo_salida.is_open()) return;

    // Se obtiene el vector de posición completo
    Vector3D r = particula.GetPosicion();
    // Se obtiene el vector de velocidad completo
    Vector3D V = particula.GetVelocidad();

    // Se escriben los componentes de los vectores obtenidos
    archivo_salida << tiempo << " "
                   << r.x << " " << r.y << " " << r.z << " "
                   << V.x << " " << V.y << " " << V.z << " "
                   << particula.EnergiaCinetica() << "\n";
}

