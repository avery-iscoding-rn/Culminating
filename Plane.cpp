#include "Plane.hpp"

Plane::Plane(std::string n, Point loc, bool f, int cp, int s)
    :name(n), coordinates(loc), flying(f), capacity(cp), speed(s) {}

std::string Plane::getmodel() {
    return name;
}

int Plane::getcapacity() {
    return capacity;
}

int Plane::getspeed() {
    return speed; //in K/M
}

bool Plane::status() {
    return flying; //if flying
}

void Plane::land() {
    flying = false;
}

void Plane::takeoff() {
    flying = true;
}