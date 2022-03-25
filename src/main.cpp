#include <cmath>
#include <iostream>

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
        std::cout << lvlGrndShotCalc(shotVelocity) << std::endl;
    }
};

int main() {
    Artillery art(0, 60, 10, 10);
    art.shoot(30);
    return 0;
}
