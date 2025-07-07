// SAWSimulador.cpp
#include "SAWSimulador.h" // Se espera que el Makefile configure la ruta de inclusión
#include <vector>
#include <fstream>   // Para std::ofstream
#include <iostream>  // Para std::cerr
#include <cmath>     // Para std::pow (usado en GetDistanciaExtremoAExtremoCuadrada)
#include <algorithm> // Para std::shuffle (opcional, para aleatorizar direcciones)

SAWSimulador::SAWSimulador(int N_max_pasos, unsigned int semilla)
    : max_steps(N_max_pasos), gen(semilla), distrib_direccion(0, 3), current_steps(0) {
    Reset();
}

void SAWSimulador::Reset() {
    current_position = {0, 0}; // Iniciar en el origen
    path.clear();
    visited_sites.clear();

    path.push_back(current_position);
    visited_sites.insert(current_position);
    current_steps = 0;
}

bool SAWSimulador::RealizarPaso() {
    if (current_steps >= max_steps) {
        return false; // Se alcanzó el máximo de pasos definidos para esta caminata
    }

    // Posibles movimientos (N, E, S, O) - índices 0, 1, 2, 3
    const Point2D desplazamientos[4] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    std::vector<Point2D> posibles_siguientes_posiciones;

    // Intentar las 4 direcciones en orden aleatorio para evitar sesgos direccionales
    std::vector<int> orden_direcciones = {0, 1, 2, 3};
    std::shuffle(orden_direcciones.begin(), orden_direcciones.end(), gen);

    for (int dir_idx : orden_direcciones) {
        Point2D proxima_posicion = {current_position.x + desplazamientos[dir_idx].x,
                                   current_position.y + desplazamientos[dir_idx].y};

        // Verificar si el sitio ya ha sido visitado
        if (visited_sites.find(proxima_posicion) == visited_sites.end()) {
            posibles_siguientes_posiciones.push_back(proxima_posicion);
        }
    }

    if (posibles_siguientes_posiciones.empty()) {
        return false; // La caminata se atascó (no hay movimientos válidos)
    }

    // Elegir una de las posiciones válidas aleatoriamente
    // Si solo hay una, distrib_pasos_validos(0,0) funcionará.
    std::uniform_int_distribution<> distrib_pasos_validos(0, posibles_siguientes_posiciones.size() - 1);
    current_position = posibles_siguientes_posiciones[distrib_pasos_validos(gen)];

    path.push_back(current_position);
    visited_sites.insert(current_position);
    current_steps++;

    return true;
}

bool SAWSimulador::SimularUnaCaminata() {
    Reset(); // Asegura que cada simulación comience de nuevo
    while (current_steps < max_steps) {
        if (!RealizarPaso()) {
            return false; // Se atascó antes de N_max_pasos
        }
    }
    return true; // Alcanzó N_max_pasos
}

double SAWSimulador::GetDistanciaExtremoAExtremoCuadrada() const {
    if (path.empty()) return 0.0;
    // La distancia es entre el primer y el último punto del camino.
    // El primer punto es siempre (0,0) por la forma en que se inicializa.
    Point2D inicio = path.front(); // Debería ser {0,0}
    Point2D fin = path.back(); // Es current_position al final de la caminata

    double dx = static_cast<double>(fin.x - inicio.x);
    double dy = static_cast<double>(fin.y - inicio.y);
    return dx * dx + dy * dy;
}

int SAWSimulador::GetLongitudRealCamino() const {
    // La longitud es el número de pasos dados, que es current_steps.
    // O path.size() - 1, ya que path incluye el punto inicial.
    return current_steps;
}

void SAWSimulador::GuardarCamino(const std::string& filename) const {
    std::ofstream outfile(filename);
    if (!outfile.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo para guardar el camino SAW: " << filename << std::endl;
        return;
    }
    outfile << "# x y (un punto por línea)" << std::endl;
    for (const auto& p : path) {
        outfile << p.x << " " << p.y << std::endl;
    }
    outfile.close();
}
