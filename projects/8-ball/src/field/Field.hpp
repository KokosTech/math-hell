#ifndef FIELD_HPP

#include "../ball/Ball.hpp"
#include "../objects/Line.hpp"
#include "../objects/Point.hpp"

#define ASPECT_RATIO 0.5  // 1:2 ratio

class Field {
   private:
    Ball ball;
    Point starting_pos;

    Point end_points[4];
    Line lines[4];

    double sinA, cosA;
    Point rotationPoint;

    bool is_valid_shape(const Point& p1, const Point& p2, const Point& p3,
                        const Point& p4) const;

    void get_rotation_angle(const Point& p1, const Point& p2);
    Point rotate_point(const Point& point);
    Point reverse_point(const Point& point);

    void get_lines(const Point& p1, const Point& p2, const Point& p3,
                   const Point& p4);
    void get_rotated_end_points(const Point& p1, const Point& p2,
                                const Point& p3, const Point& p4);

    bool is_on_field(const Point& point) const;
    bool is_in_hole(const Point& point) const;
    std::pair<Vector, Line> get_coll(const Vector& dirVec) const;

   public:
    Field();
    Field(const Point& p1, const Point& p2, const Point& p3, const Point& p4,
          const Point& starting_pos, double ball_radius);
    Field(const Field& other);

    Field& operator=(const Field& other);

    void set_end_points(const Point& p1, const Point& p2, const Point& p3,
                        const Point& p4);
    void set_starting_pos(const Point& starting_pos);
    void set_ball_radius(double radius);

    Point get_starting_pos();
    Point get_curr_ball_pos();
    double get_ball_radius() const;
    Ball get_ball();

    void hit_ball(const Point& direction, double power);
    void reset_ball_pos();

    friend std::ostream& operator<<(std::ostream& os, Field& field);
    friend std::istream& operator>>(std::istream& is, Field& field);

    ~Field();
};

#endif  // FIELD_HPP