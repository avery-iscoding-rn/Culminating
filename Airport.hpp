#include <iostream>
//#include <algorthim>
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
    std::vector<Plane> planes; //planes at the airport
public:
    std::string getname();
    std::string getcity();
    std::string getcode();
    Point getlocation();
    Airport(std::string n, std::string cty, std::string c, Point loc);//constructor
    void addplane(Plane p);
    void removeplane(Plane p);
    void printplanes();
};