#include "gameObjs.h"
#include "maths.h"

Target::Target(Point pos, int radius, int hp, int points)
    : m_pos(pos), m_radius(radius), m_hp(clamp(hp, 0, 100)), m_points(points) {};

bool Target::doesThisHitMe(const Point& shot) {
    return calcDist(shot.x, shot.y, m_pos.x, m_pos.y) <= m_radius;
}

void Target::changePos(double x, double y) {
    m_pos.x += x;
    m_pos.y += y;
}

void Target::changeHP(int change) {
    m_hp = clamp(m_hp + change, 0, 100);
}
