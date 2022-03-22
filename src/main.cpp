#include <iostream>

class Artillery {
private:
    double m_degHeading;
    double m_degElevation;
    int m_maxRotSpeed;
    int m_maxElevSpeed;
public:
    Artillery(double degHeading, double degElevation, int maxRotSpeed, int maxElevSpeed)
        : m_degHeading(degHeading), m_degElevation(degElevation),
          m_maxRotSpeed(maxRotSpeed), m_maxElevSpeed(maxElevSpeed) {};
    Artillery(int maxRotSpeed, int maxElevSpeed)
        : Artillery(0.0, 45.0, maxRotSpeed, maxElevSpeed) {};
};

int main() {
    std::cout << "Hello world!" << std::endl;
    return 0;
}
