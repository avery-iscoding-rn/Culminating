#ifndef PLANE_HPP
#define PLANE_HPP

#include <iostream>
//#include <algorithm>
#include <string>
#include <vector>
#include <cmath>

class Point {
private:
    int longitude, latitude;
public:
    Point(int L, int l);
    int getdistance(Point p1, Point p2);//in KM
};
#endif