#include "Airport.hpp"

Airport::Airport(std::string n, std::string cty, std::string c, Point ll)
    :name(n), city(cty), code(c), coordinates(ll) {}

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