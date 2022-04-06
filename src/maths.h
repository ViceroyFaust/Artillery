#ifndef MATHS_H_INCLUDED
#define MATHS_H_INCLUDED

const double pi (3.1415926536);

/* If value exceeds maximum, returns max. If value below minimum, returns min.
 * Otherwise, returns num */
double clamp(double num, double min, double max);

/* Returns num if it is greater than lim. Otherwise returns lim */
double noLessThan(double num, double lim);

/* If number exceeds maximum or is below minimum, returns a rotated through value */
double rotateThrough(double num, double min, double max);

// Converts compass bearing to mathematical degrees
double bear2deg(double bearing);

// Converting degrees to radians
double deg2Rad(double deg);

// Calculates distance between two points; d = sqrt((x2 - x1)^(2) + (y2 - y1)^(2))
double calcDist(double x1, double y1, double x2, double y2);

#endif // MATHS_H_INCLUDED
