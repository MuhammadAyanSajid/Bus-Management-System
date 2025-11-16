#include "../include/BusManager.h"
#include "../include/DataSaver.h"
#include "../include/DisplayManager.h"
#include <iostream>
#include <algorithm>

BusManager::BusManager(std::vector<Bus> &busList, const std::string &filename)
    : buses(busList), dataFile(filename) {}

bool BusManager::validateBus(const Bus &bus) const
{
    if (bus.getId().empty())
    {
        std::cout << "Error: Bus ID cannot be empty." << std::endl;
        return false;
    }

    if (bus.getCapacity() <= 0)
    {
        std::cout << "Error: Bus capacity must be positive." << std::endl;
        return false;
    }

    if (bus.getModel().empty())
    {
        std::cout << "Error: Bus model must be provided." << std::endl;
        return false;
    }

    std::string status = bus.getStatus();
    if (status != "Active" && status != "Maintenance" && status != "Inactive")
    {
        std::cout << "Error: Bus status must be Active, Maintenance, or Inactive." << std::endl;
        return false;
    }

    return true;
}

bool BusManager::busExists(const std::string &busId) const
{
    return std::any_of(buses.begin(), buses.end(),
                       [&busId](const Bus &b)
                       { return b.getId() == busId; });
}

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

bool BusManager::addBus(const Bus &newBus)
{
    if (!validateBus(newBus))
    {
        return false;
    }

    if (busExists(newBus.getId()))
    {
        std::cout << "Error: Bus with ID " << newBus.getId() << " already exists." << std::endl;
        return false;
    }

    buses.push_back(newBus);
    std::cout << "Bus " << newBus.getId() << " added successfully." << std::endl;

    return saveToFile();
}

bool BusManager::updateBus(const std::string &busId, const Bus &updatedBus)
{
    Bus *bus = findBus(busId);
    if (!bus)
    {
        std::cout << "Error: Bus with ID " << busId << " not found." << std::endl;
        return false;
    }

    if (!validateBus(updatedBus))
    {
        return false;
    }

    *bus = updatedBus;
    std::cout << "Bus " << busId << " updated successfully." << std::endl;

    return saveToFile();
}

bool BusManager::removeBus(const std::string &busId)
{
    auto it = std::find_if(buses.begin(), buses.end(),
                           [&busId](const Bus &b)
                           { return b.getId() == busId; });

    if (it == buses.end())
    {
        std::cout << "Error: Bus with ID " << busId << " not found." << std::endl;
        return false;
    }

    buses.erase(it);
    std::cout << "Bus " << busId << " removed successfully." << std::endl;

    return saveToFile();
}

bool BusManager::saveToFile()
{
    return DataSaver::saveBuses(dataFile, buses);
}

void BusManager::displayAllBuses() const
{
    DisplayManager::displayBuses(buses);
}
