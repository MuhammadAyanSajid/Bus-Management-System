#include "../include/Route.h"
#include <iomanip>
#include <sstream>

using namespace std;

Route::Route() : id(""), origin(""), destination(""), estimatedTravelTime(0) {}
Route::Route(const string &id, const string &origin,
             const string &destination, const vector<string> &keyStops,
             int estimatedTravelTime)
    : id(id), origin(origin), destination(destination),
      keyStops(keyStops), estimatedTravelTime(estimatedTravelTime) {}

string Route::getId() const
{
    return id;
}

string Route::getOrigin() const
{
    return origin;
}

string Route::getDestination() const
{
    return destination;
}

vector<string> Route::getKeyStops() const
{
    return keyStops;
}

int Route::getEstimatedTravelTime() const
{
    return estimatedTravelTime;
}

void Route::setId(const string &id)
{
    this->id = id;
}

void Route::setOrigin(const string &origin)
{
    this->origin = origin;
}

void Route::setDestination(const string &destination)
{
    this->destination = destination;
}

void Route::setKeyStops(const vector<string> &keyStops)
{
    this->keyStops = keyStops;
}

void Route::setEstimatedTravelTime(int estimatedTravelTime)
{
    this->estimatedTravelTime = estimatedTravelTime;
}

void Route::addStop(const string &stop)
{
    keyStops.push_back(stop);
}

void Route::display() const
{
    cout << left
         << setw(10) << id
         << setw(15) << origin
         << setw(15) << destination
         << setw(40) << getStopsAsString()
         << setw(10) << estimatedTravelTime
         << endl;
}

string Route::getStopsAsString() const
{
    stringstream ss;
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
