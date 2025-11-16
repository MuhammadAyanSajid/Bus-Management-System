#include "../include/DriverManager.h"
#include "../include/DataSaver.h"
#include "../include/DisplayManager.h"
#include <iostream>
#include <algorithm>

DriverManager::DriverManager(std::vector<Driver> &driverList, const std::string &filename)
    : drivers(driverList), dataFile(filename) {}

bool DriverManager::validateDriver(const Driver &driver) const
{
    if (driver.getId().empty())
    {
        std::cout << "Error: Driver ID cannot be empty." << std::endl;
        return false;
    }

    if (driver.getName().empty())
    {
        std::cout << "Error: Driver name must be provided." << std::endl;
        return false;
    }

    if (driver.getContactInfo().empty())
    {
        std::cout << "Error: Driver contact information must be provided." << std::endl;
        return false;
    }

    if (driver.getLicenseDetails().empty())
    {
        std::cout << "Error: Driver license details must be provided." << std::endl;
        return false;
    }

    return true;
}

bool DriverManager::driverExists(const std::string &driverId) const
{
    return std::any_of(drivers.begin(), drivers.end(),
                       [&driverId](const Driver &d)
                       { return d.getId() == driverId; });
}

Driver *DriverManager::findDriver(const std::string &driverId)
{
    auto it = std::find_if(drivers.begin(), drivers.end(),
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
        std::cout << "Error: Driver with ID " << newDriver.getId() << " already exists." << std::endl;
        return false;
    }

    drivers.push_back(newDriver);
    std::cout << "Driver " << newDriver.getId() << " added successfully." << std::endl;

    return saveToFile();
}

bool DriverManager::updateDriver(const std::string &driverId, const Driver &updatedDriver)
{
    Driver *driver = findDriver(driverId);
    if (!driver)
    {
        std::cout << "Error: Driver with ID " << driverId << " not found." << std::endl;
        return false;
    }

    if (!validateDriver(updatedDriver))
    {
        return false;
    }

    *driver = updatedDriver;
    std::cout << "Driver " << driverId << " updated successfully." << std::endl;

    return saveToFile();
}

bool DriverManager::removeDriver(const std::string &driverId)
{
    auto it = std::find_if(drivers.begin(), drivers.end(),
                           [&driverId](const Driver &d)
                           { return d.getId() == driverId; });

    if (it == drivers.end())
    {
        std::cout << "Error: Driver with ID " << driverId << " not found." << std::endl;
        return false;
    }

    drivers.erase(it);
    std::cout << "Driver " << driverId << " removed successfully." << std::endl;

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
