#ifndef ROUTE_H
#define ROUTE_H

#include <string>
#include <vector>
#include <iostream>

using std::string;
using std::vector;

class Route
{
private:
    string id;
    string origin;
    string destination;
    vector<string> keyStops;
    int estimatedTravelTime;

public:
    Route();
    Route(const string &id, const string &origin,
          const string &destination, const vector<string> &keyStops,
          int estimatedTravelTime);

    string getId() const;
    string getOrigin() const;
    string getDestination() const;
    vector<string> getKeyStops() const;
    int getEstimatedTravelTime() const;

    void setId(const string &id);
    void setOrigin(const string &origin);
    void setDestination(const string &destination);
    void setKeyStops(const vector<string> &keyStops);
    void setEstimatedTravelTime(int estimatedTravelTime);

    void addStop(const string &stop);
    void display() const;
    string getStopsAsString() const;
};

#endif