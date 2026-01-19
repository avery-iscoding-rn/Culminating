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
        Flight temporary(std::to_string(randomInt(100000,999999)), Airports[dest] ,Airports[i], Airports[i].planes[0],allminutes,-1); //arrival is -1 for rn cuz we don't know time yet
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

void searchflightcode(){
    std::cout << "Enter the code of the flight you are looking for: "
        int code;
        std::cin >> code;
        bool doesexist = false;
        searchindex;

        for (int i = 0; i < plannedflights.size(); i ++){
            if (plannedflights[i].getcode() == code){
                doesexist = true;
                searchindex = i;
            }
        
        if (doesexist == false){
            std::cout << "\nFlight not found.";
        }

        else {
            std::cout << "\nFlight: " << plannedflights[searchindex].getorigin().getcode() << " - > " << plannedflights[searchindex].getdest().getcode();
            std::cout<< "\nDeparting from:  " << plannedflights[searchindex].getorigin().getcity();
            std::cout<< "\nHeaded to:  " << plannedflights[searchindex].getdestination().getcity();
            std::string planestatus;
            resettime();
            Point currentlocation = Flight::getPoint(plannedflights[searchindex], timern);
            if ((plannedflights[searchindex].getorigin().getlocation().getlat)-1 <= plannedflights[searchindex].getorigin().getlocation().getlat <= (plannedflights[searchindex].getorigin().getlocation().getlat)+1) && ((plannedflights[searchindex].getorigin().getlocation().getlong())-1 <= plannedflights[searchindex].getorigin().getlocation().getlong() <= 1 + plannedflights[searchindex].getorigin().getlocation().getlong) {
                planestatus = "Departing Soon"; 
            }
            else if ((plannedflights[searchindex].getdest().getlocation().getlat)-1 <= plannedflights[searchindex].getdest().getlocation().getlat <= (plannedflights[searchindex].getdest().getlocation().getlat)+1) && ((plannedflights[searchindex].getdest().getlocation().getlong())-1 <= plannedflights[searchindex].getdest().getlocation().getlong() <= 1 + plannedflights[searchindex].getdest().getlocation().getlong) {
                planestatus= "Arrived";
            }
            if planestatus == "Arrived" or "Departing Soon"{
                std::cout<<"\nStatus:   " << planestatus;
            }
            else {
                std::cout << "\nStatus: Currently flying";
                std::cout << "\nCurrent location:   "<< Flight::getPoint(plannedflights[searchindex],timern).latitude << " , " << Flight::getPoint(plannedflights[searchindex],timern).longitude;
            }
        }

    }
}

void menu() { //menu printing function
    std::cout << "1. See flight schedule\n2. See live updates\n3. Find a plane\n4. Find an airport\n5. Exit\n-> ";
    int num;
    std::cin >> num;
    //making sure number is valid
    do {
    std::cout << "\nPlease enter a number between 1-5\n";
    std::cout << "1. See flight schedule\n2. See live updates\n3. Find a plane\n4. Find an airport\n5. Search by flight code \n6. Exit\n-> ";
    } while (num > 7 || num < 1);

    if (num == 1) { // FLIGHT SCHEDULE
        std::cout << "placeholder";

    } else if (num == 2) { //SEE LIVE UPDATES
        std::cout << "placeholder";

    } else if (num == 3) { //FIND A PLANE
        std::cout << "placeholder";

    } else if (num == 4) { //FIND AN AIRPORT
        std::cout << "placeholder";

    } else if (num == 5){ // search by flight code
        searchflightcode()
    }
    else if(num == 6){
        std::cout<<"\nGoodbye";
        running = false;
    }
}


void setup() { //simplification of setup
    readairports();
    createplanes();
    initalflights();
}


//------------------------------------------------------


//main
int main(void){
    setup();

    return 0;
}