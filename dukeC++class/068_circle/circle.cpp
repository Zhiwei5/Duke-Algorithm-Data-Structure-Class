#include "circle.h"

#include <math.h>
#include <stdlib.h>

#include <algorithm>

Circle::Circle(const Point & p, double r) : center(p), radius(r) {}

void Circle::move(double dx, double dy) {
  center.move(dx, dy);
}

double Circle::intersectionArea(const Circle & otherCircle) {
  double distance = center.distanceFrom(otherCircle.center);
  if (distance >= radius + otherCircle.radius) {
    return 0;
  }
  else {
    if (distance <= abs(radius - otherCircle.radius)) {
      double min_r = std::min(radius, otherCircle.radius);
      return min_r * min_r * M_PI;
    }

    double a = radius * radius;
    double b = otherCircle.radius * otherCircle.radius;
    double distanceSq = distance * distance;
    double d1 = (a - b + distanceSq) / (2 * distance);
    double d2 = (b - a + distanceSq) / (2 * distance);

    if (distance <= abs(radius - otherCircle.radius)) {
      double min_r = std::min(radius, otherCircle.radius);
      return min_r * min_r * M_PI;
    }

    return a * acos(d1 / radius) - d1 * sqrt(a - d1 * d1) + b * acos(d2 / otherCircle.radius) -
           d2 * sqrt(b - d2 * d2);
  }
}
