
#ifndef SUPPORT_H
#define SUPPORT_H
#include "provided.h"

inline bool operator<(const FlightSegment& a, const FlightSegment& b);

inline bool operator<(const FlightSegment& a, const FlightSegment& b) {
    return a.departure_time < b.departure_time;
}
inline bool operator<=(const FlightSegment& a, const FlightSegment& b) {
    return a.departure_time <= b.departure_time;
}
#endif
