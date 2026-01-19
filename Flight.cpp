#include "Flight.hpp"

Flight::Flight(std::string c, Airport d, Airport o, Plane p, int l, int a)
    :code(c), destination(d), origin(o), aircraft(p), liftoff(l), arrival(a) {}

Airport Flight::getdest() {
    return destination;
}

Airport Flight::getorigin(){
    return origin;
}

std::string Flight::getcode(){
    return code;
}

Plane Flight::getaircraft(){
    return aircraft;
}

int Flight::liftofftime(){
    return liftoff;
}

int Flight::landingtime(){
    return arrival;
}