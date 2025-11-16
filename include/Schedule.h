#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <string>
#include <iostream>

using std::string;

class Schedule
{
private:
    string id;
    string routeId;
    string busId;
    string driverId;
    string date;
    string departureTime;
    string arrivalTime;

public:
    Schedule();
    Schedule(const string &id, const string &routeId,
             const string &busId, const string &driverId,
             const string &date, const string &departureTime,
             const string &arrivalTime);

    string getId() const;
    string getRouteId() const;
    string getBusId() const;
    string getDriverId() const;
    string getDate() const;
    string getDepartureTime() const;
    string getArrivalTime() const;

    void setId(const string &id);
    void setRouteId(const string &routeId);
    void setBusId(const string &busId);
    void setDriverId(const string &driverId);
    void setDate(const string &date);
    void setDepartureTime(const string &departureTime);
    void setArrivalTime(const string &arrivalTime);

    void display() const;

    bool hasTimeOverlap(const Schedule &other) const;
};

#endif