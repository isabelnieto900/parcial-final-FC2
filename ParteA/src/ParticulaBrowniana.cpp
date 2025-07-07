// ParticulaBrowniana.cpp
#include "ParticulaBrowniana.h"
#include <cmath> // Para std::sqrt, std::pow

// Constante de Boltzmann (ejemplo, ajustar si es necesario o pasar como parámetro)
const double k_Boltzmann = 1.380649e-23; // J/K

ParticulaBrowniana::ParticulaBrowniana() : gen(std::random_device{}()), dist_normal(0.0, 1.0) {
    // Inicializar m, gamma, kT a valores por defecto o esperar a Inicie
    m = 1.0;
    gamma = 1.0;
    kT = 1.0; // kT = k_Boltzmann * Temperatura_real
}

void ParticulaBrowniana::Inicie(double x0, double y0, double z0,
                                double Vx0, double Vy0, double Vz0,
                                double m0, double gamma0, double Temperatura) {
    r = Vector3D(x0, y0, z0);
    V = Vector3D(Vx0, Vy0, Vz0);
    m = m0;
    gamma = gamma0;
    kT = k_Boltzmann * Temperatura; // Asumiendo que Temperatura está en Kelvin
    // Re-inicializar la distribución normal si kT o gamma cambian significativamente la escala de la fuerza aleatoria
    // Para Euler-Maruyama, la fuerza estocástica tiene una varianza relacionada con 2*gamma*kT*dt
}

void ParticulaBrowniana::ActualizarPosicionEulerMaruyama(double dt) {
    // Fuerza estocástica eta(t)
    // <eta_i(t)eta_j(t')> = 2*gamma*kT*delta_ij*delta(t-t')
    // Para la simulación discreta, eta(t)*dt se aproxima como sqrt(2*gamma*kT*dt) * N(0,1)
    // O, si se integra dv = (-gamma*v/m)*dt + (sqrt(2*gamma*kT)/m)*dW
    // donde dW es un incremento de Wiener, N(0, sqrt(dt))

    double factor_fuerza_estocastica = std::sqrt(2.0 * gamma * kT / dt); // Ajustado para eta(t) dt -> sqrt(2*gamma*kT*dt) N(0,1)
                                                                     // O si la ecuación es m dv/dt = -gamma v + eta_tilde(t) con <eta_tilde_i(t)eta_tilde_j(t')> = 2*gamma*kT delta_ij delta(t-t')
                                                                     // entonces dv = (-gamma*v/m)dt + (1/m) * sqrt(2*gamma*kT*dt) * N(0,1)

    Vector3D fuerza_estocastica(
        factor_fuerza_estocastica * dist_normal(gen),
        factor_fuerza_estocastica * dist_normal(gen),
        factor_fuerza_estocastica * dist_normal(gen)
    );

    // Ecuación de Langevin: m * dv/dt = -gamma*V + eta(t)
    // dv = (-gamma*V/m) * dt + (eta(t)/m) * dt
    // Para Euler-Maruyama, eta(t)*dt es sqrt(2*gamma*kT*dt)*N(0,1)
    // dv = (-gamma*V/m)*dt + (sqrt(2*gamma*kT*dt)/m)*N(0,1)

    double sqrt_dt = std::sqrt(dt);
    Vector3D dW(
        dist_normal(gen) * sqrt_dt,
        dist_normal(gen) * sqrt_dt,
        dist_normal(gen) * sqrt_dt
    );

    Vector3D F_drag = V * (-gamma);
    // La fuerza estocástica eta(t) tiene propiedades <eta_i(t)>=0 y <eta_i(t)eta_j(t')> = 2*gamma*kT*delta_ij*delta(t-t')
    // El término en la ecuación de Euler-Maruyama para dv es (1/m)*sqrt(2*gamma*kT*dt)*N(0,1)
    Vector3D F_stochastic_term = dW * (std::sqrt(2.0 * gamma * kT) / m);


    // Actualizar velocidad
    // V(t+dt) = V(t) + (F_drag/m)*dt + (F_stochastic_term/m)*dt  <- Error aquí, F_stochastic_term ya está escalado por 1/m y dt implícito en dW
       V = V + (F_drag * (dt/m)) + F_stochastic_term; // Correcto: F_stochastic_term ya incluye 1/m y sqrt(dt)

    // Actualizar posición
    r = r + V * dt;
}

double ParticulaBrowniana::Getx(void) const { return r.x; }
double ParticulaBrowniana::Gety(void) const { return r.y; }
double ParticulaBrowniana::Getz(void) const { return r.z; }

Vector3D ParticulaBrowniana::GetPosicion(void) const { return r; }
Vector3D ParticulaBrowniana::GetVelocidad(void) const { return V; }

double ParticulaBrowniana::EnergiaCinetica(void) const {
    return 0.5 * m * V.dot(V);
}

void ParticulaBrowniana::ImprimirEstado(std::ostream& os) const {
    os << r.x << " " << r.y << " " << r.z << " "
       << V.x << " " << V.y << " " << V.z;
}
