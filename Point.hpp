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
    static double getdistance(const Point& p1, const Point& p2); //in KM
    double getlat();
    double getlong();
};
#endif