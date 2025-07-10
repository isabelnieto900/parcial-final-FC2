#include "ParticulaBrowniana.h"
#include <cmath> // Para std::sqrt

// Constante de Boltzmann (J/K)
const double K_BOLTZMANN = 1.380649e-23;

ParticulaBrowniana::ParticulaBrowniana()
    : gen(std::random_device{}()), dist_normal(0.0, 1.0) {
    // Inicializar a valores por defecto seguros, Inicie() los establecerá correctamente
    m = 1.0;
    gamma = 1.0;
    kT = 1.0;
    r = Vector3D(0,0,0);
    V = Vector3D(0,0,0);
}

void ParticulaBrowniana::Inicie(double x0, double y0, double z0,
                                  double Vx0, double Vy0, double Vz0,
                                  double m0, double gamma0, double Temperatura_K, unsigned int semilla) {
    r = Vector3D(x0, y0, z0);
    V = Vector3D(Vx0, Vy0, Vz0);
    m = m0;
    gamma = gamma0;
    kT = K_BOLTZMANN * Temperatura_K;
    gen.seed(semilla); // Sembrar el generador de números aleatorios
}

void ParticulaBrowniana::ActualizarPosicionEulerMaruyama(double dt) {
    if (m <= 1e-9) return; // Evitar división por cero si la masa es muy pequeña o cero

    // Fuerza de arrastre: F_drag = -gamma * V
    Vector3D F_drag = V * (-gamma);

    // --- ADVERTENCIA CORREGIDA ---
    // La variable 'factor_estocastico' se calculaba aquí pero no se usaba.
    // La lógica correcta ya está implementada en 'std_dev_fuerza_est_dt',
    // por lo que la línea original fue eliminada.

    // V_{n+1} = V_n + (F_drag/m)*dt + sqrt(2*gamma*kT*dt)/m * N(0,1)
    double std_dev_fuerza_est_dt = std::sqrt(2.0 * gamma * kT * dt) / m;

    Vector3D ruido(
        dist_normal(gen),
        dist_normal(gen),
        dist_normal(gen)
    );
    Vector3D termino_estocastico_dv = ruido * std_dev_fuerza_est_dt;

    // Actualizar velocidad: V(t+dt) = V(t) + (F_drag/m)*dt + termino_estocastico_dv
    V = V + (F_drag * (1.0/m) * dt) + termino_estocastico_dv;

    // Actualizar posición: r(t+dt) = r(t) + V(t+dt)*dt
    r = r + V * dt;
}

// --- ERROR DE REDEFINICIÓN CORREGIDO ---
// Las siguientes funciones se eliminaron de este archivo .cpp porque ya estaban
// completamente definidas (como 'inline') dentro de la declaración de la clase en el archivo .h.
// Mantenerlas aquí causaba un error de "redefinición".
/*
Vector3D ParticulaBrowniana::GetPosicion(void) const { return r; }
Vector3D ParticulaBrowniana::GetVelocidad(void) const { return V; }
*/

double ParticulaBrowniana::EnergiaCinetica(void) const {
    return 0.5 * m * V.norm2(); // V.norm2() es V.dot(V)
}

void ParticulaBrowniana::ImprimirEstado(std::ostream& os) const {
    // Formato: x y z Vx Vy Vz (separados por espacio)
    os << r.x << " " << r.y << " " << r.z << " "
       << V.x << " " << V.y << " " << V.z;
}

