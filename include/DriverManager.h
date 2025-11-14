#ifndef DRIVERMANAGER_H
#define DRIVERMANAGER_H

#include <string>
#include <vector>
#include "Driver.h"

class DriverManager
{
private:
    std::vector<Driver> &drivers;
    std::string dataFile;

public:
    // Constructor
    DriverManager(std::vector<Driver> &driverList, const std::string &filename);

    // CRUD operations
    bool addDriver(const Driver &newDriver);
    bool updateDriver(const std::string &driverId, const Driver &updatedDriver);
    bool removeDriver(const std::string &driverId);

    // Query operations
    Driver *findDriver(const std::string &driverId);
    bool driverExists(const std::string &driverId) const;

    // Save to file
    bool saveToFile();

    // Display all drivers
    void displayAllDrivers() const;

    // Validation
    bool validateDriver(const Driver &driver) const;
};

#endif // DRIVERMANAGER_H
