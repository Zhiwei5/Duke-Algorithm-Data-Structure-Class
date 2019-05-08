#include "point.h"

#include <math.h>

Point::Point() : x(0), y(0) {}

void Point::move(double dx, double dy) {
  x += dx;
  y += dy;
}

double Point::distanceFrom(const Point & p) {
  double distance_square = (x - p.x) * (x - p.x) + (y - p.y) * (y - p.y);
  return sqrt(distance_square);
}
