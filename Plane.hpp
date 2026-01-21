#ifndef PLANE_HPP
#define PLANE_HPP


#include <iostream>
#include <algorithm>
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
    Plane(std::string n, Point loc, bool f, int cp, int s, int fn);
    int flightnum; //current flight number
    std::string getmodel() const;
    //returns true if plane is flying, false if plane is not
    bool status();
    int getcapacity();
    int getspeed();
    Point getcoordinates();
     //switches status to false, as plane is no longer flying
    void land();
    //switches status to true, as plane is no longer flying
    void takeoff();
    
    bool operator==(const Plane& other) const;
};
#endif