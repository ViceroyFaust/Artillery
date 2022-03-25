#include <cmath>
#include <iostream>

/*
 * @Author DFOwl 2022
 */

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
        double elevDeg2Rad = m_degElevation * 3.1415 / 180;
        // 2 * vnet^2 * sin(theta) * cos(theta) / g
        return 2 * (shotVelocity*shotVelocity) * std::sin(elevDeg2Rad) * std::cos(elevDeg2Rad) / 9.81;
    }

public:
    Artillery(double degHeading, double degElevation, int maxRotSpeed, int maxElevSpeed)
        : m_degHeading(degHeading), m_degElevation(degElevation),
          m_maxRotSpeed(maxRotSpeed), m_maxElevSpeed(maxElevSpeed) {};
    Artillery(int maxRotSpeed, int maxElevSpeed)
        : Artillery(0.0, 45.0, maxRotSpeed, maxElevSpeed) {};

    void shoot(double shotVelocity) {
        std::cout << lvlGrndShotCalc(shotVelocity) << " @ " << m_degHeading << std::endl;
    }
};

int main() {
    Coord coord(6, 36);
    std::cout << coord;
    return 0;
}
