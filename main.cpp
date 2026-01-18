//Avery and Aurora culminating
//January 13th 2026
//A global airspace and airport simulator

//including
#include "Airport.hpp"
#include "Plane.hpp"
#include "Point.hpp"

#include <iostream>
//#include <algorthim>
#include <string>
#include <vector>
#include <ctime>

//global variables
int hours, minutes;
time_t start = time(NULL); //inital timestamp for reference-- for start of program to reset simulated time
void printtime() {
    time_t rn = time(NULL);
    rn = rn-start;

    //converting into readable format
    int seconds = rn%60;
    int minutes = rn/60;
    int hours = minutes/60;
    minutes = minutes - (hours*60);

    printf("Current sim, time is %02d:%02d\n", minutes, seconds);
}

void resettime() {
        time_t rn = time(NULL);
    rn = rn-start;

    //converting into readable format
    int seconds = rn%60;
    int minutes = rn/60;
    int hours = minutes/60;
    minutes = minutes - (hours*60);
}


//main
int main(void){


    return 0;
}