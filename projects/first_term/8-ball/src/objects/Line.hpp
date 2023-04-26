#ifndef LINE_HPP
#define LINE_HPP

#include "Vector.hpp"
#include "Point.hpp"

class Line {
   private:
    double A;
    double B;
    double C;

   public:
    Line(double A = 0, double B = 0, double C = 0);
    Line(const Point& p, const Vector& v);
    Line(const Point& p1, const Point& p2);
    Line(const Line& other);

    Line& operator&=(const Line& other);

    double get_A() const;
    double get_B() const;
    double get_C() const;

    void set_A(double A);
    void set_B(double B);
    void set_C(double C);

    bool are_parallel(const Line& other) const;
    bool is_orthogonal(const Line& other) const;
    Point get_intersection(const Line& other) const;

    Vector colinear() const;
    Vector orthogonal() const;

    Line parallel(const Point &p) const;
    Line orthogonal(const Point &p) const;

    double get_angle(const Line& other) const;

    friend std::ostream& operator<<(std::ostream& out, const Line& l);
    friend std::istream& operator>>(std::istream& in, Line& l);
    friend Point symmetric(const Point& point, const Line& line);

    ~Line();
};

#endif  // LINE_HPP