#include <cmath>
#include <iostream>
#include <unordered_map>
#include <vector>

#include "maths.h"

/*
 * @Author DFOwl 2022
 */

class Point {
public:
    double m_x;
    double m_y;
    Point(double x, double y) : m_x(x), m_y(y) {};

    friend std::ostream& operator<<(std::ostream& os, const Point& p) {
        os << "(" << p.m_x << ", " << p.m_y << ")";
        return os;
    }
};

class Target {
private:
    Point m_pos;
    double m_radius;
    int m_points;

public:
    Target(Point pos, int radius, int points)
        : m_pos(pos), m_radius(radius), m_points(points) {};
    Point getPos() {
        return m_pos;
    }
    double getRadius() {
        return m_radius;
    }
    int getPoints() {
        return m_points;
    }
};

class WorldMap {
private:
    std::vector<Point> shots;
    std::unordered_map<unsigned int, Target> targets;

    unsigned int genTargetID() {
        static unsigned int s_id{0};
        return s_id++;
    }

public:
    WorldMap() : shots(), targets() {};

    void recordShot(const Point& c) {
        shots.push_back(c);
    }

    void addTarget(const Target& toAdd) {
        targets.insert(std::pair<unsigned int, Target>(genTargetID(), toAdd));
    }

    void removeTarget(unsigned int idToRemove) {
        targets.erase(idToRemove);
    }

    std::vector<Point> getShots() {
        return shots;
    }

    std::unordered_map<unsigned int, Target> getTargets() {
        return targets;
    }

};

class Artillery {
private:
    double m_degBearing;
    double m_degElevation;
    double m_maxRotSpeed;
    double m_maxElevSpeed;

    double calcLevelDistance(double shotVelocity) {
        double radElev = deg2Rad(m_degElevation);
        // 2 * vnet^2 * sin(theta) * cos(theta) / g
        return std::abs(2 * (shotVelocity*shotVelocity) * std::sin(radElev) * std::cos(radElev) / 9.81);
    }

public:
    Artillery(double degHeading, double degElevation, double maxRotSpeed, double maxElevSpeed)
        : m_degBearing(degHeading), m_degElevation(degElevation),
          m_maxRotSpeed(maxRotSpeed), m_maxElevSpeed(maxElevSpeed) {};
    Artillery(double maxRotSpeed, double maxElevSpeed)
        : Artillery(0.0, 0.0, maxRotSpeed, maxElevSpeed) {};

    void rotateBy(double degrees) {
        m_degBearing = rotateThrough(m_degBearing + degrees, 0, 360);
    }

    void changeElevBy(double degrees) {
        m_degElevation = clamp(m_degElevation + degrees, 0, 90);
    }

    double getBearing () {
        return m_degBearing;
    }

    double getDegsElevation() {
        return m_degElevation;
    }

    double getRotSpeed() {
        return m_maxRotSpeed;
    }

    double getElevSpeed() {
        return m_maxElevSpeed;
    }

    Point shoot(double shotVelocity) {
        double distance = calcLevelDistance(shotVelocity);
        // Convert the bearing to trig degrees for math to be right
        // Further, convert degrees to radians as that's what cmath uses
        double radHead = deg2Rad(bear2deg(m_degBearing));
        double x = distance * std::cos(radHead);
        double y = distance * std::sin(radHead);
        return Point(x, y);
    }
};

int main() {
    WorldMap gameMap;
    Artillery art(10, 2);
    art.rotateBy(345);
    art.changeElevBy(33);
    std::cout << "Shot landed @ " << art.shoot(100) << std::endl; // (-241.02, 899.51)

    return 0;
}
