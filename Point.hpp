#ifndef POINT_HPP
#define POINT_HPP

#include <iostream>
//#include <algorithm>
#include <string>
#include <vector>
#include <cmath>

class Point {
private:
    double longitude, latitude;
public:
    Point(double l, double L);
    //calculates distance between two points, taking into account the curve of earth's surface
    static double getdistance(const Point& p1, const Point& p2); //in KM
    double getlat();
    double getlong();
};
#endif