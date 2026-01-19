#include "Flight.hpp"

Flight::Flight(std::string c, Airport d, Airport o, Plane p, int l, int a)
    :code(c), destination(d), origin(o), aircraft(p), liftoff(l), arrival(a) {}

struct coordinates {
    double x;
    double y;
    double z;
}; // longitude and latitude angles must be converted to an [x,y,z] vector

Flight::getPoint(Flight F, int timern){

    int R = 6371; // earth's radius

    double φ = F.origin.coordinates.latitude * M_PI / 180;
    double λ = F.origin.coordinates.longitude* M_PI / 180;
    // Converting degrees to radians

    double xO = cos(φ) * cos(λ);
    double yO = cos(φ) * sin(λ);
    double zO = sin(φ);
    // Using degrees in radians to a vector (origin)

    double φ2 = F.getdest().getlocation().getlat()* M_PI / 180;
    double λ2 = F.getdest().getlocation().getlong()* M_PI / 180;
    // Converting degrees to radians

    double xD = cos(φ2) * cos(λ2);
    double yD = cos(φ2) * sin(λ2);
    double zD = sin(φ2);

    double angle = std::acos((xO*xD)+(yO*yD)+(zO*zD));
    double surfacedistance = R * angle;

    double distance = getdistance(F.destination.coordinates, F.origin.coordinates);
    // not needed (?)

    double Distancetravelled = Flight.aircraft.speed * (timern - F.liftoff);
    //Velocity (km/h) x time spent = distance travelled

    double t = Distancetravelled/surfacedistance;
    // Factor by which you need to multiply the unit vector [x,y,z] because that is just a ratio, not an exact distance

    if (t > 1){
        t = .999;
    }
    // coordinates currentPoint = {xO + (percentofFlight*resultant.x),  yO + (percentofFlight*resultant.y), zO + (percentofFlight*resultant.z)};

    // Spherical linear interpolation
    // Don't really know how this works tbh
    coordinates currentPoint {
        (sin((1-t)*angle) / sin(angle) * xO + sin (t*angle) / sin(angle) * xD),
        (sin((1-t)*angle) / sin(angle) * yO + sin (t*angle) / sin(angle) * yD),
        (sin((1-t)*angle) / sin(angle) * zO + sin (t*angle) / sin(angle) * zD),
    };


    double len = sqrt(currentPoint.x*currentPoint.x + currentPoint.y*currentPoint.y + currentPoint.z*currentPoint.z);
    // Resultant magnitude (Length of vector)

    if (len != 0) {
        // can't be 0

        currentPoint.x = currentPoint.x / len;
        currentPoint.y = currentPoint.y /len;
        currentPoint.z = currentPoint.z /len;
        // Divide it back by length to get unit vector of length 1 (?) before converting back to radians 
    }

    double A = std::atan2(currentPoint.z,(std::sqrt(std::pow(currentPoint.x,2)+(std::pow(currentPoint.y,2))))); //latitdude, radians
    double B = std::atan2(currentPoint.y, currentPoint.x); // longitude, radians

    Point PT = {180/M_PI* A,180/M_PI*B}; // final result in degrees

    return PT;
};

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