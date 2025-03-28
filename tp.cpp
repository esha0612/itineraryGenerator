
#include "tp.h"
#include "fm.h"
#include "support.h"
#include "bstset.h"
#include "provided.h"
#include <string>
#include <queue>

#include <unordered_set>
#include <unordered_map>


void TravelPlanner::add_preferred_airline(std::string airline){
    preferred_airlines.insert(airline);
}

bool TravelPlanner::plan_travel(std::string source_airport, std::string destination_airport, int start_time, Itinerary& itinerary) const {
    std::queue<std::vector<FlightSegment>> currentFlights;
    std::unordered_map<std::string, std::unordered_set<int>> visited;
    
    std::vector<FlightSegment> allFlights = get_available_flights(source_airport, start_time, start_time + get_max_layover());
    
    //initialize queue with starting flights
    for (const FlightSegment& flight : allFlights) {
        currentFlights.push({flight});
        visited[flight.destination_airport].insert(flight.departure_time);
    }
    
    while (!currentFlights.empty()) {
        std::vector<FlightSegment> currentPath = currentFlights.front();
        currentFlights.pop();
        
        FlightSegment prevFlight = currentPath.back();
        
        if (prevFlight.destination_airport == destination_airport) {
            itinerary.source_airport = source_airport;
            itinerary.destination_airport = destination_airport;
            itinerary.flights = currentPath;
            itinerary.total_duration =  prevFlight.departure_time + prevFlight.duration_sec - start_time;
            return true;
        }

        int next_start = prevFlight.departure_time + prevFlight.duration_sec + get_min_connection_time();
        int next_end = prevFlight.departure_time + prevFlight.duration_sec + get_max_layover();
        std::vector<FlightSegment> nextFlights = get_available_flights(prevFlight.destination_airport, next_start, next_end);
        
        for (const FlightSegment& flight : nextFlights) {
            int totalDuration = flight.duration_sec + (currentPath.empty() ? 0 : currentPath.back().duration_sec);
            if (totalDuration <= get_max_duration()) {
                if (visited[flight.destination_airport].find(flight.departure_time) == visited[flight.destination_airport].end()) {
                    std::vector<FlightSegment> newPath = currentPath;
                    newPath.push_back(flight);
                    currentFlights.push(newPath);
                    visited[flight.destination_airport].insert(flight.departure_time);
                }
            }
        }
    }
    return false;
}

std::vector<FlightSegment> TravelPlanner::get_available_flights(const std::string& airport, int start_time, int end_time) const {
    std::vector<FlightSegment> flights;
    auto all_flights = get_flight_manager().find_flights(airport, start_time, end_time);
    
    if (!preferred_airlines.empty()) {
        for (const auto& flight : all_flights) {
            if (preferred_airlines.find(flight.airline) != preferred_airlines.end()) {
                flights.push_back(flight);
            }
        }
    } else {
        flights = all_flights;
    }
    
    return flights;
}
