#include "Ball.hpp"

#include <cmath>
#include <istream>
#include <ostream>

#include "../objects/Point.hpp"

// Constructors

Ball::Ball() : pos(Point()), radius(0.0) {}

Ball::Ball(const Point& pos, double radius) : pos(pos), radius(radius) {}

Ball::Ball(const Ball& other) : pos(other.pos), radius(other.radius) {}

// Operators

Ball& Ball::operator=(const Ball& other) {
    if (this != &other) {
        this->pos = other.pos;
        radius = other.radius;
    }
}

// Getters

Point Ball::getPos() const { return this->pos; }

double Ball::getRadius() const { return this->radius / 2.0; }

// Setters

void Ball::setPos(const Point& pos) { this->pos = pos; }

void Ball::setRadius(double radius) { this->radius = radius * 2.0; }

// Friends

std::ostream& operator<<(std::ostream& os, const Ball& c) {
    os << "Ball(" << c.pos << ", " << c.radius << ")";
    return os;
}

std::istream& operator>>(std::istream& in, Ball& b) {
    in >> b.pos >> b.radius;
    return in;
}

// Destructor

Ball::~Ball() {}
