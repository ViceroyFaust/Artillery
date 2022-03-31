#ifndef MATHS_H_INCLUDED
#define MATHS_H_INCLUDED

#include <cmath>

const double pi (3.1415926536);

double clamp(double num, double min, double max);

double noLessThan(double num, double lim);

double rotateThrough(double num, double min, double max);

double bear2deg(double bearing);

double deg2Rad(double deg);

double calcDist(double x1, double y1, double x2, double y2);

#endif // MATHS_H_INCLUDED
