// Vector3D.h
#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <iostream>

class Vector3D {
public:
    double x, y, z;

    // Constructores
    Vector3D(double x = 0, double y = 0, double z = 0);

    // Sobrecarga de operadores
    Vector3D operator+(const Vector3D& other) const;
    Vector3D operator-(const Vector3D& other) const;
    Vector3D operator*(double scalar) const;
    double dot(const Vector3D& other) const; // Producto punto
    Vector3D cross(const Vector3D& other) const; // Producto cruz

    // Otros métodos útiles
    double norm() const; // Magnitud del vector
    Vector3D normalized() const; // Vector unitario

    // Sobrecarga del operador de inserción para imprimir
    friend std::ostream& operator<<(std::ostream& os, const Vector3D& vec);
};

#endif // VECTOR3D_H
