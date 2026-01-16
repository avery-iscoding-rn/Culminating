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
    std::vector<int> planes; //planes at the airport

public:
    Airport(std::string c, Point ll);//constructor
};