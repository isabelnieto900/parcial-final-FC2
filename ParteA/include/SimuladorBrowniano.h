// SimuladorBrowniano.h
#ifndef SIMULADOR_BROWNIANO_H
#define SIMULADOR_BROWNIANO_H

#include "ParticulaBrowniana.h"
#include <vector>
#include <string>
#include <fstream> // Para std::ofstream

class SimuladorBrowniano {
private:
    std::vector<ParticulaBrowniana> particulas;
    double tiempo_actual;
    double dt_simulacion;
    std::ofstream archivo_salida; // Para guardar datos

public:
    SimuladorBrowniano();
    ~SimuladorBrowniano(); // Destructor para cerrar el archivo si está abierto

    void AgregarParticula(const ParticulaBrowniana &nueva_particula);
    void Inicializar(double paso_tiempo, const std::string& nombre_archivo_salida);

    // Para el movimiento Browniano, las "fuerzas" son intrínsecas a la actualización de la partícula.
    // No hay un paso explícito de "CalcularFuerzas" entre partículas como en N-cuerpos.

    void IntegrarPaso(); // Actualiza cada partícula
    void GuardarEstadoSistema(); // Guarda el estado actual de todas las partículas

    void Simular(double tiempo_total_simulacion, int pasos_entre_guardado);
};

#endif // SIMULADOR_BROWNIANO_H
