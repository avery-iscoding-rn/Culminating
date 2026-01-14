#include "Flight.hpp"

Flight::Flight(std::string c, Airport d, Airport o, Plane p, int l, int a)
    :code(c), destination(d), origin(o), aircraft(p), liftoff(l), arrival(a) {}