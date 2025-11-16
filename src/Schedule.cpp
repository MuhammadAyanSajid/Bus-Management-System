#include "../include/Schedule.h"
#include <iomanip>

Schedule::Schedule()
    : id(""), routeId(""), busId(""), driverId(""),
      date(""), departureTime(""), arrivalTime("") {}

Schedule::Schedule(const std::string &id, const std::string &routeId,
                   const std::string &busId, const std::string &driverId,
                   const std::string &date, const std::string &departureTime,
                   const std::string &arrivalTime)
    : id(id), routeId(routeId), busId(busId), driverId(driverId),
      date(date), departureTime(departureTime), arrivalTime(arrivalTime) {}

std::string Schedule::getId() const
{
    return id;
}

std::string Schedule::getRouteId() const
{
    return routeId;
}

std::string Schedule::getBusId() const
{
    return busId;
}

std::string Schedule::getDriverId() const
{
    return driverId;
}

std::string Schedule::getDate() const
{
    return date;
}

std::string Schedule::getDepartureTime() const
{
    return departureTime;
}

std::string Schedule::getArrivalTime() const
{
    return arrivalTime;
}

void Schedule::setId(const std::string &id)
{
    this->id = id;
}

void Schedule::setRouteId(const std::string &routeId)
{
    this->routeId = routeId;
}

void Schedule::setBusId(const std::string &busId)
{
    this->busId = busId;
}

void Schedule::setDriverId(const std::string &driverId)
{
    this->driverId = driverId;
}

void Schedule::setDate(const std::string &date)
{
    this->date = date;
}

void Schedule::setDepartureTime(const std::string &departureTime)
{
    this->departureTime = departureTime;
}

void Schedule::setArrivalTime(const std::string &arrivalTime)
{
    this->arrivalTime = arrivalTime;
}

void Schedule::display() const
{
    std::cout << std::left
              << std::setw(12) << id
              << std::setw(12) << routeId
              << std::setw(10) << busId
              << std::setw(12) << driverId
              << std::setw(12) << date
              << std::setw(10) << departureTime
              << std::setw(10) << arrivalTime
              << std::endl;
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
