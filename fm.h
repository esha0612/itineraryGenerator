#ifndef FM_H
#define FM_H
#include "bstset.h"
#include "provided.h"
#include <unordered_map>
#include <iostream>

class FlightManager : public FlightManagerBase{
public:
    FlightManager() {};
    virtual ~FlightManager() {};
    virtual bool load_flight_data(std::string filename);
    virtual std::vector<FlightSegment> find_flights(std::string source_airport, int start_time, int end_time) const;
private:
    std::unordered_map<std::string, BSTSet<FlightSegment>> flights;
    
};
#endif 
