#include "support.h"
#include "bstset.h"
#include "fm.h"
#include "provided.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "support.h"

using namespace std;
bool FlightManager::load_flight_data(std::string filename){
    
    std::ifstream file(filename);
    if (!file)
    {
        std::cerr << "Can't open flight database: " << filename << std::endl;
        return false;
    }
    
    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream ss(line);
        std::string airline, source_airport, destAir;
        int flight_number, deptime, arrival_time, duration;

        getline(ss, airline, ',');
        ss >> flight_number;
        ss.ignore(1, ',');
        getline(ss, source_airport, ',');
        getline(ss, destAir, ',');
        ss >> deptime;
        ss.ignore(1, ',');
        ss >> arrival_time;
        ss.ignore(1, ',');
        ss >> duration;

        FlightSegment flight(airline, flight_number, source_airport,
                             destAir, deptime, duration);

        
        // insert into BSTSet (flights_by_airport[source_airport] creates the BSTSet if it doesn't exist)
        flights[source_airport].insert(flight);
        
    }
    
    return true;
}
std::vector<FlightSegment> FlightManager::find_flights(std::string source_airport, int start_time, int end_time) const {
    std::vector<FlightSegment> result;

    // Check if the source airport exists in the map
    std::unordered_map<std::string, BSTSet<FlightSegment>>::const_iterator it = flights.find(source_airport);
    if (it == flights.end()) {
            return result;
    }
    const BSTSet<FlightSegment>& flight_set = it->second;
    FlightSegment temp("", 0, "", "", start_time, 0);
    BSTSet<FlightSegment>::SetIterator set_it = flight_set.find_first_not_smaller(temp);
    const FlightSegment *flight;
    while (((flight = set_it.get_and_advance()) != nullptr) && (flight->departure_time < end_time)){
        result.push_back(*flight);
    }
    return result;
}
