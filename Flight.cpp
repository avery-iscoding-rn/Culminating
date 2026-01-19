#include "Flight.hpp"

Flight::Flight(std::string c, Airport d, Airport o, Plane p, int l, int a)
    :code(c), destination(d), origin(o), aircraft(p), liftoff(l), arrival(a) {}

struct coordinates {
    double x;
    double y;
    double z;
};

Flight::getPoint(Flight F, int timern){
    int R = 6371;
    double φ = F.origin.coordinates.latitude * M_PI / 180;
    double λ = F.origin.coordinates.longitude* M_PI / 180;
    double xO = cos(φ) * cos(λ);
    double yO = cos(φ) * sin(λ);
    double zO = sin(φ);
    double φ2 = F.destination.coordinates.latitude* M_PI / 180;
    double λ2 = F.destination.coordinates.longitude* M_PI / 180;
    double xD = cos(φ2) * cos(λ2);
    double yD = cos(φ2) * sin(λ2);
    double zD = sin(φ2);

    double angle = std::acos((xO*xD)+(yO*yD)+(zO*zD));
    double surfacedistance = R * angle;

    double distance = getdistance(F.destination.coordinates, F.origin.coordinates);
    //Point resultant = {F.destination.coordinates.latitude-F.origin.coordinates.latitude, F.destination.coordinates.longitude - F.origin.coordinates.longitude};
    // coordinates resultant = {xD-xO, yD-yO, zD-zO}; 


    double Distancetravelled = 100 * (timern - F.liftoff);
    // will be changed to Flight.aircraft.speed

    //Velocity (km/h) x time spent = distance travelled
    double t = Distancetravelled/surfacedistance;
    if (t > 1){
        t = .999;
    }
    // coordinates currentPoint = {xO + (percentofFlight*resultant.x),  yO + (percentofFlight*resultant.y), zO + (percentofFlight*resultant.z)};

    /// sherical linear interpolation
    coordinates currentPoint {
        (sin((1-t)*angle) / sin(angle) * xO + sin (t*angle) / sin(angle) * xD),
        (sin((1-t)*angle) / sin(angle) * yO + sin (t*angle) / sin(angle) * yD),
        (sin((1-t)*angle) / sin(angle) * zO + sin (t*angle) / sin(angle) * zD),
    };


    double len = sqrt(currentPoint.x*currentPoint.x + currentPoint.y*currentPoint.y + currentPoint.z*currentPoint.z);
    if (len > 0) {
    currentPoint.x = currentPoint.x / len;
    currentPoint.y = currentPoint.y /len;
    currentPoint.z = currentPoint.z /len;
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