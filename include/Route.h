#ifndef ROUTE_H
#define ROUTE_H

#include <string>
#include <vector>
#include <iostream>

class Route {
private:
    std::string id;
    std::string origin;
    std::string destination;
    std::vector<std::string> keyStops;
    int estimatedTravelTime; // in minutes

public:
    // Constructors
    Route();
    Route(const std::string& id, const std::string& origin, 
          const std::string& destination, const std::vector<std::string>& keyStops,
          int estimatedTravelTime);
    
    // Getters
    std::string getId() const;
    std::string getOrigin() const;
    std::string getDestination() const;
    std::vector<std::string> getKeyStops() const;
    int getEstimatedTravelTime() const;
    
    // Setters
    void setId(const std::string& id);
    void setOrigin(const std::string& origin);
    void setDestination(const std::string& destination);
    void setKeyStops(const std::vector<std::string>& keyStops);
    void setEstimatedTravelTime(int estimatedTravelTime);
    
    // Helper functions
    void addStop(const std::string& stop);
    void display() const;
    std::string getStopsAsString() const; // For CSV export
};

#endif // ROUTE_H