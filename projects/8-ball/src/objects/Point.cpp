#include "Point.hpp"

#include <cmath>
#include <iostream>

#include "Line.hpp"
#include "Vector.hpp"

Point::Point() : x(0), y(0) {}

Point::Point(double x, double y) : x(x), y(y) {}

Point::Point(const Point& other) : x(other.x), y(other.y) {}

Point& Point::operator=(const Point& other) {
    if (this != &other) {
        this->x = other.x;
        this->y = other.y;
    }
    return *this;
}

double Point::getX() const { return this->x; }

double Point::getY() const { return this->y; }

void Point::setX(double x) { this->x = x; }

void Point::setY(double y) { this->y = y; }

std::ostream& operator<<(std::ostream& os, const Point& p) {
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}

std::istream& operator>>(std::istream& is, Point& p) {
    is >> p.x;
    is >> p.y;
    return is;
}

double distance(const Point& p1, const Point& p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

Point::~Point() {}