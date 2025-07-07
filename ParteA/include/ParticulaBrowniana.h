// ParticulaBrowniana.h
#ifndef PARTICULA_BROWNIANA_H
#define PARTICULA_BROWNIANA_H

#include "Vector3D.h"
#include <random> // Para generador de números aleatorios

class ParticulaBrowniana {
private:
    Vector3D r, V; // Posición, Velocidad (Fuerza se maneja diferente aquí)
    double m;      // Masa
    double gamma;  // Coeficiente de fricción
    double kT;     // Producto de constante de Boltzmann y Temperatura

    // Generador de números aleatorios para la fuerza estocástica
    std::mt19937 gen; // Mersenne Twister
    std::normal_distribution<> dist_normal;

public:
    // Constructor y método de inicialización
    ParticulaBrowniana();
    void Inicie(double x0, double y0, double z0,
                double Vx0, double Vy0, double Vz0,
                double m0, double gamma0, double Temperatura);

    // Método para actualizar la posición usando Euler-Maruyama
    void ActualizarPosicionEulerMaruyama(double dt);

    // Métodos para obtener información de la partícula
    double Getx(void) const;
    double Gety(void) const;
    double Getz(void) const;
    Vector3D GetPosicion(void) const;
    Vector3D GetVelocidad(void) const;
    double EnergiaCinetica(void) const;

    // Método para imprimir datos (puede ser útil para debugging o guardar resultados)
    void ImprimirEstado(std::ostream& os) const;
};

#endif // PARTICULA_BROWNIANA_H
