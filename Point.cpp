#include "Point.hpp"

Point::Point(double l, double L)
    :latitude(l), longitude(L) {}

//calculates distance between two points, taking into account the curve of earth's surface
 double Point::getdistance(const Point& p1, const Point& p2) {
    double rad1long = p1.longitude*(M_PI/180);
    double rad2long = p2.longitude*(M_PI/180);

    double rad1lat = p1.latitude*(M_PI/180);
    double rad2lat = p2.latitude*(M_PI/180);

    double Dlong = rad2long - rad1long;
    double Dlat = rad2lat - rad1lat;


    double a = (std::pow(std::sin(Dlat/2),2)) + (std::cos(rad1lat) * std::cos(rad2lat) * std::pow((std::sin(Dlong/2)),2));
    double c = 2* std::atan2(std::sqrt(a), std::sqrt(1-a)) ;
    double distance = 6371 * c; // earth's radius
    return distance;
}

double Point::getlat(){
    return latitude;
}
double Point::getlong(){
    return longitude;
}

std::string Point::toString(){
    return ("[" + std::to_string(latitude) + ","+ std::to_string(longitude)+"]");
}
std::string Point::toString(){
    return ("[" + std::to_string(std::ceil(latitude*100.0)/100.0) + ","+ std::to_string(std::ceil(longitude*100.0)/100.0)) +"]";
}