#ifndef POINT_HPP
#define POINT_HPP

#include <iostream>
//#include <algorithm>
#include <string>
#include <vector>
#include <cmath>

class Point {
private:
    int longitude, latitude;
public:
    Point(int l, int L);
    int getdistance(Point p1, Point p2);//in KM
};
#endif