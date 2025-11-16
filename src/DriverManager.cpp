#include "../include/DriverManager.h"
#include "../include/DataSaver.h"
#include "../include/DisplayManager.h"
#include <iostream>
#include <algorithm>

using namespace std;

DriverManager::DriverManager(vector<Driver> &driverList, const string &filename)
    : drivers(driverList), dataFile(filename) {}

bool DriverManager::validateDriver(const Driver &driver) const
{
    if (driver.getId().empty())
    {
        cout << "Error: Driver ID cannot be empty." << endl;
        return false;
    }

    if (driver.getName().empty())
    {
        cout << "Error: Driver name must be provided." << endl;
        return false;
    }

    if (driver.getContactInfo().empty())
    {
        cout << "Error: Driver contact information must be provided." << endl;
        return false;
    }

    if (driver.getLicenseDetails().empty())
    {
        cout << "Error: Driver license details must be provided." << endl;
        return false;
    }

    return true;
}

bool DriverManager::driverExists(const string &driverId) const
{
    return any_of(drivers.begin(), drivers.end(),
                  [&driverId](const Driver &d)
                  { return d.getId() == driverId; });
}

Driver *DriverManager::findDriver(const string &driverId)
{
    auto it = find_if(drivers.begin(), drivers.end(),
                      [&driverId](const Driver &d)
                      { return d.getId() == driverId; });

    if (it != drivers.end())
    {
        return &(*it);
    }
    return nullptr;
}

bool DriverManager::addDriver(const Driver &newDriver)
{
    if (!validateDriver(newDriver))
    {
        return false;
    }

    if (driverExists(newDriver.getId()))
    {
        cout << "Error: Driver with ID " << newDriver.getId() << " already exists." << endl;
        return false;
    }

    drivers.push_back(newDriver);
    cout << "Driver " << newDriver.getId() << " added successfully." << endl;

    return saveToFile();
}

bool DriverManager::updateDriver(const string &driverId, const Driver &updatedDriver)
{
    Driver *driver = findDriver(driverId);
    if (!driver)
    {
        cout << "Error: Driver with ID " << driverId << " not found." << endl;
        return false;
    }

    if (!validateDriver(updatedDriver))
    {
        return false;
    }

    *driver = updatedDriver;
    cout << "Driver " << driverId << " updated successfully." << endl;

    return saveToFile();
}

bool DriverManager::removeDriver(const string &driverId)
{
    auto it = find_if(drivers.begin(), drivers.end(),
                      [&driverId](const Driver &d)
                      { return d.getId() == driverId; });

    if (it == drivers.end())
    {
        cout << "Error: Driver with ID " << driverId << " not found." << endl;
        return false;
    }

    drivers.erase(it);
    cout << "Driver " << driverId << " removed successfully." << endl;

    return saveToFile();
}

bool DriverManager::saveToFile()
{
    return DataSaver::saveDrivers(dataFile, drivers);
}

void DriverManager::displayAllDrivers() const
{
    DisplayManager::displayDrivers(drivers);
}
