#ifndef BUS_H
#define BUS_H

#include <string>
#include <iostream>

class Bus {
private:
    std::string id;
    int capacity;
    std::string model;
    std::string status; // Active, Maintenance, Inactive

public:
    // Constructors
    Bus();
    Bus(const std::string& id, int capacity, const std::string& model, const std::string& status);
    
    // Getters
    std::string getId() const;
    int getCapacity() const;
    std::string getModel() const;
    std::string getStatus() const;
    
    // Setters
    void setId(const std::string& id);
    void setCapacity(int capacity);
    void setModel(const std::string& model);
    void setStatus(const std::string& status);
    
    // Display function
    void display() const;
};

#endif // BUS_H