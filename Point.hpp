#include <iostream>
#include <algorthim>
#include <string>
#include <vector>
#include <cmath>

class Point {
private:
    int longitude, latitiude;
public:
    Point(int L, int l);
    int getdistance(Point p1, Point p2);//in KM
}