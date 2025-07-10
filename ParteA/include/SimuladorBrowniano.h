/**
 * @file SimuladorBrowniano.h
 * @brief Declaración de la clase SimuladorBrowniano, que gestiona la simulación completa.
 * @author Camilo Andres Huertas Archila
 * @date 2025-07-09
 */

#ifndef SIMULADOR_BROWNIANO_H
#define SIMULADOR_BROWNIANO_H

#include "ParticulaBrowniana.h"
#include <string>
#include <fstream> // Para std::ofstream

/**
 * @class SimuladorBrowniano
 * @brief Orquesta la simulación del movimiento browniano para una partícula.
 *
 * Esta clase se encarga de inicializar los parámetros de la simulación
 * (tiempo, dt), manejar el archivo de salida de datos, y ejecutar el bucle
 * principal que actualiza el estado de la partícula a lo largo del tiempo.
 */
class SimuladorBrowniano {
private:
    ParticulaBrowniana particula; ///< La partícula que será simulada.
    double tiempo_total_sim;      ///< Duración total de la simulación.
    double paso_tiempo;           ///< Paso de tiempo (dt) para la integración.
    std::ofstream archivo_salida; ///< Stream para escribir los datos en un archivo.

public:
    /**
     * @brief Constructor por defecto.
     */
    SimuladorBrowniano();

    /**
     * @brief Destructor. Cierra el archivo de salida si está abierto.
     */
    ~SimuladorBrowniano();

    /**
     * @brief Configura e inicializa la simulación.
     * @param t_total Duración total de la simulación.
     * @param dt Paso de tiempo para la integración.
     * @param p_inicial La partícula ya configurada que se va a simular.
     * @param nombre_base_archivo El nombre base para el archivo de datos de salida (sin extensión).
     */
    void Inicializar(double t_total, double dt, const ParticulaBrowniana& p_inicial, const std::string& nombre_base_archivo);

    /**
     * @brief Ejecuta el bucle principal de la simulación.
     * Itera desde t=0 hasta t=tiempo_total_sim, actualizando la partícula
     * y guardando su estado periódicamente.
     */
    void CorrerSimulacion();

private:
    /**
     * @brief Guarda el estado actual de la partícula en el archivo de datos.
     * @param tiempo El tiempo actual de la simulación para registrar en la primera columna.
     */
    void GuardarEstado(double tiempo);
};

#endif // SIMULADOR_BROWNIANO_H

