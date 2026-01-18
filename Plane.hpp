#ifndef PLANE_HPP
#define PLANE_HPP


#include <iostream>
//#include <algorthim>
#include <string>
#include <vector>
#include <cmath>
#include "Point.hpp"

class Plane {
private:
    std::string name;
    Point coordinates;
    bool flying;
    int capacity, speed;
public:
    Plane(std::string n, Point loc, bool f, int cp, int s);
    std::string getmodel();
    bool status(); //get flying 
    int getcapacity();
    int getspeed();

    void land();
    void takeoff();
    
};
#endif