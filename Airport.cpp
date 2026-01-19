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
//removes plane from airport vector of planes (i.e. plane leaves airport)
void Airport::removeplane(Plane p) {
    std::vector<Plane> temp;
    for (int i = 0; i < planes.size(); i++) { //create a new vector, duplicates planes except for the one we're deleting
        if (planes[i].getcapacity() != p.getcapacity()) { //each plane has a unique capacity so comparing them works well
            temp.push_back(planes[i]);
        }
    }
    planes = temp; //turn planes into the temp --> target plane has been deleted
    p.takeoff(); //bool == true (flying) becuase its leaving the airport
}

// RECURSION EXAMPLE //indexes planes array until plane is found or else false is returned
bool Airport::contains(Plane p, int i) {
    if (i == planes.size()-1) {
        return false;
    }
    if (planes[i].getmodel() == p.getmodel()) {
        return true;
    }
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

