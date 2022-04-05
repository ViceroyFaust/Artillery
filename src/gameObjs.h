#ifndef GAMEOBJS_H_INCLUDED
#define GAMEOBJS_H_INCLUDED

#include <ostream>
#include "gameObjs.h"

class Point {
public:
    double x;
    double y;
    Point(double x, double y) : x(x), y(y) {};

    friend std::ostream& operator<<(std::ostream& os, const Point& p) {
        os << "(" << p.x << ", " << p.y << ")";
        return os;
    }
};

class Target {
private:
    Point m_pos;
    double m_radius;
    int m_hp;
    int m_points;

public:
    Target(Point pos, int radius, int hp, int points);

    bool doesThisHitMe(const Point& shot);

    void changePos(double x, double y);

    void changeHP(int change);

    Point getPos() const { return m_pos; }

    double getRadius() const { return m_radius; }

    int getHP() const { return m_hp; }

    int getPoints() const { return m_points; }
};

#endif // GAMEOBJS_H_INCLUDED
