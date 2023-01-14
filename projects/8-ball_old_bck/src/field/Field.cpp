#include "Field.hh"

#include <cmath>
#include <stdexcept>
#include <vector>

#include "../ball/Ball.hh"
#include "../objects/Line.hh"
#include "../objects/Point.hh"
#include "../objects/Vector.hh"

Field::Field()
    : ball(Point(0, 0), 0),
      starting_pos(0, 0),
      sinA(0),
      cosA(1),
      rotationPoint(0, 0) {
    this->set_end_points(Point(0, 0), Point(0, 0), Point(0, 0), Point(0, 0));
}

Field::Field(const Point& p1, const Point& p2, const Point& p3, const Point& p4,
             const Point& starting_pos, double ball_radius) {
    if (!this->is_valid_shape(p1, p2, p3, p4))
        throw std::invalid_argument("Invalid shape");

    get_rotation_angle(p1, p2);

    this->starting_pos = this->rotate_point(starting_pos);
    this->ball = Ball(this->starting_pos, ball_radius);

    this->get_rotated_end_points(p1, p2, p3, p4);

    if (!this->is_on_field(this->ball.getPos()))
        throw std::invalid_argument("Ball is not on the field");

    this->get_lines(this->end_points[0], this->end_points[1],
                    this->end_points[2], this->end_points[3]);
}

Field::Field(const Field& other)
    : ball(other.ball),
      starting_pos(other.starting_pos),
      sinA(other.sinA),
      cosA(other.cosA),
      rotationPoint(other.rotationPoint) {
    for (int i = 0; i < 4; ++i) {
        this->end_points[i] = other.end_points[i];
        this->lines[i] = other.lines[i];
    }
}

Field& Field::operator=(const Field& other) {
    if (this != &other) {
        this->ball = other.ball;
        this->starting_pos = other.starting_pos;
        this->sinA = other.sinA;
        this->cosA = other.cosA;
        this->rotationPoint = other.rotationPoint;

        for (int i = 0; i < 4; ++i) {
            this->end_points[i] = other.end_points[i];
            this->lines[i] = other.lines[i];
        }
    }

    return *this;
}

bool Field::is_valid_shape(const Point& p1, const Point& p2, const Point& p3,
                           const Point& p4) const {
    double AB = distance(p1, p2);
    double BC = distance(p2, p3);
    double CD = distance(p3, p4);
    double DA = distance(p4, p1);

    if (BC / AB != ASPECT_RATIO || DA / CD != ASPECT_RATIO) return false;

    double AC = distance(p1, p3);
    double BD = distance(p2, p4);

    return AB == CD && BC == DA && AC == BD;
}

void Field::get_rotation_angle(const Point& p1, const Point& p2) {
    Line ox(Point(0, 0), Point(1, 0));
    Line side(p1, p2);

    this->rotationPoint = side.get_intersection(ox);
    this->cosA = side.get_angle(ox);
    this->sinA = sqrt(1 - cosA * cosA);
}

Point Field::rotate_point(const Point& point) {
    Point rotated(cosA * (point.getX() - rotationPoint.getX()) +
                      sinA * (point.getY() - rotationPoint.getY()) +
                      rotationPoint.getX(),
                  -sinA * (point.getX() - rotationPoint.getX()) +
                      cosA * (point.getY() - rotationPoint.getY()) +
                      rotationPoint.getY());

    return std::isnan(rotated.getX()) && std::isnan(rotated.getY()) ? point
                                                                    : rotated;
}

Point Field::reverse_point(const Point& point) {
    Point reversed(cosA * (point.getX() - rotationPoint.getX()) -
                       sinA * (point.getY() - rotationPoint.getY()) +
                       rotationPoint.getX(),
                   sinA * (point.getX() - rotationPoint.getX()) +
                       cosA * (point.getY() - rotationPoint.getY()) +
                       rotationPoint.getY());

    // check if the point is valid
    return std::isnan(reversed.getX()) && std::isnan(reversed.getY())
               ? point
               : reversed;
}

Point Field::reverse_point(Point& point) {
    Point reversed(cosA * (point.getX() - rotationPoint.getX()) -
                       sinA * (point.getY() - rotationPoint.getY()) +
                       rotationPoint.getX(),
                   sinA * (point.getX() - rotationPoint.getX()) +
                       cosA * (point.getY() - rotationPoint.getY()) +
                       rotationPoint.getY());

    // check if the point is valid
    return std::isnan(reversed.getX()) && std::isnan(reversed.getY())
               ? point
               : reversed;
}

void Field::get_lines(const Point& p1, const Point& p2, const Point& p3,
                      const Point& p4) {
    lines[0] = Line(p1, p2);
    lines[1] = Line(p2, p3);
    lines[2] = Line(p3, p4);
    lines[3] = Line(p4, p1);
}

void Field::get_rotated_end_points(const Point& p1, const Point& p2,
                                   const Point& p3, const Point& p4) {
    double radius = this->ball.getRadius();

    this->end_points[0] = rotate_point(p1);
    this->end_points[0].setX(this->end_points[0].getX() + radius);
    this->end_points[0].setY(this->end_points[0].getY() + radius);

    this->end_points[1] = rotate_point(p2);
    this->end_points[1].setX(this->end_points[1].getX() - radius);
    this->end_points[1].setY(this->end_points[1].getY() + radius);

    this->end_points[2] = rotate_point(p3);
    this->end_points[2].setX(this->end_points[2].getX() - radius);
    this->end_points[2].setY(this->end_points[2].getY() - radius);

    this->end_points[3] = rotate_point(p4);
    this->end_points[3].setX(this->end_points[3].getX() + radius);
    this->end_points[3].setY(this->end_points[3].getY() - radius);
}

bool Field::is_on_field(const Point& point) const {
    double Sr = 0.5 * abs((end_points[0].getY() - end_points[2].getY()) *
                              (end_points[3].getX() - end_points[1].getX()) +
                          (end_points[1].getY() - end_points[3].getY()) *
                              (end_points[0].getX() - end_points[2].getX()));
    double Sabp =
        0.5 * abs(end_points[0].getX() * (end_points[1].getY() - point.getY()) +
                  end_points[1].getX() * (point.getY() - end_points[0].getY()) +
                  point.getX() * (end_points[0].getY() - end_points[1].getY()));
    double Sbcp =
        0.5 * abs(end_points[1].getX() * (end_points[2].getY() - point.getY()) +
                  end_points[2].getX() * (point.getY() - end_points[1].getY()) +
                  point.getX() * (end_points[1].getY() - end_points[2].getY()));
    double Scdp =
        0.5 * abs(end_points[2].getX() * (end_points[3].getY() - point.getY()) +
                  end_points[3].getX() * (point.getY() - end_points[2].getY()) +
                  point.getX() * (end_points[2].getY() - end_points[3].getY()));
    double Sdap =
        0.5 * abs(end_points[3].getX() * (end_points[0].getY() - point.getY()) +
                  end_points[0].getX() * (point.getY() - end_points[3].getY()) +
                  point.getX() * (end_points[3].getY() - end_points[0].getY()));

    if (Sr < Sabp + Sbcp + Scdp + Sdap) return false;

    return true;
}

bool Field::is_in_hole(const Point& pos) const {
    char count = 0;
    for (int i = 0; i < 4; i++) {
        if (lines[i].get_A() * pos.getX() + lines[i].get_B() * pos.getY() +
                lines[i].get_C() <
            0.0000001) {
            ++count;
        }
    }

    return count == 2;
}

std::pair<Vector, Line> Field::get_coll(const Vector& dir_vec) const {
    Line cross(ball.getPos(), dir_vec);
    std::vector<std::pair<Vector, Line> > pairs;

    for (int i = 0; i < 4; ++i) {
        Point inter = cross.get_intersection(lines[i]);
        Vector v(inter, ball.getPos());

        if (!dir_vec.are_opposite(v) && !std::isnan(inter.getX()) &&
            !std::isnan(inter.getY()) && v.length() != NULL) {
            pairs.push_back(std::make_pair(v, lines[i]));
        }
    }

    // find min vector length
    std::pair<Vector, Line> min = pairs[0];
    for (int i = 0; i < pairs.size(); ++i) {
        if (pairs[i].first.length() < min.first.length()) {
            min = pairs[i];
        }
    }

    return min;
}

void Field::set_end_points(const Point& p1, const Point& p2, const Point& p3,
                           const Point& p4) {
    Point prev_points[4];
    for (int i = 0; i < 4; ++i) prev_points[i] = this->end_points[i];

    Line prev_lines[4];
    for (int i = 0; i < 4; ++i) prev_lines[i] = this->lines[i];

    get_rotated_end_points(p1, p2, p3, p4);
    get_lines(p1, p2, p3, p4);

    if (!is_on_field(ball.getPos())) {
        for (int i = 0; i < 4; ++i) this->end_points[i] = prev_points[i];
        for (int i = 0; i < 4; ++i) this->lines[i] = prev_lines[i];
        throw std::invalid_argument("Ball is not on the field");
    }
}

void Field::set_starting_pos(const Point& pos) {
    Point rotated_pos = rotate_point(pos);

    if (!is_on_field(rotated_pos))
        throw std::invalid_argument("Starting position is not on the field");

    this->starting_pos = rotated_pos;
}

void Field::set_ball_radius(double radius) {
    if (radius < 0) throw std::invalid_argument("Radius cannot be negative");

    Point prev_points[4];
    for (int i = 0; i < 4; ++i) prev_points[i] = this->end_points[i];

    Line prev_lines[4];
    for (int i = 0; i < 4; ++i) prev_lines[i] = this->lines[i];

    double prev_radius = ball.getRadius();
    double diff = radius - prev_radius;

    ball.setRadius(radius);

    this->end_points[0].setX(this->end_points[0].getX() + diff);
    this->end_points[0].setY(this->end_points[0].getY() + diff);

    this->end_points[1].setX(this->end_points[1].getX() - diff);
    this->end_points[1].setY(this->end_points[1].getY() + diff);

    this->end_points[2].setX(this->end_points[2].getX() - diff);
    this->end_points[2].setY(this->end_points[2].getY() - diff);

    this->end_points[3].setX(this->end_points[3].getX() + diff);
    this->end_points[3].setY(this->end_points[3].getY() - diff);

    get_lines(this->end_points[0], this->end_points[1], this->end_points[2],
              this->end_points[3]);

    if (!is_valid_shape(this->end_points[0], this->end_points[1],
                        this->end_points[2], this->end_points[3])) {
        for (int i = 0; i < 4; ++i) this->end_points[i] = prev_points[i];
        for (int i = 0; i < 4; ++i) this->lines[i] = prev_lines[i];

        ball.setRadius(prev_radius);

        throw std::invalid_argument("Invalid shape");
    }
}

Point Field::get_curr_ball_pos() const { return reverse_point(ball.getPos()); }

double Field::get_ball_radius() const { return ball.getRadius(); }

Point Field::get_starting_pos() const { return reverse_point(starting_pos); }

Ball Field::get_ball() { return ball; }

void Field::reset_ball_pos() { ball.setPos(starting_pos); }

void Field::hit_ball(const Point& direction, double power) {
    if (power < 1 || power > 10)
        throw std::invalid_argument("Invalid power value range");

    Point rotated_dir = rotate_point(direction);
    Vector dir_vec(rotated_dir, ball.getPos());
    dir_vec.times_num(power);

    Point new_pos = ball.getPos();
    new_pos.setX(new_pos.getX() + dir_vec.getX());
    new_pos.setY(new_pos.getY() + dir_vec.getY());

    while (!is_on_field(new_pos)) {
        std::pair<Vector, Line> collision = get_coll(dir_vec);
        Vector coll_vec = collision.first;
        Line collisionSide = collision.second;
        Point collisionPoint = Point(coll_vec.getX() + ball.getPos().getX(),
                                     coll_vec.getY() + ball.getPos().getY());

        ball.setPos(collisionPoint);
        if (is_in_hole(ball.getPos())) {
            ball.setPos(starting_pos);
            std::cout << "Ball is in hole" << std::endl;
            return;
        }

        std::cout << "Ball bounces off at: " << reverse_point(ball.getPos())
                  << std::endl;
        new_pos = symmetric(new_pos, collisionSide);
        dir_vec = Vector(new_pos, ball.getPos());
    }
    ball.setPos(new_pos);
}

Field::~Field() {}