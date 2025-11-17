#ifndef DRIVERMANAGER_H
#define DRIVERMANAGER_H

#include <string>
#include <vector>
#include "Driver.h"

using std::string;
using std::vector;

class DriverManager
{
private:
    vector<Driver> &drivers;
    string dataFile;

public:
    DriverManager(vector<Driver> &driverList, const string &filename);

    bool addDriver(const Driver &newDriver);
    bool updateDriver(const string &driverId, const Driver &updatedDriver);
    bool removeDriver(const string &driverId);

    Driver *findDriver(const string &driverId);
    bool driverExists(const string &driverId) const;

    bool saveToFile();

    void displayAllDrivers() const;

    bool validateDriver(const Driver &driver) const;
};

#endif 
