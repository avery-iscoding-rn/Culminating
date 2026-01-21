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
#include <iomanip>
#include <algorithm>


//GLOBAL VARIABLES------------
int hours, minutes, realhours; //allminutes is ongoing counter that never resets, minutes and hours are for display
int allminutes;
time_t start = time(NULL); //inital timestamp for reference-- for start of program to reset simulated time
time_t rn;
std::vector<Airport> Airports;
std::vector<Flight> plannedflights; //vector of all flight ever
std::vector<Plane> Planes;
std::vector<int> flightnums; //vector of all existing flight ID/flight numbers
bool running = true;  //if program is running
std::vector <Flight> nowflights;

struct UPDATE{
    int timeofupdate;
    std::string message; //AIRCRAFT ARRIVED/DEPARTED AT AIRPORTCODE
    Flight theflight;
    Plane theplane;
};

std::vector<UPDATE> liveupdates; //contains all updates
//-----------------------------




//FUNCTIONS -------------------


//Random number generator i found somewhere
int randomInt(int low, int high) { 
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(low, high);
    return dist(gen);
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
        std::cout << "\n\n------------------------\n";
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

    printf("%02d:%02d", h, m);
}

// prints status
std::string printstatus(Flight F){
    if (F.getaircraft().status()){
        return "Flying";
    }
    else{
        if (F.atorigin(F.getPoint(allminutes))){
            return "Departing soon";
        } else {
            return "Arrived";
        }
    }
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
        double lat, log;
        
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
    Plane Boeing737("Boeing737", Airports[num].getlocation(), false, 200, 730,0); //last num is the flight they belong to, 0 == no flight
    Airports[num].addplane(Boeing737);

    num = randomInt(0,11);
    Plane Airbus330("Airbus330", Airports[randomInt(0,11)].getlocation(), false, 300, 880,0);
    Airports[num].addplane(Airbus330);

    num = randomInt(0,11);
    Plane Boeing777("Boeing777", Airports[randomInt(0,11)].getlocation(), false, 510, 920,0);
    Airports[num].addplane(Boeing777);

    Planes.push_back(Boeing737);
    Planes.push_back(Airbus330);
    Planes.push_back(Boeing777);
}



//creates an inital flight for each plane to start the schedule (vector of flights)
void initalflights() {

    //rounding set up
    std::cout << std::fixed << std::setprecision(2);

    //finding planes which airport each plane is at
    int j;
    
    for (int p = 0; p < Planes.size(); p++) { //for every plane
        //std::cout << "\nplane number " << p << ", " << Planes[p].getmodel();
        //std::cout << "\nplanes # " << p;
        for (int a = 0; a < Airports.size(); a++) { //for every airport
            //std::cout << "\nairports # " << a;
            if (Airports[a].contains(Planes[p], 0) != -1) {// if plane is in this airport
                j = a;
                    //std::cout << "\nfound in " << Airports[a].getname();
            }
        }
        //randomizing destination
        int dest = j;
        do {
            dest = randomInt(0,11);
        } while (dest == j);
        //std::cout << "\norigin" << Airports[j].getname();
        //std::cout << "\ndesination" << Airports[dest].getname();
        
        //creating flight
        //randomizing flight num and fact checking it doesnt already exist.
        bool repeated = false;
        int ID;
        do {
            ID = randomInt(100000,999999);
            for (int i = 0; i < flightnums.size(); i++) {
                if (flightnums[i] == ID) {
                    repeated = true;
                }
            }
        } while (repeated);
        
        
        //creating instance of flight
        //estimated arrival time
        int atime; 
        atime = Point::getdistance(Airports[j].getlocation(),Airports[dest].getlocation())/Planes[p].getspeed(); //time is distance/speed
        std::cout << "\n" << Point::getdistance(Airports[j].getlocation(),Airports[dest].getlocation()) << " / " << Planes[p].getspeed() << " = " << atime;
        Flight temporary(std::to_string(ID), Airports[dest] ,Airports[j], Airports[j].planes[0],allminutes, allminutes + (60*atime)); //tracking time + (60(to convert to minutes) x estimiated time) --> tracked estimated time (in allminutes)
        //std::cout << "\nflight created";
        std::cout << "\n" << temporary.getcode();
        plannedflights.push_back(temporary);

        //making sure the plane knows its flying now (cuz all inital flights leave at 00:00)
        temporary.getaircraft().flightnum = std::stoi(temporary.getcode());
        temporary.getaircraft().takeoff();

        //creating update
        struct UPDATE newupdatee{
            allminutes,
            "Departed",
            temporary,
            temporary.getaircraft(),
        };
        liveupdates.push_back(newupdatee);
    } 
}



//creates scheduled flights
//creates scheduled flights
void scheduleflights() {
    if (plannedflights.empty()) { //if no planned flights
        initalflights();
    } else { //if there are planned flights
        std::cout << "PLACEHOLDER";
        //AURORA I WILL FINISH THIS FUNCITON AFTER SCHOOL OKAY-- IT WILL FILL THE PLANNED FLIGHT VECTOR WITH FLIGHTS
    //creating inital flights
    initalflights();

    //Then creating subsequent flights
    std::cout << "\nsubsequent flights";

    bool withintheday = true;
    int index = 0; //the flight we're looking at to create the new flight

    while (index < plannedflights.size()) { //looping so long as it's within the same day (24 hours)

        Flight previous = plannedflights[index]; //the flight we're looking at to base new one off of
        std::cout << "\nbasing off of flight number " << index;

        //SETTING EACH VARIABLE FOR NEW FLIGHT
            //generating code
        bool repeated = false;
        int ID;
        do {
            ID = randomInt(100000,999999);
            for (int i = 0; i < flightnums.size(); i++) {
                if (flightnums[i] == ID) {
                    repeated = true;
                }
            }
        } while (repeated);
        std::cout << "\ncreated flight ID";

            //randomizing destination
        int dest;
        do { //randomize destination while it is not equal to our orign/destination of previous flight
            dest = randomInt(0,11);
        } while (Airports[dest].getname() == previous.getdest().getname());
        std::cout << "\nfound destination";

            //doing time math
        int leavingtime = previous.landingtime() + 45; //adding forty five mintues for stuff until the plane leaves again
        double estimatedarrival = leavingtime + 60*(Point::getdistance(previous.getdest().getlocation(),Airports[dest].getlocation())/previous.getaircraft().getspeed());
        std::cout << "\nfiguring out time, arrival time is" << estimatedarrival;

        //checking if we need to break this bad boy
        if (estimatedarrival >= 1439) { //if goes beyond the 24 hour time constraint
            std::cout << "\ncan't make the flight";
            

        } else { //make the flight
            
            Flight newflight(std::to_string(ID), Airports[dest], previous.getdest(), previous.getaircraft(), leavingtime, estimatedarrival);
            std::cout << "\ncreated the flight";
            plannedflights.push_back(newflight);
            std::cout << "\npushed it into vector";
        }
        index++;
    }
    
    //sorting flights according to their departure time
    std::sort(plannedflights.begin(), plannedflights.end());
}


}


//prints full flight schedule in a designated format (i.e. contents of plannedflights)
void printflightschedule() {
    std::cout << std::fixed << std::setprecision(2); //round to 2 decimal places for output

    std::cout << "\nFLIGHT SCHEDULE:\n----------------";
    for (int i = 0; i < plannedflights.size(); i++) {
        Flight thisone = plannedflights[i];
        std::cout << "\n\nFlight " << thisone.getcode() << "\n" << thisone.getaircraft().getmodel() << " travelling " << thisone.getorigin().getcity() << " (" << thisone.getorigin().getcode() << ") -> " << thisone.getdest().getcity() << " (" << thisone.getdest().getcode() << ")";
        std::cout << "\nDeparture time ";
        convert(thisone.liftofftime());
        std::cout << "Estimated arrival time ";
        convert(thisone.landingtime());
        double dist = Point::getdistance(thisone.getorigin().getlocation(),thisone.getdest().getlocation());
        std::cout << "Travelling " << dist << "km in about " << dist/thisone.getaircraft().getspeed() << " hours (speed of " << thisone.getaircraft().getspeed() << "km/h)";
    }
}
// Flight whichFlightDoesPlaneBelongTo (Plane P){
    //     for (int i = 0; i < plannedflights.size(); i++){
//         if (plannedflights[i].getaircraft() == P){
//             return plannedflights[i];
//         }
//     }
//     Flight fake()
//     return fake;
// }


//searches vectors for the given flight code (basically linear search)
void searchflightcode(){
    std::cout << "\nEnter the code of the flight you are looking for: ";
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
        std::cout << "\nDeparting from: " << temp.getorigin().getname() << ", " << temp.getorigin().getcity();
        std::cout << "\nDeparture time : ";
        convert(temp.liftofftime());
        std::cout << "\nHeading to: " << temp.getdest().getname() << ", " << temp.getdest().getcity();
        std::cout << "\nEstimated arrival time : ";
        convert(temp.landingtime());
        std::cout << "\nAircraft: " << temp.getaircraft().getmodel();

    //finding plane
        std::string planestatus;
        resettime(false);
        Point currentlocation = temp.getPoint(allminutes);

        //if close to Airport of origin, then display departing soon
        if ((currentlocation.getlat() >= temp.getorigin().getlocation().getlat()-1 && currentlocation.getlat() <= temp.getorigin().getlocation().getlat()+1) && (currentlocation.getlong() >= temp.getorigin().getlocation().getlong()-1 && currentlocation.getlong() <= temp.getorigin().getlocation().getlong()+1)) {
            planestatus = "Departing Soon"; 

        //if close to Airport of desitnation, then display "arrived"
        } else if ((currentlocation.getlat() >= temp.getdest().getlocation().getlat()-1 && currentlocation.getlat() <= temp.getdest().getlocation().getlat()+1) && (currentlocation.getlong() >= temp.getdest().getlocation().getlong()-1 && currentlocation.getlong() <= temp.getdest().getlocation().getlong()+1)) {
            planestatus= "Arrived";
        }
        
        //if close to an airport
        if (planestatus == "Arrived" | planestatus =="Departing Soon"){
            std::cout<<"\nStatus: " << planestatus;

        //if in the air
        } else {
            std::cout << "\nStatus: Currently flying";
            resettime(false);
            std::cout << "\nCurrent location: "<< "["<<temp.getPoint(allminutes).getlat() << " , " << temp.getPoint(allminutes).getlong()<<"]";
        }
    }    
}

// returns vector of all flights from a certain airport either departing or arriving
std::vector<Flight> findFlights(Airport A, std::string DorA){

    std::vector<Flight> flightsFromAirport;

    for (Flight F : plannedflights){
        if (DorA == "A" ){
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
    return flightsFromAirport;
}

// returns vector of CURRENT flights (remakes every time, does not exist outside of function)
std::vector <Flight> getcurrentflights (int timern){
    std::vector <Flight> currentflights;
    for (Flight F : plannedflights){
        if (F.getaircraft().status()==true){
            currentflights.push_back(F);
        }
    }
    return currentflights;
}

// searches for an airport by 3 digit code and outputs departures and arrivals
void searchairport(){

    int searchindex;
    std::string code;
    char space = ' ';

    std::cout << "Enter the 3 letter code of the airport you are looking for: ";
    std::cin >> code;
    bool doesexist = false;
    
    for (int i = 0; i < Airports.size(); i ++){
        if (Airports[i].getcode() == code){
            doesexist = true;
            searchindex = i;
        }
    }

    if (!doesexist) {
        std::cout << "\nAirport not found.\nEnsure you enter the code in capital letters.";
    }

    else{
        std::cout<< "\nAirport: " << Airports[searchindex].getname();
        std::cout << "\nCity:   " << Airports[searchindex].getcity();
        
        // departures
        std::cout<< "\nDepartures:  " << "-----"; 
        std::cout <<"\nCode         |   Destination   |    Status    |  Location        | Departure | Arrival ";
        for (Flight F : findFlights(Airports[searchindex], "D") ){
            std::cout<<"\n";
            std::cout<< std::left << std::setw(16) << std::setfill(space)<< F.getcode();
            std::cout<< std::left << std::setw(18) << std::setfill(space)<< F.getdest().getcode()<< ":" << F.getdest().getcity();
            std::cout<< std::left << std::setw(16) << std::setfill(space)<< printstatus(F);
            if(F.atorigin(F.getPoint(rn))){
                std::cout<< std::left << std::setw(16) << std::setfill(space)<< F.getorigin().getcode();
            }
            else if (F.atdest(F.getPoint(rn))){
                std::cout<< std::left << std::setw(16) << std::setfill(space)<< F.getdest().getcode();
            }
            else {
                resettime(false);
                std::cout<< std::left << std::setw(16) << std::setfill(space)<< F.getPoint(rn).toString();
            }
            std::cout<< std::left << std::setw(11) << std::setfill(space)<< F.liftofftime();
            std::cout<< std::left << std::setw(10) << std::setfill(space)<< F.landingtime();


        // // arrivals
        std::cout<< "\nArrivals:  " << "-----"; 
        std::cout <<"\nCode         |  Arriving from  |    Status    |  Location        | Departure | Arrival ";
        for (Flight F : findFlights(Airports[searchindex], "A") ){
            std::cout<<"\n";
            std::cout<< std::left << std::setw(16) << std::setfill(space)<< F.getcode();
            std::cout<< std::left << std::setw(18) << std::setfill(space)<< F.getorigin().getcode()<< ":" <<F.getorigin().getcity();
            std::cout<< std::left << std::setw(16) << std::setfill(space)<<printstatus(F);
            if(F.atorigin(F.getPoint(rn))){
                std::cout<< std::left << std::setw(16) << std::setfill(space)<< F.getorigin().getcode();
            }
            else if (F.atdest(F.getPoint(rn))){
                std::cout<< std::left << std::setw(16) << std::setfill(space)<< F.getdest().getcode();
            }
            else {
                resettime(false);
                std::cout<< std::left << std::setw(16) << std::setfill(space)<< F.getPoint(rn).toString();
            }
            std::cout<< std::left << std::setw(11) << std::setfill(space)<< F.liftofftime();
            std::cout<< std::left << std::setw(10) << std::setfill(space) <<F.landingtime();
        }
    }
}

}

// searches for a plane and outputs stats and current locaation
void findplane(){
    std::cout << "Enter the plane model (example: Boeing737): ";
        std::string plane;
        std::cin>> plane;
        for (Plane P: Planes){
            if (P.getmodel() == plane){
                std::cout<< "\n"<< plane;
                std::cout<<"\nCapacity: "<< P.getcapacity();
                std::cout<< "\nPlane speed: " << P.getspeed();
                if (P.status()== true){
                    std::cout<< "\nStatus: Currently flying";
                    std::cout<< "\nLocation: " << "[" << P.getcoordinates().getlat() << " , " << P.getcoordinates().getlong()<<"]"; 
                }
                else{
                    //FUNCTION NEEDA TO BE MADE THEN UNCOMMENT
                    std::cout<< "\nLocation: ";
                    // if (P.atorigin()== true){
                    //     std::cout << [" << P.getflight().getorigin().getlat(); << " , " << P.getflight().getorigin().getlong()<<"]"; 
                        
                    // }
                    // else if (P.atdest() == true){
                    //     std::cout<< P.getflight().getdest();
                    // }
                }
            }
        }
    std::string plane2;
    std::cin>> plane2;
    for (Plane P: Planes){
        if (P.getmodel() == plane2){
            std::cout<< "\n"<< plane2 << "\n------------------";
            std::cout<<"\nCapactity: "<< P.getcapacity();
            std::cout<< "\nPlane speed: " << P.getspeed() << "km/h";
            if (P.status()== true){
                std::cout<< "\nStatus: Currently flying";
                std::cout<< "\nLocation: " << P.getcoordinates().toString(); 
            }
            else{
                std::cout<< "\nLocation: ";
                for (Flight F: plannedflights){
                    if (F.getcode()==std::to_string(P.flightnum) && F.atorigin(F.getPoint(allminutes))){
                        std::cout<< F.getorigin().getcode();
                    }
                    else if (F.getcode()==std::to_string(P.flightnum) && F.atdest(F.getPoint(allminutes))){
                        std::cout<< F.getdest().getcode();
                    }
                }

            }
            std::cout << "\n\nScheduled flights today: ";
            for (int i = 0; i < plannedflights.size(); i++) {
                if (plannedflights[i].getaircraft() == P) {

                    //printing flight info
                    Flight thisone = plannedflights[i];
                    std::cout << "\n\nFlight " << thisone.getcode() << "\n" << thisone.getaircraft().getmodel() << " travelling " << thisone.getorigin().getcity() << " (" << thisone.getorigin().getcode() << ") -> " << thisone.getdest().getcity() << " (" << thisone.getdest().getcode() << ")";
                    std::cout << "\nDeparture time ";
                    convert(thisone.liftofftime());
                    std::cout << "Estimated arrival time ";
                    convert(thisone.landingtime());
                    double dist = Point::getdistance(thisone.getorigin().getlocation(),thisone.getdest().getlocation());
                    std::cout << "Travelling " << dist << "km in about " << dist/thisone.getaircraft().getspeed() << " hours (speed of " << thisone.getaircraft().getspeed() << "km/h)";

                }
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
    


    if (num == 1) { // FLIGHT SCHEDULE
        printflightschedule();
        
    } else if (num == 2) { //SEE LIVE UPDATES
        for (int i = 0; i < liveupdates.size(); i++) {
            UPDATE thisone = liveupdates[i];
            std::cout << "\n";
            convert(thisone.timeofupdate);
            std::cout << "-> Fight " << thisone.theflight.getcode() << ": " << thisone.theplane.getmodel() << " has " <<  thisone.message ;
            if (thisone.message == "Departed") {
                std:: cout << " from " << thisone.theflight.getorigin().getcode();
            } else {
                std:: cout << " at " << thisone.theflight.getdest().getcode();
            }
        }
        std::cout << "\n----------------\n";

    } else if (num == 3) { //FIND A PLANE
        findplane();

        
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

//updating all planes, their statuses locations and flights.
void update() {
    for (int i = 0; i < Planes.size(); i++) {
        resettime(false);

        if (Planes[i].flightnum != 0) { //if in a flight rn
            
            //finding our flight
            int myflight = -1; 
            for (int j = 0; j < plannedflights.size(); j++) {
                if (plannedflights[j].getcode() == std::to_string(Planes[i].flightnum)) {
                    myflight = j;
                    break;
                }
            }

            Flight& subject = plannedflights[myflight];

            //updating coordinates
            subject.getPoint(allminutes);
            subject.getaircraft().setcoordinates(subject.getPoint(allminutes));
            std::cout << "\n" << subject.getaircraft().getmodel() << " is located at " << subject.getaircraft().getcoordinates().toString();

            if (allminutes >= subject.landingtime()-1) { //if arrived
                //resetting plane stats
                subject.getaircraft().land();
                subject.getaircraft().flightnum = 0;

                struct UPDATE newupdate = {
                    allminutes,
                    "Arrived",
                    subject,
                    subject.getaircraft(),
                };
                liveupdates.push_back(newupdate);
            }
            

        } else {


            if (Planes[i].flightnum == 0) { //if we don't know next flight

                //finding most recently occured flight
                int lastone = -1;//next flight
                for (int j = 0; j < liveupdates.size(); j++) {
                    if (liveupdates[j].theplane == Planes[i]) {
                        lastone = std::stoi(liveupdates[j].theflight.getcode());
                    }
                }
    
                if (lastone != -1){//making sure we have a valid flight number
                    //finding next flightnum
                    int index;
                    for (int j = 0; j < plannedflights.size(); j++) {
                        if (plannedflights[j].getcode() == std::to_string(lastone)) { //finding index of last flight
                            index = j;
                        }
                    }
                    int temp;
                    for (int j = index+1; j < plannedflights.size(); j++) {
                        if (plannedflights[j].getcode() == std::to_string(lastone)) { //finding index of NEW FLIGHT starting at old flight
                            temp = j;
                            break;
                        }
                    }
                    Flight nextflight = plannedflights[temp];

                    Planes[i].flightnum = std::stoi(nextflight.getcode()); //switching plane num to newest flight ID

                    if (allminutes-2 <= nextflight.liftofftime()) {
                        Planes[i].takeoff(); //switch bool flying to true

                        struct UPDATE newupdatee{
                            allminutes,
                            "Departed",
                            nextflight,
                            nextflight.getaircraft(),
                        };
                        liveupdates.push_back(newupdatee);
                    }

                }
            }        
        }
    }
}
//------------------------------------------------------




//main function
int main(void){
    std::cout << "WELCOME STATEMENT (PLACEHOLDER)\n";
    setup();
    scheduleflights();

    int test = 0;
    while (running) {
        resettime(true);
        menu();
        update();
    }

    return 0;
}