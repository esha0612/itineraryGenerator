
#ifndef TP_H
#define TP_H
#include "provided.h"
#include <unordered_set>
#include <queue>


class TravelPlanner: public TravelPlannerBase{
    
public:
    TravelPlanner(const FlightManagerBase& flight_manager, const AirportDB& airport_db): TravelPlannerBase(flight_manager, airport_db) {};
    
    ~TravelPlanner() {};
    void add_preferred_airline(std::string airline);
    bool plan_travel(std::string source_airport, std::string destination_airport, int start_time, Itinerary& itinerary) const;
    int heuristic_cost(const std::string& current_airport, const std::string& destination_airport) const;
private:
    std::unordered_set<std::string> preferred_airlines;
    std::vector<FlightSegment> get_available_flights(const std::string& airport, int start_time, int end_time) const;
    
};
#endif
