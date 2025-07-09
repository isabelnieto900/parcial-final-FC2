// -------------------------------------------------------------------------
// 1. GUARDAS DE CABECERA (HEADER GUARDS)
// -------------------------------------------------------------------------
// Evitan que el contenido de este archivo se incluya más de una vez
// en una misma compilación, lo que causaría errores de redefinición.
#ifndef SAW_SIMULADOR_H
#define SAW_SIMULADOR_H

// -------------------------------------------------------------------------
// 2. INCLUSIONES DE LIBRERÍAS ESTÁNDAR
// -------------------------------------------------------------------------
#include <vector>   // Para std::vector, usado para almacenar la trayectoria (path).
#include <string>   // Para std::string, usado en nombres de archivo.
#include <set>      // Para std::set, usado para un chequeo rápido de sitios visitados.
#include <random>   // Para el generador de números aleatorios (std::mt19937).

// -------------------------------------------------------------------------
// 3. DEFINICIÓN DE LA ESTRUCTURA Point2D
// -------------------------------------------------------------------------
/**
 * @struct Point2D
 * @brief Representa un punto con coordenadas enteras (x, y) en una retícula 2D.
 * @details Esta estructura es fundamental para definir la posición de cada paso
 * en la caminata aleatoria.
 */
struct Point2D {
    int x, y;

    /**
     * @brief Operador de comparación "menor que".
     * @details Esencial para poder usar Point2D como clave en un std::set,
     * lo que permite una búsqueda eficiente de sitios ya visitados.
     * Compara primero por la coordenada x, y luego por la y.
     * @param other El otro punto con el que se compara.
     * @return true si este punto es "menor" que el otro.
     */
    bool operator<(const Point2D& other) const {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }

    /**
     * @brief Operador de comparación de igualdad.
     * @param other El otro punto con el que se compara.
     * @return true si ambos puntos tienen las mismas coordenadas.
     */
    bool operator==(const Point2D& other) const {
        return x == other.x && y == other.y;
    }
};

// -------------------------------------------------------------------------
// 4. DECLARACIÓN DE LA CLASE SAWSimulador
// -------------------------------------------------------------------------
/**
 * @class SAWSimulador
 * @brief Gestiona la simulación de una única Caminata Aleatoria Autoevitante (SAW).
 * @details Esta clase encapsula toda la lógica para generar una caminata,
 * incluyendo el seguimiento de la trayectoria, la comprobación de auto-intersecciones
 * y la selección aleatoria de los siguientes pasos.
 */
class SAWSimulador {
public: // --- INTERFAZ PÚBLICA ---
    // Métodos que el 'main' u otro código puede llamar.

    /**
     * @brief Constructor de la clase SAWSimulador.
     * @param N_max_pasos La longitud máxima (número de pasos) que la caminata intentará alcanzar.
     * @param seed La semilla para inicializar el generador de números aleatorios, permitiendo reproducibilidad.
     */
    SAWSimulador(int N_max_pasos, unsigned int seed);

    /**
     * @brief Ejecuta una simulación completa de una caminata.
     * @details Reinicia la caminata y la extiende paso a paso hasta que alcanza
     * la longitud máxima (max_steps) o hasta que queda atrapada sin movimientos válidos.
     * @return true si la caminata alcanzó N_max_pasos (exitosa), false si se atascó antes.
     */
    bool runWalk();

    /**
     * @brief Obtiene el desplazamiento cuadrático final de la caminata (R^2).
     * @details Calcula la distancia euclidiana al cuadrado desde el punto de inicio (0,0)
     * hasta el punto final de la caminata.
     * @return El valor de (x_final^2 + y_final^2).
     */
    double getEndToEndDistanceSq() const;

    /**
     * @brief Obtiene la longitud final (número de pasos) de la caminata generada.
     * @return El número de pasos que la caminata logró dar antes de terminar.
     */
    int getPathLength() const;
    
    /**
     * @brief Devuelve la trayectoria completa de la caminata.
     * @details Proporciona acceso de solo lectura al vector de puntos que componen el camino,
     * útil para guardar o visualizar una caminata de ejemplo.
     * @return Una referencia constante al vector de Point2D que representa el camino.
     */
    const std::vector<Point2D>& getPath() const;

private: // --- MIEMBROS PRIVADOS ---
    // Variables y métodos internos, no accesibles desde fuera de la clase.

    /**
     * @brief Reinicia el estado de la simulación para una nueva caminata.
     * @details Limpia la trayectoria y el conjunto de sitios visitados, y
     * restablece la posición inicial al origen (0,0).
     */
    void reset();

    // Miembros de datos (variables de estado)
    int max_steps;                      // Número máximo de pasos objetivo.
    int current_steps;                  // Pasos actuales en la caminata.
    Point2D current_position;           // Posición actual del caminante.
    std::vector<Point2D> path;          // Almacena la secuencia de puntos visitados (la trayectoria).
    std::set<Point2D> visited_sites;    // Conjunto de sitios visitados para chequeo rápido O(log N).

    std::mt19937 gen;                   // Generador de números aleatorios Mersenne Twister.
};

// Fin de la guarda de cabecera
#endif // SAW_SIMULADOR_H

