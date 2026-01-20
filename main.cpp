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
int hours, minutes, realhours; //allminutes is ongoing counter that never resets, minutes and hours are for display
int allminutes;
time_t start = time(NULL); //inital timestamp for reference-- for start of program to reset simulated time
time_t rn;
std::vector<Airport> Airports;
std::vector<Flight> plannedflights; 
bool running = true;  //if program is running
//-----------------------------




//FUNCTIONS -------------------
//Random number generator i found somewhere
int randomInt(int low, int high) { 
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(low, high);
    return dist(gen);
}

//fills the vector of all the airports from the text file
void readairports() { 
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
//creates planes and puts them in a random airport
void createplanes() { 
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

//creates an inital flight for each plane to start the schedule (vector of flights)
void initalflights() {
    int j;
    for (int i = 0; i < 3; i++) {
        //finding plane
        for (int h = 0; h < Airports.size(); h++) {
            if (!Airports[h].planes.empty()) {
                j = h;
            }
        }
        //randomizing destination
        int dest = j;
        do {
            dest = randomInt(0,11);
        } while (dest != j);

        //creating flight
        Flight temporary(std::to_string(randomInt(100000,999999)), Airports[dest] ,Airports[j], Airports[j].planes[0],allminutes,-1); //arrival is -1 for rn cuz we don't know time yet
        temporary.getorigin().removeplane(temporary.getaircraft()); //removes and makes plane bool "flyings"/true
        plannedflights.push_back(temporary);
    }
}

//refreshes time (boht HH:MM and allminutes which is just and ongoing counter of the seconds since program started)
void resettime(bool print) {
    rn = time(NULL);
    rn = rn-start;

    //converting into readable format
    allminutes = rn; //all seconds

    minutes = rn%60; //irl seconds
    hours = rn/60; //irl minutes

    realhours = hours/60; //removing real hours
    hours = hours - (realhours*60);

    if (print) {
        std::cout << "\n";
        printf("January 1st, 2075, %02d:%02d\n", hours, minutes);
    }

    //Stopping the clock at 24 hours
    if (hours > 23) {
        running = false;
        std::cout << "\n\n The day is over! Thanks for visiting!";
    }
}

//converts AND PRINTS an allminutes value into the 24 hour HH:MM clock string
void convert(int allmin) {
    int h = allmin/60;
    int m = allmin%60;

    printf("%02d:%02d\n", h, m);
}

//searches vectors for the given flight code (basically linear search)
void searchflightcode(){
    std::cout << "Enter the code of the flight you are looking for: ";
    std::string code;
    std::cin >> code;
    bool doesexist = false;
    int searchindex;
    
    for (int i = 0; i < plannedflights.size(); i ++){
        if (plannedflights[i].getcode() == code){
            doesexist = true;
                searchindex = i;
        }
    }
    
    //flight doesn't exist
    if (!doesexist) {
        std::cout << "\nFlight not found.";
    
    } else {
        Flight temp = plannedflights[searchindex]; //flight we're looking for

        //printing data
        std::cout << "\nFlight: " << temp.getorigin().getcode() << " - > " << temp.getdest().getcode();
        std::cout<< "\nDeparting from:  " << temp.getorigin().getcity();
        std::cout<< "\nHeaded to:  " << temp.getdest().getcity();

        //finding plane
        std::string planestatus;
        resettime(false);
        Point currentlocation = temp.getPoint(rn);

        //if close to Airport of origin, then display departing soon
        if ((currentlocation.getlat() >= temp.getorigin().getlocation().getlat()-1 && currentlocation.getlat() <= temp.getorigin().getlocation().getlat()+1) && (currentlocation.getlong() >= temp.getorigin().getlocation().getlong()-1 && currentlocation.getlong() <= temp.getorigin().getlocation().getlong()+1)) {
            planestatus = "Departing Soon"; 

        //if close to Airport of desitnation, then display "arrived"
        } else if ((currentlocation.getlat() >= temp.getdest().getlocation().getlat()-1 && currentlocation.getlat() <= temp.getdest().getlocation().getlat()+1) && (currentlocation.getlong() >= temp.getdest().getlocation().getlong()-1 && currentlocation.getlong() <= temp.getdest().getlocation().getlong()+1)) {
            planestatus= "Arrived";
        }
        
        //if close to an airport
        if (planestatus == "Arrived" or "Departing Soon"){
            std::cout<<"\nStatus:   " << planestatus;

        //if in the air
        } else {
            std::cout << "\nStatus: Currently flying";
            Point location = temp.getPoint(rn); //current location
            std::cout << "\nCurrent location:   "<< location.getlat() << " , " << location.getlong();
        }
    }    
}

std::vector<Flight> findFlights(Airport A, std::string DorA){

    std::vector<Flight> flightsFromAirport;

    for (Flight F: flightsFromAirport){
        if (DorA == "A"){
            if (F.getdest().getcode()== A.getcode()){
                flightsFromAirport.push_back(F);
            }
        }
        else if (DorA == "D"){
            if (F.getorigin().getcode() == A.getcode()){
                flightsFromAirport.push_back(F); 
            }
        }
    }
}

void searchairport(){
    std::cout << "Enter the 3 letter code of the airport you are looking for: ";
    std::string code;
    std::cin >> code;
    bool doesexist = false;
    int searchindex;
    
    for (int i = 0; i < Airports.size(); i ++){
        if (Airports[i].getcode() == code){
            doesexist = true;
            searchindex = i;
        }
    }

    if (!doesexist) {
        std::cout << "\nAirport not found.";
    }

    else{
        std::cout<< "\nAirport: " << Airports[searchindex].getname();
        std::cout << "\nCity:   " << Airports[searchindex].getcity();
        
        // departures
        std::cout<< "\nDepartures:  " << "-----"; 
        std::cout <<"\nCode         |           Destination          |        Status/Location         |           Departure Time          |           Arrival Time";
        for (Flight F : findFlights(Airports[searchindex], "D") ){
            std::cout<<"\n"<< F.getcode()<<"                           ";
            std::cout<<"\n"<< F.getdest().getcode() << ":"<< F.getdest().getcity()<<"     ";
            if(F.getaircraft().getcoordinates().getlat() == F.getdest().getlocation().getlat() && F.getaircraft().getcoordinates().getlong() == F.getdest().getlocation().getlong()){
                std::cout<< "Arrived                 ";
            }
            else if ((F.getaircraft().getcoordinates().getlat() == F.getorigin().getlocation().getlat()) && (F.getaircraft().getcoordinates().getlong() == F.getorigin().getlocation().getlong() )){
                std::cout<< "Departing soon.         ";
            }
            resettime(false);
            std::cout<< "["<<F.getPoint(rn).getlat()<<" , "<<F.getPoint(rn).getlong()<<"]       ";
            std::cout<< F.liftofftime() << "                   "<< F.landingtime();
            std::cout<<"\n";


        // arrivals 
        std::cout<< "\n\nArrivals:  " << "-----"; 
        std::cout <<"\nCode         |           Destination          |        Status/Location         |           Departure Time          |           Arrival Time";
        for (Flight F : findFlights(Airports[searchindex], "A") ){
            std::cout<<"\n"<< F.getcode()<<"                           ";
            std::cout<<"\n"<< F.getorigin().getcode() << ":"<< F.getorigin().getcity()<<"     ";
            if(F.getaircraft().getcoordinates().getlat() == F.getdest().getlocation().getlat() && F.getaircraft().getcoordinates().getlong() == F.getdest().getlocation().getlong()){
                std::cout<< "Arrived                 ";
            }
            else if (F.getaircraft().getcoordinates().getlat() == F.getorigin().getlocation().getlat() && F.getaircraft().getcoordinates().getlong() == F.getorigin().getlocation().getlong()){
                std::cout<< "Departing soon.         ";
            }
            std::cout<< "["<<F.getPoint(rn).getlat()<<" , "<<F.getPoint(rn).getlong()<<"]       ";
            std::cout<< F.liftofftime() << "                   "<< F.landingtime();

        }
    }
}

}

//prints menu, processes user input (also validates it), then runs subsequent function
void menu() {

    //std::cout << "\nMENU:\n1. See flight schedule\n2. See live updates\n3. Find a plane\n4. Find an airport\n5. Search by flight code \n6. Exit\n-> ";
    int num = 0;
    //making sure number is valid
    do {
        if (num != 0) {
            std::cout << "\nPlease enter a number between 1-5\n";
        }
        std::cout << "\nMENU:\n1. See flight schedule\n2. See live updates\n3. Find a plane\n4. Find an airport\n5. Search by flight code \n6. Exit\n-> ";
        std::cin >> num;
    } while (num > 7 || num < 1); //validating num
    


    if (num == 1) { // FLIGHT SCHEDULEs
        std::cout << "placeholder";
        
    } else if (num == 2) { //SEE LIVE UPDATES
        std::cout << "placeholder";

    } else if (num == 3) { //FIND A PLANE
        std::cout << "placeholder";
        
    } else if (num == 4) { //FIND AN AIRPORT
        searchairport();
        
    } else if (num == 5){ // search by flight code
        searchflightcode();
    }
    else if(num == 6){
        std::cout<<"\nThanks for visiting! Book a flight soon!\n\n";
        running = false;
    }
}

//simplification of set up that needs to be done at start of program (airports, planes, flights)
void setup() { 
    readairports();
    createplanes();
    initalflights();
}


//------------------------------------------------------




//main function
int main(void){
    std::cout << "WELCOME STATEMENT (PLACEHOLDER)\n";
    setup();

    int test = 0;
    while (running) {
        resettime(true);
        menu();
    }

    return 0;
}