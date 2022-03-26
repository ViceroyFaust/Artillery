#include <cmath>
#include <iostream>

/*
 * @Author DFOwl 2022
 */

double bear2deg(double bearing) {
    double deg = 90 - bearing;
    if (deg < 0)        deg + 360;
    else if (deg > 360) deg - 360;
    return deg;
}

double deg2Rad(double deg) {
    return deg * 3.1415 / 180;
}

class Coord {
private:
    double m_x;
    double m_y;
public:
    Coord(double x, double y) : m_x(x), m_y(y) {};
    double x() const {
        return m_x;
    }
    double y() const {
        return m_y;
    }

    friend std::ostream& operator<<(std::ostream& os, const Coord& c) {
        os << "(" << c.x() << ", " << c.y() << ")";
        return os;
    }
};

class Artillery {
private:
    double m_degHeading;
    double m_degElevation;
    int m_maxRotSpeed;
    int m_maxElevSpeed;

    double lvlGrndShotCalc(double shotVelocity) {
        double radElev = deg2Rad(m_degElevation);
        // 2 * vnet^2 * sin(theta) * cos(theta) / g
        return 2 * (shotVelocity*shotVelocity) * std::sin(radElev) * std::cos(radElev) / 9.81;
    }

    Coord shotLandingCalc(double distance) {
        double radHead = deg2Rad(m_degHeading);
        double x = distance * std::cos(radHead);
        double y = distance * std::sin(radHead);
        return Coord(x, y);
    }

public:
    Artillery(double degHeading, double degElevation, int maxRotSpeed, int maxElevSpeed)
        : m_degHeading(degHeading), m_degElevation(degElevation),
          m_maxRotSpeed(maxRotSpeed), m_maxElevSpeed(maxElevSpeed) {};
    Artillery(int maxRotSpeed, int maxElevSpeed)
        : Artillery(0.0, 45.0, maxRotSpeed, maxElevSpeed) {};

    void shoot(double shotVelocity) {
        double dist = lvlGrndShotCalc(shotVelocity);
        Coord shotCoord = shotLandingCalc(dist);
        std::cout << dist << " @ " << m_degHeading << std::endl;
        std::cout << "Shot landed at: " << shotCoord << "." << std::endl;
    }
};

int main() {
    Artillery art(30, 60, 10, 10);
    art.shoot(30);
    return 0;
}
