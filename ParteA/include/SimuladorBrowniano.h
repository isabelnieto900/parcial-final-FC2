// SimuladorBrowniano.h
#ifndef SIMULADOR_BROWNIANO_H
#define SIMULADOR_BROWNIANO_H

#include "ParticulaBrowniana.h" // Asumiendo que está en el mismo directorio include o el Makefile lo resuelve
#include <vector>
#include <string>
#include <fstream> // Para std::ofstream

class SimuladorBrowniano {
private:
    std::vector<ParticulaBrowniana> particulas;
    double tiempo_actual;
    double dt_simulacion;
    std::ofstream archivo_salida; // Para guardar datos
    std::string nombre_archivo_salida_str; // Para poder reabrir si es necesario o para referencia

public:
    SimuladorBrowniano();
    ~SimuladorBrowniano(); // Destructor para cerrar el archivo si está abierto

    void AgregarParticula(const ParticulaBrowniana &nueva_particula);

    // Inicializa el simulador, incluyendo la apertura del archivo de salida.
    void Inicializar(double paso_tiempo, const std::string& _nombre_archivo_salida);

    // Realiza un paso de integración para todas las partículas.
    void IntegrarPaso();

    // Guarda el estado actual del sistema (tiempo y estado de cada partícula) en el archivo.
    void GuardarEstadoSistema();

    // Ejecuta la simulación completa.
    // pasos_entre_guardado: frecuencia con la que se guardan los datos (cada N pasos).
    void Simular(double tiempo_total_simulacion, int pasos_entre_guardado);

    // Método para obtener una referencia al vector de partículas (útil para análisis post-simulación)
    const std::vector<ParticulaBrowniana>& GetParticulas() const { return particulas; }
};

#endif // SIMULADOR_BROWNIANO_H
