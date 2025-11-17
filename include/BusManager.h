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
    BusManager(vector<Bus> &busList, const string &filename);

    bool addBus(const Bus &newBus);
    bool updateBus(const string &busId, const Bus &updatedBus);
    bool removeBus(const string &busId);

    Bus *findBus(const string &busId);
    bool busExists(const string &busId) const;

    bool saveToFile();

    void displayAllBuses() const;

    bool validateBus(const Bus &bus) const;
};

#endif 