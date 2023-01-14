#ifndef BALL_HPP
#define BALL_HPP

#include "../objects/Point.hpp"

class Ball {
    private:
        Point pos;
        double radius;
    public:
        Ball();
        Ball(const Point& pos, double radius);
        Ball(const Ball& other);
        
        Ball& operator=(const Ball& other);

        Point getPos() const;
        double getRadius() const;

        void setPos(const Point& pos);
        void setRadius(double radius);

        friend std::ostream& operator<<(std::ostream& os, const Ball& c);
        friend std::istream& operator>>(std::istream& in, Ball& b);

        ~Ball();
};

#endif  // BALL_HPP