// -------------------------------------------------------------------------
// 1. INCLUSIÓN DEL ARCHIVO DE CABECERA CORRESPONDIENTE
// -------------------------------------------------------------------------
// Esto le da a este archivo .cpp acceso a la declaración de la clase SAWSimulador.
#include "SAWSimulador.h"

// -------------------------------------------------------------------------
// 2. INCLUSIONES ADICIONALES DE LIBRERÍAS ESTÁNDAR
// -------------------------------------------------------------------------
#include <vector>       // Aunque ya está en el .h, es buena práctica incluirlo si se usa directamente.
#include <iostream>     // No es estrictamente necesario aquí, pero útil para depuración.
#include <algorithm>    // Para std::shuffle, una forma de aleatorizar las direcciones.

// -------------------------------------------------------------------------
// 3. IMPLEMENTACIÓN DEL CONSTRUCTOR
// -------------------------------------------------------------------------
/**
 * @brief Constructor de la clase.
 * @details Inicializa los miembros de la clase con los valores proporcionados.
 * Pre-reserva memoria para el vector 'path' para mejorar la eficiencia,
 * evitando realocaciones de memoria durante la ejecución de la caminata.
 * @param N_max_pasos Longitud máxima objetivo de la caminata.
 * @param seed Semilla para el generador de números aleatorios.
 */
SAWSimulador::SAWSimulador(int N_max_pasos, unsigned int seed)
    : max_steps(N_max_pasos), gen(seed) { // Lista de inicialización de miembros
    path.reserve(N_max_pasos + 1); // Optimización: reservar memoria para evitar realocaciones.
    reset(); // Llama a reset para establecer el estado inicial.
}

// -------------------------------------------------------------------------
// 4. IMPLEMENTACIÓN DEL MÉTODO 'reset'
// -------------------------------------------------------------------------
/**
 * @brief Reinicia la caminata a su estado inicial.
 * @details Limpia todas las estructuras de datos y coloca al caminante
 * en el origen (0,0), listo para una nueva simulación.
 */
void SAWSimulador::reset() {
    current_position = {0, 0}; // La caminata siempre empieza en el origen.
    path.clear();              // Borra la trayectoria anterior.
    visited_sites.clear();     // Borra el conjunto de sitios visitados.

    // Añade el punto de inicio a la trayectoria y al conjunto de visitados.
    path.push_back(current_position);
    visited_sites.insert(current_position);
    current_steps = 0; // El número de pasos dados es cero al inicio.
}

// -------------------------------------------------------------------------
// 5. IMPLEMENTACIÓN DEL MÉTODO PRINCIPAL 'runWalk'
// -------------------------------------------------------------------------
/**
 * @brief Ejecuta una simulación completa de una caminata autoevitante.
 * @details Este es el corazón de la simulación. El bucle se ejecuta hasta
 * que se alcanza el número máximo de pasos o la caminata se queda atrapada.
 * @return true si la caminata fue exitosa (alcanzó max_steps), false si no.
 */
bool SAWSimulador::runWalk() {
    reset(); // Asegura que cada caminata comience desde un estado limpio.
    
    while (current_steps < max_steps) {
        // Define los 4 posibles desplazamientos desde la posición actual (Norte, Este, Sur, Oeste).
        const Point2D desplazamientos[4] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        std::vector<Point2D> valid_moves;
        valid_moves.reserve(4); // Pequeña optimización.

        // Itera sobre los 4 posibles movimientos para encontrar los que son válidos.
        for (const auto& d : desplazamientos) {
            Point2D next_pos = {current_position.x + d.x, current_position.y + d.y};
            
            // Un movimiento es válido si el sitio de destino NO ha sido visitado.
            // La búsqueda en std::set (find) es muy eficiente (logarítmica).
            if (visited_sites.find(next_pos) == visited_sites.end()) {
                valid_moves.push_back(next_pos);
            }
        }

        // Comprueba si la caminata está atrapada.
        if (valid_moves.empty()) {
            return false; // Atrapado. No hay movimientos válidos. Termina la caminata.
        }

        // Si hay movimientos válidos, elige uno de ellos al azar.
        std::uniform_int_distribution<> distrib(0, valid_moves.size() - 1);
        current_position = valid_moves[distrib(gen)];
        
        // Actualiza el estado de la caminata con el nuevo paso.
        path.push_back(current_position);
        visited_sites.insert(current_position);
        current_steps++;
    }
    
    return true; // Éxito. El bucle terminó porque se alcanzó max_steps.
}

// -------------------------------------------------------------------------
// 6. IMPLEMENTACIÓN DE LOS MÉTODOS 'GETTER'
// -------------------------------------------------------------------------
// Estos métodos simplemente devuelven el valor de variables privadas.

/**
 * @brief Devuelve el cuadrado de la distancia del inicio al fin.
 */
double SAWSimulador::getEndToEndDistanceSq() const {
    if (path.empty()) return 0.0;
    // El punto de inicio es siempre {0,0}, por lo que solo necesitamos las coordenadas del final.
    const auto& end_point = path.back();
    double dx = static_cast<double>(end_point.x);
    double dy = static_cast<double>(end_point.y);
    return dx * dx + dy * dy;
}

/**
 * @brief Devuelve la longitud final de la caminata.
 */
int SAWSimulador::getPathLength() const {
    return current_steps;
}

/**
 * @brief Devuelve una referencia constante a la trayectoria.
 */
const std::vector<Point2D>& SAWSimulador::getPath() const {
    return path;
}

