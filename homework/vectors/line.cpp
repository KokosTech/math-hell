#include "line.h"

// TODO - constructs a line given a point and a vector
Line::Line(const Point p, const Vector& v) {
    this->A = v.y;
    this->B = -v.x;
    this->C = -(A * p.x + B * p.y);
}

// TODO - constructs a line given two points
Line::Line(const Point p1, const Point p2) {
    Vector v1(p1, p2);

    this->A = v1.y;
    this->B = -v1.x;
    this->C = -(A * p1.x + B * p1.y);
}

// TODO - checks if two lines a parallel to eachother
bool Line::are_parallel(const Line& other) const {
    return (this->A * other.B == this->B * other.A);
}

// TODO - checks if two lines are orthogonal (perpendicular)
bool Line::is_orthogonal(const Line& other) const {
    return (((this->A * other.A) + (this->B * other.B)) == 0);
}

// TODO - returns the vector that is colinear to the line
Vector Line::colinear() const {
    return Vector(-(this->B), this->A);
}

// TODO - returns the vector that is orthogonal to the line
Vector Line::orthogonal() const {
    return Vector(this->A, this->B);
}

// TODO - returns a line, passing through the point p, that is parallel to the line
Line Line::parallel(const Point p) const {
    return Line(p, this->colinear());
}

// TODO - returns a line, passing through the point p, that is orthogonal to the line
Line Line::orthogonal(const Point p) const {
    return Line(p, this->orthogonal());
}