#include "Line.hh"

#include <cmath>
#include <iostream>
#include <istream>
#include <ostream>

#include "Point.hh"
#include "Vector.hh"

// Constructors

Line::Line(double A, double B, double C) : A(A), B(B), C(C) {}

Line::Line(const Point& p, const Vector& v) {
    this->A = v.y;
    this->B = -v.x;
    this->C = -(A * p.x + B * p.y);
}

Line::Line(const Point& p1, const Point& p2) {
    Vector v1(p1, p2);

    this->A = v1.y;
    this->B = -v1.x;
    this->C = -(A * p1.x + B * p1.y);
}

Line::Line(const Line& other) : A(other.A), B(other.B), C(other.C) {}

// Operators

Line& Line::operator&=(const Line& other) {
    this->A = other.A;
    this->B = other.B;
    this->C = other.C;

    return *this;
}

// Getters

double Line::get_A() const { return this->A; }

double Line::get_B() const { return this->B; }

double Line::get_C() const { return this->C; }

// Setters

void Line::set_A(double A) { this->A = A; }

void Line::set_B(double B) { this->B = B; }

void Line::set_C(double C) { this->C = C; }

// Methods

bool Line::are_parallel(const Line& other) const {
    return (this->A * other.B == this->B * other.A);
}

bool Line::is_orthogonal(const Line& other) const {
    return (((this->A * other.A) + (this->B * other.B)) == 0);
}

Point Line::get_intersection(const Line& other) const {
    double x = (this->B * other.C - this->C * other.B) /
               (this->A * other.B - this->B * other.A);
    double y = (this->C * other.A - this->A * other.C) /
               (this->A * other.B - this->B * other.A);

    return Point(x, y);
}

Vector Line::colinear() const { return Vector(-(this->B), this->A); }

Vector Line::orthogonal() const { return Vector(this->A, this->B); }

Line Line::parallel(const Point &p) const { return Line(p, this->colinear()); }

Line Line::orthogonal(const Point &p) const {
    return Line(p, this->orthogonal());
}

// Complex method

double Line::get_angle(const Line& other) const {
    double cos = ((this->A * other.A) + (this->B * other.B)) /
                 (sqrt(pow(this->A, 2) + pow(this->B, 2)) *
                  sqrt(other.A * other.A + other.B * other.B));

    return acos(cos);
}

// Friends

std::ostream& operator<<(std::ostream& out, const Line& l) {
    out << l.A << "x + " << l.B << "y + " << l.C << " = 0 ";
    return out;
}

std::istream& operator>>(std::istream& in, Line& l) {
    in >> l.A;
    in >> l.B;
    in >> l.C;
    return in;
}

// Destructor

Line::~Line() {}
