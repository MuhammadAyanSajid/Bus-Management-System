#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <string>
#include <iostream>

class Schedule {
private:
    std::string id;
    std::string routeId;
    std::string busId;
    std::string driverId;
    std::string date;         // Format: YYYY-MM-DD
    std::string departureTime; // Format: HH:MM
    std::string arrivalTime;   // Format: HH:MM

public:
    // Constructors
    Schedule();
    Schedule(const std::string& id, const std::string& routeId, 
             const std::string& busId, const std::string& driverId,
             const std::string& date, const std::string& departureTime,
             const std::string& arrivalTime);
    
    // Getters
    std::string getId() const;
    std::string getRouteId() const;
    std::string getBusId() const;
    std::string getDriverId() const;
    std::string getDate() const;
    std::string getDepartureTime() const;
    std::string getArrivalTime() const;
    
    // Setters
    void setId(const std::string& id);
    void setRouteId(const std::string& routeId);
    void setBusId(const std::string& busId);
    void setDriverId(const std::string& driverId);
    void setDate(const std::string& date);
    void setDepartureTime(const std::string& departureTime);
    void setArrivalTime(const std::string& arrivalTime);
    
    // Display function
    void display() const;
    
    // Helper function to check for time overlap
    bool hasTimeOverlap(const Schedule& other) const;
};

#endif // SCHEDULE_H