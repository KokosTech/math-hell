#include "vector.h"

// TODO - constructs vector from 2 points
Vector::Vector(const Point p1, const Point p2) {
    this->x = p2.x - p1.x;
    this->y = p2.y - p1.y;
}

// TODO - returns the sum of two vectors (which is also e vector)
Vector Vector::sum(const Vector& other) const {
    return Vector(other.x + this->x, other.y + this->y);
}

// TODO - returns the product of a vector and a number (which is also e vector)
Vector Vector::times_num(int num) const {
    return Vector(this->x * num, this->y * num);
}

// TODO - returns a boolean value, answering the question whether the current 
// vector and another ("other") are collinear
bool Vector::is_colinear(const Vector& other) const {
    return this->x * other.y == this->y * other.x;
}

// TODO - returns the length of the current vector
double Vector::length() const {
    return sqrt(pow(this->x, 2) + pow(this->y, 2));
}

// TODO - returns the dot(scalar) product of the current vector and another
int Vector::dot_product(const Vector& other) const {
    return (this->x * other.x) + (this->y * other.y); 
}

// TODO - finds the area of a triangle given two vectors denoting two of its sides
int area(const Vector v1, const Vector v2) {
    double a = v1.length();
    double b = v2.length();
    double c = (v1.sum(v2)).length();
    double p = (a + b + c) / 2.0;

    return sqrt(p * (p - a) * (p - b) * (p - c));
}
