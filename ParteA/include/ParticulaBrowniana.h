/**
 * @file ParticulaBrowniana.h
 * @brief Declaración de la clase ParticulaBrowniana, que modela una partícula
 * sometida a la ecuación de Langevin en 3D.
 * @author Camilo Andres Huertas Archila
 * @date 2025-07-09
 */

#ifndef PARTICULA_BROWNIANA_H
#define PARTICULA_BROWNIANA_H

#include "Vector3D.h"
#include <random>
#include <iostream>

/**
 * @class ParticulaBrowniana
 * @brief Representa una partícula puntual que experimenta movimiento browniano.
 *
 * Esta clase encapsula las propiedades físicas de una partícula (posición,
 * velocidad, masa) y las fuerzas que actúan sobre ella (arrastre viscoso y
 * fuerza estocástica). La evolución temporal se calcula mediante el método
 * de Euler-Maruyama.
 */
class ParticulaBrowniana {
private:
    Vector3D r, V; ///< Vector de posición (r) y velocidad (V) de la partícula.
    double m;      ///< Masa de la partícula.
    double gamma;  ///< Coeficiente de fricción o arrastre viscoso.
    double kT;     ///< Energía térmica (Constante de Boltzmann * Temperatura).

    std::mt19937 gen; ///< Generador de números aleatorios (Mersenne Twister).
    std::normal_distribution<> dist_normal; ///< Distribución normal estándar N(0,1).

public:
    /**
     * @brief Constructor por defecto.
     */
    ParticulaBrowniana();

    /**
     * @brief Inicializa el estado completo de la partícula.
     * @param x0 Componente x de la posición inicial.
     * @param y0 Componente y de la posición inicial.
     * @param z0 Componente z de la posición inicial.
     * @param Vx0 Componente x de la velocidad inicial.
     * @param Vy0 Componente y de la velocidad inicial.
     * @param Vz0 Componente z de la velocidad inicial.
     * @param m0 Masa de la partícula.
     * @param gamma0 Coeficiente de arrastre.
     * @param Temperatura_K Temperatura del fluido en Kelvin.
     * @param semilla Semilla para el generador de números aleatorios.
     */
    void Inicie(double x0, double y0, double z0,
                double Vx0, double Vy0, double Vz0,
                double m0, double gamma0, double Temperatura_K, unsigned int semilla = std::random_device{}());

    /**
     * @brief Avanza la simulación un paso de tiempo usando el método de Euler-Maruyama.
     * @param dt El paso de tiempo para la integración.
     */
    void ActualizarPosicionEulerMaruyama(double dt);

    // --- Getters ---

    /**
     * @brief Obtiene la posición actual de la partícula.
     * @return Un Vector3D con la posición (r).
     */
    Vector3D GetPosicion(void) const { return r; }

    /**
     * @brief Obtiene la velocidad actual de la partícula.
     * @return Un Vector3D con la velocidad (V).
     */
    Vector3D GetVelocidad(void) const { return V; }
    
    /**
     * @brief Calcula la energía cinética instantánea de la partícula.
     * @return El valor de la energía cinética (0.5 * m * V^2).
     */
    double EnergiaCinetica(void) const;

    /**
     * @brief Imprime el estado actual de la partícula a un stream de salida.
     * @param os El stream de salida (ej. std::cout o un std::ofstream).
     */
    void ImprimirEstado(std::ostream& os) const;
};

#endif // PARTICULA_BROWNIANA_H

