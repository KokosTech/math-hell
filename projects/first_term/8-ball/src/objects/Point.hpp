#ifndef POINT_HPP
#define POINT_HPP

#include <iostream>
#include <istream>
#include <ostream>

class Point {
   private:
    double x;
    double y;

   public:
    Point();
    Point(double x, double y);
    Point(const Point& other);

    Point& operator=(const Point& other);

    double getX() const;
    double getY() const;

    void setX(double x);
    void setY(double y);

    friend std::ostream& operator<<(std::ostream& os, const Point& p);
    friend std::istream& operator>>(std::istream& is, Point& p);
    friend double distance(const Point& p1, const Point& p2);

    ~Point();
};

#endif  // POINT_HPP