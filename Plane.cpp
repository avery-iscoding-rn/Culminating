#include "Plane.hpp"


Plane::Plane(std::string n, Point loc, bool f, int cp, int s, int fn)
    :name(n), coordinates(loc), flying(f), capacity(cp), speed(s),flightnum(fn) {}

std::string Plane::getmodel() const {
    return name;
}


Point Plane::getcoordinates(){
    return coordinates;
}

int Plane::getcapacity() {
    return capacity;
}

int Plane::getspeed() {
    return speed; //in K/M
}

//returns true if plane is flying, false if plane is not
bool Plane::status() {
    return flying; //if flying
}

//set coordinates
    void Plane::setcoordinates(Point p) {
        coordinates = p;
    }

//switches status to false, as plane is no longer flying
void Plane::land() {
    flying = false;
}
//switches status to true, as plane is no longer flying
void Plane::takeoff() {
    flying = true;
}
//OVERRIDES == OPERATOR
//overrides == operator to allow to planes to be compared via their model
bool Plane::operator==(const Plane& other) const {
    return this->getmodel() == other.getmodel();
    //overrides == to compare their model
}
