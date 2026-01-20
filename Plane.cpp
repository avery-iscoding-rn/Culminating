#include "Plane.hpp"

Plane::Plane(std::string n, Point loc, bool f, int cp, int s)
    :name(n), coordinates(loc), flying(f), capacity(cp), speed(s) {}

std::string Plane::getmodel() {
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

//switches status to false, as plane is no longer flying
void Plane::land() {
    flying = false;
}
//switches status to true, as plane is no longer flying
void Plane::takeoff() {
    flying = true;
}