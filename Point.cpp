#include "Point.hpp"

Point::Point(int L, int l)
    :longitude(L), latitude(l) {}

Point::getdistance(Point p1, Point p2) {
<<<<<<< HEAD
    return 0;
=======
    double rad1long = p1.longitude*(M_PI/180);
    double rad2long = p2.longitude*(M_PI/180);

    double rad1lat = p1.latitude*(M_PI/180);
    double rad2lat = p2.latitude*(M_PI/180);

    double Dlong = rad2long - rad1long;
    double Dlat = rad2lat - rad1lat;

    double a = ((std::sin(Dlat/2))**2) + (std::cos(rad1lat) * std::cos(rad2lat) * (std::sin(Dlong/2))**2)
    double c = 2* (a * tan2(std::sqrt(a), std::sqrt(1-a))) ;
    double distance = 6731 * c;
    return distance;
>>>>>>> 3172ff0e9d83624ac23097bea6ee3ed1eadf63e7
}
