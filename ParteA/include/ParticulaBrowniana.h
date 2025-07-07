// ParticulaBrowniana.h
#ifndef PARTICULA_BROWNIANA_H
#define PARTICULA_BROWNIANA_H

#include "Vector3D.h" // Se asume que está en el mismo directorio include o el Makefile lo resuelve
#include <random>    // Para generador de números aleatorios
#include <iostream>  // Para std::ostream

class ParticulaBrowniana {
private:
    Vector3D r, V; // Posición, Velocidad
    double m;      // Masa
    double gamma;  // Coeficiente de fricción
    double kT;     // Producto de constante de Boltzmann y Temperatura (k_B * T)

    // Generador de números aleatorios para la fuerza estocástica
    // Se recomienda inicializarlo con una semilla para reproducibilidad en pruebas,
    // y con std::random_device para corridas de producción.
    std::mt19937 gen;
    std::normal_distribution<> dist_normal; // Distribución N(0,1)

public:
    // Constructor y método de inicialización
    ParticulaBrowniana(); // Constructor por defecto
    void Inicie(double x0, double y0, double z0,
                double Vx0, double Vy0, double Vz0,
                double m0, double gamma0, double Temperatura_K, unsigned int semilla = std::random_device{}());

    // Método para actualizar la posición usando Euler-Maruyama
    void ActualizarPosicionEulerMaruyama(double dt);

    // Métodos para obtener información de la partícula
    double Getx(void) const { return r.x; }
    double Gety(void) const { return r.y; }
    double Getz(void) const { return r.z; }
    Vector3D GetPosicion(void) const { return r; }
    Vector3D GetVelocidad(void) const { return V; }
    double EnergiaCinetica(void) const;

    // Método para imprimir datos (formato: x y z vx vy vz)
    void ImprimirEstado(std::ostream& os) const;
};

#endif // PARTICULA_BROWNIANA_H
