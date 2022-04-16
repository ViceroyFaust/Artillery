#ifndef GAMEOBJS_H_INCLUDED
#define GAMEOBJS_H_INCLUDED

#include <ostream>
#include "gameObjs.h"

// A standard coordinate point
struct Point {
    double x;
    double y;

    Point(double x, double y) : x(x), y(y) {};
    friend std::ostream& operator<<(std::ostream& os, const Point& p) {
        os << "(" << p.x << ", " << p.y << ")";
        return os;
    }
};

using idVal = unsigned int;
// A target to be shot by the player.
class Target {
private:
    Point m_pos;
    double m_radius;
    int m_hp;
    int m_points;
    idVal m_id;

public:
    // Constructs a target with a coordinate pos, hit radius, hitpoints, and points
    Target(Point pos, double radius, int hp, int points, idVal id);

    // Increments x and y based on input
    void changePos(double x, double y);

    // Increments health based on input
    void changeHP(int change);

    Point getPos() const { return m_pos; }

    double getRadius() const { return m_radius; }

    int getHP() const { return m_hp; }

    int getPoints() const { return m_points; }

    idVal getID() const { return m_id; }
};

#endif // GAMEOBJS_H_INCLUDED
