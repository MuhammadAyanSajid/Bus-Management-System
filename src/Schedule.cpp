#include "../include/Schedule.h"
#include <iomanip>

using namespace std;

Schedule::Schedule()
    : id(""), routeId(""), busId(""), driverId(""),
      date(""), departureTime(""), arrivalTime("") {}

Schedule::Schedule(const string &id, const string &routeId,
                   const string &busId, const string &driverId,
                   const string &date, const string &departureTime,
                   const string &arrivalTime)
    : id(id), routeId(routeId), busId(busId), driverId(driverId),
      date(date), departureTime(departureTime), arrivalTime(arrivalTime) {}

string Schedule::getId() const
{
    return id;
}

string Schedule::getRouteId() const
{
    return routeId;
}

string Schedule::getBusId() const
{
    return busId;
}

string Schedule::getDriverId() const
{
    return driverId;
}

string Schedule::getDate() const
{
    return date;
}

string Schedule::getDepartureTime() const
{
    return departureTime;
}

string Schedule::getArrivalTime() const
{
    return arrivalTime;
}

void Schedule::setId(const string &id)
{
    this->id = id;
}

void Schedule::setRouteId(const string &routeId)
{
    this->routeId = routeId;
}

void Schedule::setBusId(const string &busId)
{
    this->busId = busId;
}

void Schedule::setDriverId(const string &driverId)
{
    this->driverId = driverId;
}

void Schedule::setDate(const string &date)
{
    this->date = date;
}

void Schedule::setDepartureTime(const string &departureTime)
{
    this->departureTime = departureTime;
}

void Schedule::setArrivalTime(const string &arrivalTime)
{
    this->arrivalTime = arrivalTime;
}

void Schedule::display() const
{
    cout << left
         << setw(12) << id
         << setw(12) << routeId
         << setw(10) << busId
         << setw(12) << driverId
         << setw(12) << date
         << setw(10) << departureTime
         << setw(10) << arrivalTime
         << endl;
}

bool Schedule::hasTimeOverlap(const Schedule &other) const
{
    if (this->date != other.date)
    {
        return false;
    }

    return !((this->arrivalTime <= other.departureTime) ||
             (this->departureTime >= other.arrivalTime));
}
