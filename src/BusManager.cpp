#include "../include/BusManager.h"
#include "../include/DataSaver.h"
#include "../include/DisplayManager.h"
#include <iostream>
#include <algorithm>

using namespace std;

BusManager::BusManager(vector<Bus> &busList, const string &filename)
    : buses(busList), dataFile(filename) {}

bool BusManager::validateBus(const Bus &bus) const
{
    if (bus.getId().empty())
    {
        cout << "Error: Bus ID cannot be empty." << endl;
        return false;
    }

    if (bus.getCapacity() <= 0)
    {
        cout << "Error: Bus capacity must be positive." << endl;
        return false;
    }

    if (bus.getModel().empty())
    {
        cout << "Error: Bus model must be provided." << endl;
        return false;
    }

    string status = bus.getStatus();
    if (status != "Active" && status != "Maintenance" && status != "Inactive")
    {
        cout << "Error: Bus status must be Active, Maintenance, or Inactive." << endl;
        return false;
    }

    return true;
}

bool BusManager::busExists(const string &busId) const
{
    return any_of(buses.begin(), buses.end(),
                  [&busId](const Bus &b)
                  { return b.getId() == busId; });
}

Bus *BusManager::findBus(const string &busId)
{
    auto it = find_if(buses.begin(), buses.end(),
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
        cout << "Error: Bus with ID " << newBus.getId() << " already exists." << endl;
        return false;
    }

    buses.push_back(newBus);
    cout << "Bus " << newBus.getId() << " added successfully." << endl;

    return saveToFile();
}

bool BusManager::updateBus(const string &busId, const Bus &updatedBus)
{
    Bus *bus = findBus(busId);
    if (!bus)
    {
        cout << "Error: Bus with ID " << busId << " not found." << endl;
        return false;
    }

    if (!validateBus(updatedBus))
    {
        return false;
    }

    *bus = updatedBus;
    cout << "Bus " << busId << " updated successfully." << endl;

    return saveToFile();
}

bool BusManager::removeBus(const string &busId)
{
    auto it = find_if(buses.begin(), buses.end(),
                      [&busId](const Bus &b)
                      { return b.getId() == busId; });

    if (it == buses.end())
    {
        cout << "Error: Bus with ID " << busId << " not found." << endl;
        return false;
    }

    buses.erase(it);
    cout << "Bus " << busId << " removed successfully." << endl;

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
