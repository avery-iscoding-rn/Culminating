//Avery and Aurora culminating
//January 13th 2026
//A global airspace and airport simulator

//including
#include "Airport.hpp"
#include "Plane.hpp"
#include "Point.hpp"
#include "Flight.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <fstream>
#include <random>

//GLOBAL VARIABLES------------
int hours, minutes, allminutes; //allminutes is ongoing counter that never resets, minutes and hours are for display
time_t start = time(NULL); //inital timestamp for reference-- for start of program to reset simulated time
std::vector<Airport> Airports;
std::vector<Flight> plannedflights; 
//-----------------------------




//FUNCTIONS -------------------

int randomInt(int low, int high) { //Random number generator i found somewhere
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(low, high);
    return dist(gen);
}

    //SETUP FUNCTIONS===========

void readairports() { //fills the vector of all the airports from the text file
    std::ifstream inFile;
    inFile.open("airports.txt");
    std::string line;
    int num;

    getline(inFile, line);
    num = stoi(line);

    for (int i = 0; i < num; i++) {
        std::string name, city, code;
        int lat, log;
        
        getline(inFile, name);
        getline(inFile, city);
        getline(inFile, code);

        getline(inFile, line);
        lat = stoi(line);
        getline(inFile, line);
        log = stoi(line);

        Point temp(lat, log);

        Airport temporary(name, city, code, temp);
        Airports.push_back(temporary);
    }
    inFile.close();
}

void createplanes() { //creates planes and puts them in a random airport
    int num;

    num = randomInt(0,11);
    Plane Boeing737("Boeing737", Airports[num].getlocation(), false, 200, 730);
    Airports[num].addplane(Boeing737);

    num = randomInt(0,11);
    Plane Airbus330("Airbus330", Airports[randomInt(0,11)].getlocation(), false, 300, 880);
    Airports[num].addplane(Airbus330);

    num = randomInt(0,11);
    Plane Boeing777("Boeing777", Airports[randomInt(0,11)].getlocation(), false, 510, 920);
    Airports[num].addplane(Boeing777);
}


void setup() { //simplification of setup
    readairports();
    createplanes();
    initalflights();
}
    //PLANE/FLIGHT FUNCTIONS

void initalflights() {
    int j;
    for (int i = 0; i < 3; i++) {
        //finding plane
        for (int i = 0; i < Airports.size(); i++) {
            if (!Airports[i].planes.empty()) {
                j = i;
            }
        }
        //randomizing destination
        int dest = i;
        do {
            dest = randomInt(0,11);
        } while (dest != i);

        //creating flight
        Flight temporary(randomInt(100000,999999), Airports[dest] ,Airports[i], Airports[i].planes[0],allminutes,-1); //arrival is -1 for rn cuz we don't know time yet
        temporary.getorigin().removeplane(temporary.getaircraft()); //removes and makes plane bool "flyings"/true
        plannedflights.push_back(temporary);
    }
}

    //TIME FUNCTIONS============
void printtime() {
    time_t rn = time(NULL);
    rn = rn-start;

    //converting into readable format
    int seconds = rn%60;
    int allminutes = rn/60;
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
    int allminutes = rn/60;
    int hours = minutes/60;
    minutes = minutes - (hours*60);
}
    //===============
//------------------------------------------------------


//main
int main(void){
    setup();

    return 0;
}