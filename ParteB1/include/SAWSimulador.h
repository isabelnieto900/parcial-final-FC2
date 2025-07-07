// SAWSimulador.h
#ifndef SAW_SIMULADOR_H
#define SAW_SIMULADOR_H

#include <vector>
#include <string>
#include <set>
#include <random> // Para std::mt19937, std::uniform_int_distribution, std::random_device

// Estructura para coordenadas 2D en la retícula
struct Point2D {
    int x, y;

    // Operador necesario para std::set y std::map
    bool operator<(const Point2D& other) const {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }
    // Operador de igualdad para comparaciones
    bool operator==(const Point2D& other) const {
        return x == other.x && y == other.y;
    }
};

class SAWSimulador {
private:
    Point2D current_position;          // Posición actual del extremo de la caminata
    std::vector<Point2D> path;         // Secuencia de puntos que forman la caminata
    std::set<Point2D> visited_sites;   // Conjunto de sitios visitados para chequeo rápido de auto-evitación

    int max_steps;                     // Número máximo de pasos para una caminata
    int current_steps;                 // Número actual de pasos en la caminata

    std::mt19937 gen;                  // Generador de números aleatorios Mersenne Twister
    std::uniform_int_distribution<> distrib_direccion; // Para elegir una de las 4 direcciones

public:
    // Constructor: N_max_pasos es la longitud deseada de la caminata (número de segmentos)
    SAWSimulador(int N_max_pasos, unsigned int semilla = std::random_device{}());

    void Reset(); // Reinicia la caminata a su estado inicial (origen, un solo punto)

    // Intenta realizar un paso de la caminata autoevitante.
    // Devuelve true si el paso fue exitoso, false si la caminata se atascó.
    bool RealizarPaso();

    // Ejecuta una simulación completa de una caminata SAW.
    // La caminata continúa hasta alcanzar `max_steps` o hasta que se atasque.
    // Devuelve true si la caminata alcanzó `max_steps`, false si se atascó antes.
    bool SimularUnaCaminata();

    // Métodos para obtener propiedades de la caminata completada
    double GetDistanciaExtremoAExtremoCuadrada() const; // Calcula R^2 (distancia cuadrada del inicio al fin)
    int GetLongitudRealCamino() const; // Devuelve el número de pasos realizados (puede ser < max_steps si se atascó)

    // Guarda la trayectoria actual de la caminata a un archivo.
    // Útil para visualización de ejemplos.
    void GuardarCamino(const std::string& filename) const;
};

#endif // SAW_SIMULADOR_H
