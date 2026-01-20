#ifndef AIRPORT_HPP
#define AIRPORT_HPP

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <cmath>
#include "Point.hpp"
#include "Plane.hpp"

class Airport {
private:
    std::string name;
    std::string city;
    std::string code;
    Point coordinates;
public:
    Airport(std::string n, std::string cty, std::string c, Point loc);//constructor

    std::vector<Plane> planes; //planes at the airport

    std::string getname();
    std::string getcity();
    std::string getcode();
    Point getlocation();

    //adds plane to airport vector of planes (i.e. plane arrives at airport)
    void addplane(Plane p);
    //removes plane from airport vector of planes (i.e. plane leaves airport)
    void removeplane(Plane p);
    //prints all planes within an airport (prints "no planes" if empty)
    void printplanes();
    // RECURSION EXAMPLE //indexes planes array until plane is found or else -1 is returned
    int contains(Plane p, int i);
};
#endif