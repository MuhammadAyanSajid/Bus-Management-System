#include "../include/BusManager.h"
#include "../include/DataSaver.h"
#include "../include/DisplayManager.h"
#include <iostream>
#include <algorithm>

// Constructor
BusManager::BusManager(std::vector<Bus> &busList, const std::string &filename)
    : buses(busList), dataFile(filename) {}

// Validate bus
bool BusManager::validateBus(const Bus &bus) const
{
    // Check if ID is not empty
    if (bus.getId().empty())
    {
        std::cout << "Error: Bus ID cannot be empty." << std::endl;
        return false;
    }

    // Check if capacity is positive
    if (bus.getCapacity() <= 0)
    {
        std::cout << "Error: Bus capacity must be positive." << std::endl;
        return false;
    }

    // Check if model is provided
    if (bus.getModel().empty())
    {
        std::cout << "Error: Bus model must be provided." << std::endl;
        return false;
    }

    // Check if status is valid
    std::string status = bus.getStatus();
    if (status != "Active" && status != "Maintenance" && status != "Inactive")
    {
        std::cout << "Error: Bus status must be Active, Maintenance, or Inactive." << std::endl;
        return false;
    }

    return true;
}

// Check if bus exists
bool BusManager::busExists(const std::string &busId) const
{
    return std::any_of(buses.begin(), buses.end(),
                       [&busId](const Bus &b)
                       { return b.getId() == busId; });
}

// Find bus by ID
Bus *BusManager::findBus(const std::string &busId)
{
    auto it = std::find_if(buses.begin(), buses.end(),
                           [&busId](const Bus &b)
                           { return b.getId() == busId; });

    if (it != buses.end())
    {
        return &(*it);
    }
    return nullptr;
}

// Add new bus
bool BusManager::addBus(const Bus &newBus)
{
    // Validate bus
    if (!validateBus(newBus))
    {
        return false;
    }

    // Check if bus ID already exists
    if (busExists(newBus.getId()))
    {
        std::cout << "Error: Bus with ID " << newBus.getId() << " already exists." << std::endl;
        return false;
    }

    // Add bus
    buses.push_back(newBus);
    std::cout << "Bus " << newBus.getId() << " added successfully." << std::endl;

    // Save to file
    return saveToFile();
}

// Update existing bus
bool BusManager::updateBus(const std::string &busId, const Bus &updatedBus)
{
    // Find bus
    Bus *bus = findBus(busId);
    if (!bus)
    {
        std::cout << "Error: Bus with ID " << busId << " not found." << std::endl;
        return false;
    }

    // Validate updated bus
    if (!validateBus(updatedBus))
    {
        return false;
    }

    // Update bus
    *bus = updatedBus;
    std::cout << "Bus " << busId << " updated successfully." << std::endl;

    // Save to file
    return saveToFile();
}

// Remove bus
bool BusManager::removeBus(const std::string &busId)
{
    // Find bus
    auto it = std::find_if(buses.begin(), buses.end(),
                           [&busId](const Bus &b)
                           { return b.getId() == busId; });

    if (it == buses.end())
    {
        std::cout << "Error: Bus with ID " << busId << " not found." << std::endl;
        return false;
    }

    // Remove bus
    buses.erase(it);
    std::cout << "Bus " << busId << " removed successfully." << std::endl;

    // Save to file
    return saveToFile();
}

// Save to file
bool BusManager::saveToFile()
{
    return DataSaver::saveBuses(dataFile, buses);
}

// Display all buses
void BusManager::displayAllBuses() const
{
    DisplayManager::displayBuses(buses);
}
