// Vector3D.cpp
#include "Vector3D.h"
#include <cmath> // Para std::sqrt

// Constructores
Vector3D::Vector3D(double x, double y, double z) : x(x), y(y), z(z) {}

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
double Vector3D::norm() const {
    return std::sqrt(x * x + y * y + z * z);
}

Vector3D Vector3D::normalized() const {
    double n = norm();
    if (n > 0) { // Evitar división por cero
        return Vector3D(x / n, y / n, z / n);
    }
    return Vector3D(); // Devuelve vector cero si la norma es cero
}

// Sobrecarga del operador de inserción para imprimir
std::ostream& operator<<(std::ostream& os, const Vector3D& vec) {
    os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
    return os;
}
