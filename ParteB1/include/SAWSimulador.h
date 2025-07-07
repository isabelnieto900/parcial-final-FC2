// SAWSimulador.h
#ifndef SAW_SIMULADOR_H
#define SAW_SIMULADOR_H

#include "Vector3D.h" // Para representar posiciones en la retícula (aunque int podría ser más apropiado para índices)
#include <vector>
#include <string>
#include <set> // Para mantener un registro eficiente de los sitios visitados

// Podríamos usar una estructura simple para las coordenadas de la retícula si Vector3D es demasiado pesado
struct Point2D {
    int x, y;
    bool operator<(const Point2D& other) const { // Necesario para std::set
        if (x != other.x) return x < other.x;
        return y < other.y;
    }
    bool operator==(const Point2D& other) const { // Para comprobaciones
        return x == other.x && y == other.y;
    }
};

class SAWSimulador {
private:
    Point2D current_position;
    std::vector<Point2D> path; // Almacena la caminata actual
    std::set<Point2D> visited_sites; // Para verificar auto-intersecciones rápidamente

    int lattice_size; // Podría ser útil si la caminata está confinada, aunque SAW es usualmente en una red infinita
    int max_steps;    // Número máximo de pasos para una caminata

    // Generador de números aleatorios (se podría usar el de C++ <random>)
    std::mt19937 gen;
    std::uniform_int_distribution<> distrib_direccion; // Para 0, 1, 2, 3 (ej. N, E, S, O)

public:
    SAWSimulador(int N_max_pasos, int seed = std::random_device{}());

    void Reset(); // Reinicia la caminata para una nueva simulación
    bool RealizarPaso(); // Intenta realizar un paso de la SAW

    // Ejecuta una simulación completa de SAW hasta max_steps o hasta que se atasque
    // Devuelve true si la caminata alcanzó max_steps, false si se atascó
    bool SimularUnaCaminata();

    // Para medir propiedades
    double GetDistanciaExtremoAExtremoCuadrada() const; // R^2
    int GetLongitudCamino() const;

    // Guardar la trayectoria (opcional, para visualización)
    void GuardarCamino(const std::string& filename) const;
};

#endif // SAW_SIMULADOR_H
