#include "gameObjs.h"
#include "maths.h"

// Constructs a target with a coordinate pos, hit radius, hitpoints, and points
Target::Target(Point pos, double radius, int hp, int points, idVal id)
    : m_pos(pos), m_radius(radius), m_hp(clamp(hp, 0, 100)), m_points(points), m_id(id) {};

// Increments x and y based on input
void Target::changePos(double x, double y) {
    m_pos.x += x;
    m_pos.y += y;
}

// Increments health based on input
void Target::changeHP(int change) {
    m_hp = clamp(m_hp + change, 0, 100);
}
