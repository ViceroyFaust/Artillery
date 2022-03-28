#include <cmath>
#include <iostream>
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

class Pos {
public:
    double m_x;
    double m_y;
    Pos(double x, double y) : m_x(x), m_y(y) {};

    friend std::ostream& operator<<(std::ostream& os, const Pos& c) {
        os << "(" << c.m_x << ", " << c.m_y << ")";
        return os;
    }
};

class WorldMap {
private:
    std::vector<Pos> shots;
public:
    WorldMap() : shots() {};

    void recordShot(const Pos& c) {
        shots.push_back(c);
    }
};

class Artillery {
private:
    double m_degBearing;
    double m_degElevation;
    int m_maxRotSpeed;
    int m_maxElevSpeed;

    double lvlGrndShotCalc(double shotVelocity) {
        double radElev = deg2Rad(m_degElevation);
        // 2 * vnet^2 * sin(theta) * cos(theta) / g
        return 2 * (shotVelocity*shotVelocity) * std::sin(radElev) * std::cos(radElev) / 9.81;
    }

    Pos shotLandingCalc(double distance) {
        // Convert the bearing to trig degrees for math to be right
        // Further, convert degrees to radians as that's what cmath uses
        double radHead = deg2Rad(bear2deg(m_degBearing));
        double x = distance * std::cos(radHead);
        double y = distance * std::sin(radHead);
        return Pos(x, y);
    }

public:
    Artillery(double degHeading, double degElevation, int maxRotSpeed, int maxElevSpeed)
        : m_degBearing(degHeading), m_degElevation(degElevation),
          m_maxRotSpeed(maxRotSpeed), m_maxElevSpeed(maxElevSpeed) {};
    Artillery(int maxRotSpeed, int maxElevSpeed)
        : Artillery(0.0, 45.0, maxRotSpeed, maxElevSpeed) {};

    void shoot(double shotVelocity) {
        double dist = lvlGrndShotCalc(shotVelocity);
        Pos shotCoord = shotLandingCalc(dist);
        std::cout << dist << " @ " << m_degBearing << std::endl;
        std::cout << "Shot landed at: " << shotCoord << "." << std::endl;
    }
};

int main() {
    Artillery art(200, 60, 10, 10); // Expected (-27.17, -74.66) as result
    art.shoot(30);
    return 0;
}
