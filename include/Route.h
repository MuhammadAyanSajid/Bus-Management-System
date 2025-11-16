#ifndef ROUTE_H
#define ROUTE_H

#include <string>
#include <vector>
#include <iostream>

class Route
{
private:
    std::string id;
    std::string origin;
    std::string destination;
    std::vector<std::string> keyStops;
    int estimatedTravelTime;

public:
    Route();
    Route(const std::string &id, const std::string &origin,
          const std::string &destination, const std::vector<std::string> &keyStops,
          int estimatedTravelTime);

    std::string getId() const;
    std::string getOrigin() const;
    std::string getDestination() const;
    std::vector<std::string> getKeyStops() const;
    int getEstimatedTravelTime() const;

    void setId(const std::string &id);
    void setOrigin(const std::string &origin);
    void setDestination(const std::string &destination);
    void setKeyStops(const std::vector<std::string> &keyStops);
    void setEstimatedTravelTime(int estimatedTravelTime);

    void addStop(const std::string &stop);
    void display() const;
    std::string getStopsAsString() const;
};

#endif // ROUTE_H