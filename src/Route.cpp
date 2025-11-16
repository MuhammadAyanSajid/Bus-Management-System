#include "../include/Route.h"
#include <iomanip>
#include <sstream>

Route::Route() : id(""), origin(""), destination(""), estimatedTravelTime(0) {}
Route::Route(const std::string &id, const std::string &origin,
             const std::string &destination, const std::vector<std::string> &keyStops,
             int estimatedTravelTime)
    : id(id), origin(origin), destination(destination),
      keyStops(keyStops), estimatedTravelTime(estimatedTravelTime) {}

std::string Route::getId() const
{
    return id;
}

std::string Route::getOrigin() const
{
    return origin;
}

std::string Route::getDestination() const
{
    return destination;
}

std::vector<std::string> Route::getKeyStops() const
{
    return keyStops;
}

int Route::getEstimatedTravelTime() const
{
    return estimatedTravelTime;
}

void Route::setId(const std::string &id)
{
    this->id = id;
}

void Route::setOrigin(const std::string &origin)
{
    this->origin = origin;
}

void Route::setDestination(const std::string &destination)
{
    this->destination = destination;
}

void Route::setKeyStops(const std::vector<std::string> &keyStops)
{
    this->keyStops = keyStops;
}

void Route::setEstimatedTravelTime(int estimatedTravelTime)
{
    this->estimatedTravelTime = estimatedTravelTime;
}

void Route::addStop(const std::string &stop)
{
    keyStops.push_back(stop);
}

void Route::display() const
{
    std::cout << std::left
              << std::setw(10) << id
              << std::setw(15) << origin
              << std::setw(15) << destination
              << std::setw(40) << getStopsAsString()
              << std::setw(10) << estimatedTravelTime
              << std::endl;
}

std::string Route::getStopsAsString() const
{
    std::stringstream ss;
    for (size_t i = 0; i < keyStops.size(); ++i)
    {
        ss << keyStops[i];
        if (i < keyStops.size() - 1)
        {
            ss << "|";
        }
    }
    return ss.str();
}
