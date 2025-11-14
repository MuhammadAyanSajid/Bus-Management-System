#include "../include/DriverManager.h"
#include "../include/DataSaver.h"
#include "../include/DisplayManager.h"
#include <iostream>
#include <algorithm>

// Constructor
DriverManager::DriverManager(std::vector<Driver> &driverList, const std::string &filename)
    : drivers(driverList), dataFile(filename) {}

// Validate driver
bool DriverManager::validateDriver(const Driver &driver) const
{
    // Check if ID is not empty
    if (driver.getId().empty())
    {
        std::cout << "Error: Driver ID cannot be empty." << std::endl;
        return false;
    }

    // Check if name is provided
    if (driver.getName().empty())
    {
        std::cout << "Error: Driver name must be provided." << std::endl;
        return false;
    }

    // Check if contact info is provided
    if (driver.getContactInfo().empty())
    {
        std::cout << "Error: Driver contact information must be provided." << std::endl;
        return false;
    }

    // Check if license details are provided
    if (driver.getLicenseDetails().empty())
    {
        std::cout << "Error: Driver license details must be provided." << std::endl;
        return false;
    }

    return true;
}

// Check if driver exists
bool DriverManager::driverExists(const std::string &driverId) const
{
    return std::any_of(drivers.begin(), drivers.end(),
                       [&driverId](const Driver &d)
                       { return d.getId() == driverId; });
}

// Find driver by ID
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

// Add new driver
bool DriverManager::addDriver(const Driver &newDriver)
{
    // Validate driver
    if (!validateDriver(newDriver))
    {
        return false;
    }

    // Check if driver ID already exists
    if (driverExists(newDriver.getId()))
    {
        std::cout << "Error: Driver with ID " << newDriver.getId() << " already exists." << std::endl;
        return false;
    }

    // Add driver
    drivers.push_back(newDriver);
    std::cout << "Driver " << newDriver.getId() << " added successfully." << std::endl;

    // Save to file
    return saveToFile();
}

// Update existing driver
bool DriverManager::updateDriver(const std::string &driverId, const Driver &updatedDriver)
{
    // Find driver
    Driver *driver = findDriver(driverId);
    if (!driver)
    {
        std::cout << "Error: Driver with ID " << driverId << " not found." << std::endl;
        return false;
    }

    // Validate updated driver
    if (!validateDriver(updatedDriver))
    {
        return false;
    }

    // Update driver
    *driver = updatedDriver;
    std::cout << "Driver " << driverId << " updated successfully." << std::endl;

    // Save to file
    return saveToFile();
}

// Remove driver
bool DriverManager::removeDriver(const std::string &driverId)
{
    // Find driver
    auto it = std::find_if(drivers.begin(), drivers.end(),
                           [&driverId](const Driver &d)
                           { return d.getId() == driverId; });

    if (it == drivers.end())
    {
        std::cout << "Error: Driver with ID " << driverId << " not found." << std::endl;
        return false;
    }

    // Remove driver
    drivers.erase(it);
    std::cout << "Driver " << driverId << " removed successfully." << std::endl;

    // Save to file
    return saveToFile();
}

// Save to file
bool DriverManager::saveToFile()
{
    return DataSaver::saveDrivers(dataFile, drivers);
}

// Display all drivers
void DriverManager::displayAllDrivers() const
{
    DisplayManager::displayDrivers(drivers);
}
