#include "Airport.hpp"

Airport::Airport(std::string n, std::string cty, std::string c, Point ll)
    :name(n), city(cty), code(c), coordinates(ll) {}

Airport::getname() {
    return name;
}

Airport::getcity() {
    return city;
}

Airport::getcode() {
    return code;
}

Airport::getlocation(){
    return coordinates;
}