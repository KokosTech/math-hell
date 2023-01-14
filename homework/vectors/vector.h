#ifndef VECTOR_H
#define VECTOR_H
#include "point.h"

class Vector {
    int x, y;

public:
    Vector() : x(0), y(0) {}
    Vector(int x, int y) : x(x), y(y) {}
    Vector(const Point p1, const Point p2);

    Vector sum(const Vector& other) const;
    Vector times_num(int num) const;

    bool is_colinear(const Vector& other) const;
    double length() const;
    int dot_product(const Vector& other) const;

    friend class Line;
    friend std::ostream& operator<<(std::ostream& os, const Vector& c);
    friend std::istream& operator>>(std::istream& in, Vector& v);
};

int area(const Vector v1, const Vector v2);

inline std::ostream& operator<<(std::ostream& out, const Vector& v) 
{
    out << "(" << v.x << ", " << v.y << ")";
    return out;
}

inline std::istream& operator>>(std::istream& in, Vector& v) 
{
    in >> v.x;
    in >> v.y;
	return in;
}

#endif