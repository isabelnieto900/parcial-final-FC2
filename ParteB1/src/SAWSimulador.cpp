// SAWSimulador.cpp
#include "SAWSimulador.h"
#include <vector>
#include <random>
#include <fstream>
#include <iostream> // Para std::cerr
#include <cmath>   // Para std::sqrt y std::pow

SAWSimulador::SAWSimulador(int N_max_pasos, int seed)
    : max_steps(N_max_pasos), gen(seed), distrib_direccion(0, 3) {
    Reset();
}

void SAWSimulador::Reset() {
    current_position = {0, 0};
    path.clear();
    visited_sites.clear();
    path.push_back(current_position);
    visited_sites.insert(current_position);
}

bool SAWSimulador::RealizarPaso() {
    if (path.size() >= static_cast<size_t>(max_steps + 1)) { // +1 porque el camino incluye el punto inicial
        return false; // Se alcanzó el máximo de pasos
    }

    // Posibles movimientos (N, E, S, O)
    const Point2D movimientos[4] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    std::vector<Point2D> posibles_pasos;
    for (int i = 0; i < 4; ++i) {
        Point2D proximo_paso = {current_position.x + movimientos[i].x, current_position.y + movimientos[i].y};
        if (visited_sites.find(proximo_paso) == visited_sites.end()) {
            posibles_pasos.push_back(proximo_paso);
        }
    }

    if (posibles_pasos.empty()) {
        return false; // La caminata se atascó (no hay movimientos válidos)
    }

    // Elegir un paso válido aleatoriamente
    std::uniform_int_distribution<> distrib_pasos_validos(0, posibles_pasos.size() - 1);
    current_position = posibles_pasos[distrib_pasos_validos(gen)];

    path.push_back(current_position);
    visited_sites.insert(current_position);

    return true;
}

bool SAWSimulador::SimularUnaCaminata() {
    Reset();
    while(path.size() <= static_cast<size_t>(max_steps)) { // <= porque path.size() es N+1
        if (!RealizarPaso()) {
            return false; // Se atascó antes de N_max_pasos
        }
    }
    return true; // Alcanzó N_max_pasos
}

double SAWSimulador::GetDistanciaExtremoAExtremoCuadrada() const {
    if (path.empty()) return 0.0;
    Point2D start = path.front();
    Point2D end = path.back();
    double dx = static_cast<double>(end.x - start.x);
    double dy = static_cast<double>(end.y - start.y);
    return dx * dx + dy * dy;
}

int SAWSimulador::GetLongitudCamino() const {
    // La longitud es el número de pasos, que es path.size() - 1
    return path.empty() ? 0 : path.size() - 1;
}

void SAWSimulador::GuardarCamino(const std::string& filename) const {
    std::ofstream outfile(filename);
    if (!outfile.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo para guardar el camino: " << filename << std::endl;
        return;
    }
    for (const auto& p : path) {
        outfile << p.x << " " << p.y << std::endl;
    }
    outfile.close();
}
