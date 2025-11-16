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
    // Constructor
    DriverManager(vector<Driver> &driverList, const string &filename);

    // CRUD operations
    bool addDriver(const Driver &newDriver);
    bool updateDriver(const string &driverId, const Driver &updatedDriver);
    bool removeDriver(const string &driverId);

    // Query operations
    Driver *findDriver(const string &driverId);
    bool driverExists(const string &driverId) const;

    // Save to file
    bool saveToFile();

    // Display all drivers
    void displayAllDrivers() const;

    // Validation
    bool validateDriver(const Driver &driver) const;
};

#endif // DRIVERMANAGER_H
