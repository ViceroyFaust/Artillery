#include <iostream>
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
    Point getPos() const {
        return m_pos;
    }
    double getRadius() const {
        return m_radius;
    }
    int getPoints() const {
        return m_points;
    }
};

class World {
private:
    std::vector<Point> shots;
    std::vector<Target> targets;

    unsigned int genTargetID() {
        static unsigned int s_id{0};
        return s_id++;
    }

public:
    World() : shots(), targets() {};

    void recordShot(const Point& c) {
        shots.push_back(c);
    }

    void addTarget(const Target& toAdd) {
        targets.push_back(toAdd);
    }

    void removeTarget(unsigned int index) {
        targets.erase(targets.begin() + index);
    }

    unsigned int getTargetAmt() {
        return targets.size();
    }

    Target getTarget(unsigned int index) {
        return targets[index];
    }

    unsigned int getShotsAmt() {
        return shots.size();
    }

    Point getShot(unsigned int index) {
        return shots[index];
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

class Game {
private:
    int points;
    World gameMap;
    Artillery art;

    bool checkCollision(const Point& shot, const Target& target) {
        return calcDist(shot.m_x, shot.m_y, target.getPos().m_x, target.getPos().m_y) <= target.getRadius();
    }

public:
    Game() : points(0), gameMap(), art(15, 2) {};

    void printPoints() {
        std::cout << "Points: " << points << std::endl;
    }

    void printArtBearing() {
        std::cout << "Current Bearing: " << art.getBearing() << "°\n";
    }

    void printArtElevation() {
        std::cout << "Current Elevation: " << art.getDegsElevation() << "°\n";
    }

    void printRotSpeed() {
        std::cout << "Rotational speed: " << art.getRotSpeed() << "°/second\n";
    }

    void printElevSpeed() {
        std::cout << "Elevation speed: " << art.getElevSpeed() << "°/second\n";
    }

};

int main() {
    World gameMap;
    Artillery art(10, 2);
    art.rotateBy(345);
    art.changeElevBy(33);
    std::cout << "Shot landed @ " << art.shoot(100) << std::endl; // (-241.02, 899.51)

    return 0;
}
