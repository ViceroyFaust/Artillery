#include <cmath>
#include <iostream>
#include <unordered_map>
#include <vector>


/*
 * @Author DFOwl 2022
 */

double bear2deg(double bearing) {
    double deg = 90 - bearing;
    if (deg < 0)
        deg += 360;
    else if (deg > 360)
        deg -= 360;
    return deg;
}

double deg2Rad(double deg) {
    return deg * 3.1415 / 180;
}

// d = sqrt((x2 - x1)^(2) + (y2 - y1)^(2))
double calcDist(double x1, double y1, double x2, double y2) {
    return std::sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

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

    void addTarget(const Target& toAdd) {
        targets.insert(std::pair<unsigned int, Target>(genTargetID(), toAdd));
    }

    void removeTarget(unsigned int idToRemove) {
        targets.erase(idToRemove);
    }

    void recordShot(const Point& c) {
        shots.push_back(c);
    }
};

class Artillery {
private:
    double m_degBearing;
    double m_degElevation;
    int m_maxRotSpeed;
    int m_maxElevSpeed;

    double calcLevelDistance(double shotVelocity) {
        double radElev = deg2Rad(m_degElevation);
        // 2 * vnet^2 * sin(theta) * cos(theta) / g
        return 2 * (shotVelocity*shotVelocity) * std::sin(radElev) * std::cos(radElev) / 9.81;
    }

public:
    Artillery(double degHeading, double degElevation, int maxRotSpeed, int maxElevSpeed)
        : m_degBearing(degHeading), m_degElevation(degElevation),
          m_maxRotSpeed(maxRotSpeed), m_maxElevSpeed(maxElevSpeed) {};
    Artillery(int maxRotSpeed, int maxElevSpeed)
        : Artillery(0.0, 45.0, maxRotSpeed, maxElevSpeed) {};

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
    Artillery art(200, 60, 10, 10); // Expected (-27.17, -74.66) as result
    art.shoot(30);
    return 0;
}
