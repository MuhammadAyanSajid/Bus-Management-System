#ifndef BUSMANAGER_H
#define BUSMANAGER_H

#include <string>
#include <vector>
#include "Bus.h"

class BusManager
{
private:
    std::vector<Bus> &buses;
    std::string dataFile;

public:
    // Constructor
    BusManager(std::vector<Bus> &busList, const std::string &filename);

    // CRUD operations
    bool addBus(const Bus &newBus);
    bool updateBus(const std::string &busId, const Bus &updatedBus);
    bool removeBus(const std::string &busId);

    // Query operations
    Bus *findBus(const std::string &busId);
    bool busExists(const std::string &busId) const;

    // Save to file
    bool saveToFile();

    // Display all buses
    void displayAllBuses() const;

    // Validation
    bool validateBus(const Bus &bus) const;
};

#endif // BUSMANAGER_H
