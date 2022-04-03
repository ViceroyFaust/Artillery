#include <iostream>
#include <string>
#include <vector>

#include "cli.h"
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
    int m_hp;
    int m_points;

public:
    Target(Point pos, int radius, int hp, int points)
        : m_pos(pos), m_radius(radius), m_hp(clamp(hp, 0, 100)), m_points(points) {};

    bool doesThisHitMe(const Point& shot) {
        return calcDist(shot.m_x, shot.m_y, m_pos.m_x, m_pos.m_y) <= m_radius;
    }

    void changePos(double x, double y) {
        m_pos = Point(m_pos.m_x + x, m_pos.m_y + y);
    }

    void changeHP(int change) {
        m_hp = clamp(m_hp + change, 0, 100);
    }

    Point getPos() const {
        return m_pos;
    }

    double getRadius() const {
        return m_radius;
    }

    int getHP() const {
        return m_hp;
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
        : m_degBearing(rotateThrough(degHeading, 0, 360)), m_degElevation(clamp(degElevation, 0, 90)),
          m_maxRotSpeed(noLessThan(maxRotSpeed, 0)), m_maxElevSpeed(noLessThan(maxElevSpeed, 0)) {};
    Artillery(double maxRotSpeed, double maxElevSpeed)
        : Artillery(0.0, 0.0, maxRotSpeed, maxElevSpeed) {};

    void rotateBy(double degrees) {
        m_degBearing = rotateThrough(m_degBearing + degrees, 0, 360);
    }

    void changeElevBy(double degrees) {
        m_degElevation = clamp(m_degElevation + degrees, 0, 90);
    }

    double getBearing () const {
        return m_degBearing;
    }

    double getDegsElevation() const {
        return m_degElevation;
    }

    double getRotSpeed() const {
        return m_maxRotSpeed;
    }

    double getElevSpeed() const {
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

    void recordHits(const Point& shot) {
        unsigned int size = gameMap.getTargetAmt();
        for (unsigned int i = 0u; i < size; ++i) {
            Target t = gameMap.getTarget(i);
            if (t.getHP() > 0 && t.doesThisHitMe(shot)) {
                points += t.getPoints();
                t.changeHP(-100);
            }
        }
    }

public:
    Game(double maxRotSpeed, double maxElevSpeed)
        : points(0), gameMap(), art(maxRotSpeed, maxElevSpeed) {};

    void printInfo() const {
        std::cout << "All Info:" << std::endl;
        printArtBearing();
        printArtElevation();
        printRotSpeed();
        printElevSpeed();
        printPoints();
    }

    void printPoints() const {
        std::cout << "Points: " << points << std::endl;
    }

    void printArtBearing() const {
        std::cout << "Current Bearing: " << art.getBearing() << "°\n";
    }

    void printArtElevation() const {
        std::cout << "Current Elevation: " << art.getDegsElevation() << "°\n";
    }

    void printRotSpeed() const {
        std::cout << "Rotational speed: " << art.getRotSpeed() << "°/second\n";
    }

    void printElevSpeed() const {
        std::cout << "Elevation speed: " << art.getElevSpeed() << "°/second\n";
    }

};

int main() {
    std::string test = " \tThis,is,separated,by,commas\t            ";
    test = rightTrim(leftTrim(test));
    std::vector<std::string> words = splitStr(test, ",");
    for (std::string str : words) {
        std::cout << str << std::endl;
    }
    return 0;
}
