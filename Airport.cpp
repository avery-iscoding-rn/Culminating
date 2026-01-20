#include "Airport.hpp"
#include <iostream>

Airport::Airport(std::string n, std::string cty, std::string c, Point loc)
    :name(n), city(cty), code(c), coordinates(loc) {}

std::string Airport::getname() {
    return name;
}

std::string Airport::getcity() {
    return city;
}

std::string Airport::getcode() {
    return code;
}

Point Airport::getlocation(){
    return coordinates;
}
//adds plane to airport vector of planes (i.e. plane arrives at airport)
void Airport::addplane(Plane p) { //plane is at the airport, it is no longer flying (land makes flying bool = false)
    planes.push_back(p);
    p.land();
}


// RECURSION EXAMPLE 
//indexes planes array until plane is found or else -1 is returned
int Airport::contains(Plane p, int i) {
    if (i == planes.size()) {
        //std::cout << "\ngot to end of vector, plane not found";
        return -1;
    }
    if (planes[i].getmodel() == p.getmodel()) {
        //std::cout << "\nfound plane";
        return i;
    }
    //std::cout << "\n moving on to next plane";
    return contains(p, i+1);
}

//prints all planes within an airport (prints "no planes" if empty)
void Airport::printplanes() {
    if (!planes.empty()) {
        for (int i = 0; i < planes.size(); i++) {
            std::cout << planes[i].getmodel(); //prints the name of the plane
            if (i != planes.size()-1) {
                std::cout << ", ";
            }
        }
    } else {
        std::cout << "no planes";
    }
}

//removes plane from airport vector of planes (i.e. plane leaves airport)
void Airport::removeplane(Plane p) {
    if (!planes.empty()){ //if not empty
        std::vector<Plane> temp;
        for (int i = 0; i < planes.size(); i++) {
            if (!(planes[i] == p)) {
                temp.push_back(planes[i]);
            }
        }
        planes = temp;
        printplanes();
    }
}
