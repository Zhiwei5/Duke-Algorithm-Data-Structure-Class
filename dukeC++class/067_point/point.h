
#ifndef __POINT_H__
#define __POINT_H__

#include <stdio.h>
#include <stdlib.h>

class Point
{
 private:
  double x;
  double y;

 public:
  Point();
  void move(double dx, double dy);
  double distanceFrom(const Point & p);
  ~Point() {}
};

#endif
