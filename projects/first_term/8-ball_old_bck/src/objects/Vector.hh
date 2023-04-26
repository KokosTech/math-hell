#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "Point.hh"

class Vector {
   private:
    double x;
    double y;

   public:
    Vector();
    Vector(double x, double y);
    Vector(const Point& p1, const Point& p2);

    Vector& operator=(const Vector& other);

    double getX() const;
    double getY() const;

    void setX(double x);
    void setY(double y);

    Vector sum(const Vector& other) const;
    Vector times_num(double num) const;

    bool is_colinear(const Vector& other) const;
    bool is_orthogonal(const Vector& other) const;
    bool are_opposite(const Vector& other) const;

    double length() const;
    int dot_product(const Vector& other) const;

    friend class Line;
    friend std::ostream& operator<<(std::ostream& os, const Vector& c);
    friend std::istream& operator>>(std::istream& in, Vector& v);

    friend int area(const Vector v1, const Vector v2);

    ~Vector();
};

#endif  // VECTOR_HPP