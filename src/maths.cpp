#include <cmath>

#include "maths.h"

/* If value exceeds maximum, returns max. If value below minimum, returns min.
 * Otherwise, returns num */
double clamp(double num, double min, double max) {
    if (num > max)
        return max;
    else if (num < min)
        return min;
    return num;
}

/* Returns num if it is greater than lim. Otherwise returns lim */
double noLessThan(double num, double lim) {
    if (num < lim) {
        return lim;
    }
    return num;
}

/* If number exceeds maximum or is below minimum, returns a rotated through value */
double rotateThrough(double num, double min, double max) {
    double newNum = std::fmod((num - min), (max - min)) - min;
    if (newNum < 0)
        return newNum + max - min;
    return newNum;
}

// Converts compass bearing to mathematical degrees
double bear2deg(double bearing) {
    double deg = 90 - bearing;
    if (deg < 0)
        deg += 360;
    else if (deg >= 360)
        deg -= 360;
    return deg;
}

// Converting degrees to radians
double deg2Rad(double deg) {
    return deg * pi / 180;
}

// Calculates distance between two points; d = sqrt((x2 - x1)^(2) + (y2 - y1)^(2))
double calcDist(double x1, double y1, double x2, double y2) {
    return std::sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

// Returns the displacement of a projectile that lands on the same height as from where it was shot
double lvlProjectileDispl(double iniVel, double angle) {
    double radAngle = deg2Rad(angle);
    // 2 * vnet^2 * sin(theta) * cos(theta) / g
    return std::abs(2 * (iniVel*iniVel) * std::sin(radAngle) * std::cos(radAngle) / g);
}
