#ifndef FLIGHT_HPP
#define FLIGHT_HPP

#include <iostream>
#include <algorithm>
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
    Airport* destination;
    Airport* origin;
    Plane* aircraft;
    double liftoff, arrival;

public:
    Flight(std::string c, Airport& d, Airport& o, Plane& p, double l, double a);//constructor;

    //finds current location of a plane en route between two different airport depending on the current time
    Point getPoint(int timern); 
    //returns location of the plane in point (lat and long)

    Airport& getdest();
    Airport& getorigin();
    std::string getcode();
    Plane& getaircraft();
    double liftofftime();
    double landingtime();

    // void fly(bool rweflying, int timern);
    bool atorigin(Point mycoordinates);
    bool atdest(Point mycoordinates);

    //overriding < operator so we can compare flights and sort them in a vector (according to departure time)
    bool operator<(const Flight& other) const;

};

struct coordinates;

#endif