#include "Flight.hpp"

Flight::Flight(std::string c, Airport& d, Airport& o, Plane& p, double l, double a)
    :code(c), destination(&d), origin(&o), aircraft(&p), liftoff(l), arrival(a) {}

struct coordinates {
    // longitude and latitude angles must be converted to an [x,y,z] vector to find current point
    double x;
    double y; 
    double z;
}; 

//finds current location of a plane en route between two different airport depending on the current time
Point Flight::getPoint(int timern){

    int R = 6371; // earth's radius

    // Converting degrees to radians
    double φ = origin->getlocation().getlat() * M_PI / 180;
    double λ = origin->getlocation().getlong()* M_PI / 180;

    // Using degrees in radians to a vector (origin)

    double xO = cos(φ) * cos(λ);
    double yO = cos(φ) * sin(λ);
    double zO = sin(φ);

    // Converting degrees to radians
    double φ2 = destination->getlocation().getlat()* M_PI / 180;
    double λ2 = destination->getlocation().getlong()* M_PI / 180;

    // Using degrees in radians to a vector (destination)
    double xD = cos(φ2) * cos(λ2);
    double yD = cos(φ2) * sin(λ2);
    double zD = sin(φ2);

     // Dot product to find angle between 2 location vectors
     double angle = (xO*xD)+(yO*yD)+(zO*zD);

    // Multiplying the cos of this angle by the earth's radius will give us the surface distance between the 2 points
    // Because cos theta = a / h so a = surface distance and h = the earth's radius
    // I think that's why but not 100% sure lol
    double surfacedistance = R * std::acos(angle);

    double distance = Point::getdistance(origin->getlocation(), destination->getlocation());
    // not needed (?)

    double Distancetravelled = aircraft->getspeed() * (timern - liftoff);
    //Velocity (km/h) x time spent = distance travelled

    double t = Distancetravelled/distance;
    // Factor by which you need to multiply the unit vector [x,y,z] because that is just a ratio, not an exact distance
    // Percent of trip done

    if (t > 1){
        t = .999;
    }
    if (t==0){
        t = 0.0001;
    }

    // Spherical linear interpolation
    // Don't really know how this works tbh
    coordinates currentPoint {
        (sin((1-t)*angle) / sin(angle) * xO + sin (t*angle) / sin(angle) * xD),
        (sin((1-t)*angle) / sin(angle) * yO + sin (t*angle) / sin(angle) * yD),
        (sin((1-t)*angle) / sin(angle) * zO + sin (t*angle) / sin(angle) * zD),
    };

    // Resultant magnitude (Length of vector)
    double len = sqrt(currentPoint.x*currentPoint.x + currentPoint.y*currentPoint.y + currentPoint.z*currentPoint.z);

    if (len != 0) {
        // can't be 0

        currentPoint.x = currentPoint.x / len;
        currentPoint.y = currentPoint.y /len;
        currentPoint.z = currentPoint.z /len;
        // Divide it back by length to get unit vector of length 1 (?) before converting back to radians 
    }

    double A = std::atan2(currentPoint.z,(std::sqrt(std::pow(currentPoint.x,2)+(std::pow(currentPoint.y,2))))); //latitdude, radians
    double B = std::atan2(currentPoint.y, currentPoint.x); // longitude, radians

    Point PT(180/M_PI* A, 180/M_PI*B); // final result in degrees

    return PT;
};

// //constant updating flights
// void Flight::fly(bool rweflying, int timern) {
//     if (rweflying) {
//         aircraft.getcoordinates() = getPoint(timern);
//     } 
// }

//returns true is plane location is close enough to airport origin location
bool Flight::atorigin(Point mycoordinates) {
    if ((mycoordinates.getlat() >= origin->getlocation().getlat()-1 && mycoordinates.getlat() <= origin->getlocation().getlat()+1) && (mycoordinates.getlong() >= origin->getlocation().getlong()-1 && mycoordinates.getlong() <= origin->getlocation().getlong()+1)){
        aircraft->takeoff(); //starts flight;
        return true;
    }
    else{
        return false;
    }
}

//returns true if plane location is close enough to destination (marks as at the airport)
bool Flight::atdest(Point mycoordinates) {
    if ((mycoordinates.getlat() >= destination->getlocation().getlat()-1 && mycoordinates.getlat() <= destination->getlocation().getlat()+1) && (mycoordinates.getlong() >= destination->getlocation().getlong()-1 && mycoordinates.getlong() <= destination->getlocation().getlong()+1)){
        aircraft->land();//ends flight
        return true;
    }
    else{
        return false;
    }
}

Airport& Flight::getdest() {
    return *destination;
}

Airport& Flight::getorigin(){
    return *origin;
}

std::string Flight::getcode(){
    return code;
}

Plane& Flight::getaircraft(){
    return *aircraft;
}

double Flight::liftofftime(){
    return liftoff;
}

double Flight::landingtime(){
    return arrival;
}

//SECOND OVERLOADING OPERATOR
//overriding < operator so we can compare flights and sort them in a vector (according to departure time)
bool Flight::operator<(const Flight& other) const {
    return liftoff < other.liftoff;
}
