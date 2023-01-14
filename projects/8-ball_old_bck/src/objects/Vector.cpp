#include "Vector.hh"

#include <cmath>

#include "Line.hh"
#include "Point.hh"

// Constructors

Vector::Vector() : x(0.0), y(0.0) {}

Vector::Vector(double x, double y) : x(x), y(y) {}

Vector::Vector(const Point& p1, const Point& p2)
    : x(p1.getX() - p2.getX()), y(p1.getY() - p2.getY()) {}

// Operators

Vector& Vector::operator=(const Vector& other) {
    if (this != &other) {
        this->x = other.x;
        this->y = other.y;
    }
}

// Getters

double Vector::getX() const { return this->x; }

double Vector::getY() const { return this->y; }

// Setters

void Vector::setX(double x) { this->x = x; }

void Vector::setY(double y) { this->y = y; }

// Methods

Vector Vector::sum(const Vector& other) const {
    return Vector(this->x + other.x, this->y + other.y);
}

Vector Vector::times_num(double num) const {
    return Vector(this->x * num, this->y * num);
}

bool Vector::is_colinear(const Vector& other) const {
    return this->x * other.y == this->y * other.x;
}

bool Vector::is_orthogonal(const Vector& other) const {
    return this->x * other.x + this->y * other.y == 0;
}

bool Vector::are_opposite(const Vector& other) const {
    // check if the signs of the x and y components are different, if so then
    // the vectors are in opposite directions
    return (std::signbit(this->x) != std::signbit(other.x)) &&
           (std::signbit(this->y)) != std::signbit(other.y);
}

double Vector::length() const {
    if (std::abs(x) < 0.0000001 && std::abs(y) < 0.0000001) return NULL;

    return sqrt(x * x + y * y);
}

int Vector::dot_product(const Vector& other) const {
    return x * other.x + y * other.y;
}

// Friends

std::ostream& operator<<(std::ostream& os, const Vector& c) {
    os << "(" << c.x << ", " << c.y << ")";
    return os;
}

std::istream& operator>>(std::istream& in, Vector& v) {
    in >> v.x >> v.y;
    return in;
}

int area(const Vector v1, const Vector v2) { return v1.x * v2.y - v1.y * v2.x; }

// Destructor

Vector::~Vector() {}