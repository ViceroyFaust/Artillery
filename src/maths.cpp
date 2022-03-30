#include "maths.h"

double clamp(double num, double min, double max) {
    if (num > max)
        return max;
    else if (num < min)
        return min;
    return num;
}

double noLessThan(double num, double lim) {
    if (num < lim) {
        return lim;
    }
    return num;
}

double rotateThrough(double num, double min, double max) {
    if (num > max)
        return num - max;
    else if (num < min)
        return num + max;
    return num;
}

double bear2deg(double bearing) {
    double deg = 90 - bearing;
    if (deg < 0)
        deg += 360;
    else if (deg > 360)
        deg -= 360;
    return deg;
}

double deg2Rad(double deg) {
    return deg * pi / 180;
}

// d = sqrt((x2 - x1)^(2) + (y2 - y1)^(2))
double calcDist(double x1, double y1, double x2, double y2) {
    return std::sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}
