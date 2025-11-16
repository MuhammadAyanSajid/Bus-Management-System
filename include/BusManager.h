#ifndef BUSMANAGER_H
#define BUSMANAGER_H

#include <string>
#include <vector>
#include "Bus.h"

using std::string;
using std::vector;

class BusManager
{
private:
    vector<Bus> &buses;
    string dataFile;

public:
    // Constructor
    BusManager(vector<Bus> &busList, const string &filename);

    // CRUD operations
    bool addBus(const Bus &newBus);
    bool updateBus(const string &busId, const Bus &updatedBus);
    bool removeBus(const string &busId);

    // Query operations
    Bus *findBus(const string &busId);
    bool busExists(const string &busId) const;

    // Save to file
    bool saveToFile();

    // Display all buses
    void displayAllBuses() const;

    // Validation
    bool validateBus(const Bus &bus) const;
};

#endif // BUSMANAGER_H
