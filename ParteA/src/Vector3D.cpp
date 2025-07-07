// Vector3D.cpp
#include "Vector3D.h" // Asegúrate que el Makefile maneje la ruta a include/

// Constructores
Vector3D::Vector3D(double x_val, double y_val, double z_val) : x(x_val), y(y_val), z(z_val) {}

// Sobrecarga de operadores
Vector3D Vector3D::operator+(const Vector3D& other) const {
    return Vector3D(x + other.x, y + other.y, z + other.z);
}

Vector3D Vector3D::operator-(const Vector3D& other) const {
    return Vector3D(x - other.x, y - other.y, z - other.z);
}

Vector3D Vector3D::operator*(double scalar) const {
    return Vector3D(x * scalar, y * scalar, z * scalar);
}

double Vector3D::dot(const Vector3D& other) const {
    return x * other.x + y * other.y + z * other.z;
}

Vector3D Vector3D::cross(const Vector3D& other) const {
    return Vector3D(
        y * other.z - z * other.y,
        z * other.x - x * other.z,
        x * other.y - y * other.x
    );
}

// Otros métodos útiles
double Vector3D::norm2() const {
    return x * x + y * y + z * z;
}

double Vector3D::norm() const {
    return std::sqrt(norm2());
}

Vector3D Vector3D::normalized() const {
    double n = norm();
    if (n > 1e-9) { // Evitar división por cero con un umbral pequeño
        return Vector3D(x / n, y / n, z / n);
    }
    return Vector3D(0,0,0); // Devuelve vector cero si la norma es (casi) cero
}

// Sobrecarga del operador de inserción para imprimir
std::ostream& operator<<(std::ostream& os, const Vector3D& vec) {
    os << vec.x << " " << vec.y << " " << vec.z; // Formato más simple para archivos de datos
    // os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")"; // Formato original
    return os;
}
