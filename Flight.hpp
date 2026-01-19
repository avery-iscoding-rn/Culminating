#ifndef FLIGHT_HPP
#define FLIGHT_HPP

#include <iostream>
//#include <algorthim>
#include <string>
#include <vector>
#include <cmath>
#include <ctime>

#include "Plane.hpp"
#include "Airport.hpp"
#include "Point.hpp"

class Flight {
private:
    std::string code;
    Airport destination, origin;
    Plane aircraft;
    int liftoff, arrival;

public:
    Flight(std::string c, Airport d, Airport o, Plane p, int l, int a);//constructor;

    Point getPoint(Flight F, int timern); //returns location of the plane

    Airport getdest();
    Airport getorigin();
    std::string getcode();
    Plane getaircraft();
    int liftofftime();
    int landingtime();
};
#endif