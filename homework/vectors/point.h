#ifndef POINT_H
#define POINT_H

#include <fstream>
#include <cmath>

struct Point
{
    int x, y;
	
	Point() : x(0), y(0) {}
    Point(int x, int y) : x(x), y(y) {}
};

// this is for inputing a point
inline std::istream& operator>>(std::istream& in, Point& p) {
    in >> p.x;
    in >> p.y;
	
    return in;
}

// this is for printing a point
inline std::ostream& operator<<(std::ostream& out, Point& p) {
    out << "(" << p.x << ", " << p.y << ")";
    return out;
}

#endif