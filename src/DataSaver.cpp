#include "../include/DataSaver.h"
#include <fstream>
#include <iostream>

// Save buses to file
bool DataSaver::saveBuses(const std::string &filename, const std::vector<Bus> &buses)
{
    std::ofstream file(filename);

    if (!file.is_open())
    {
        std::cerr << "Error: Could not open file " << filename << " for writing." << std::endl;
        return false;
    }

    for (const auto &bus : buses)
    {
        file << bus.getId() << ","
             << bus.getCapacity() << ","
             << bus.getModel() << ","
             << bus.getStatus() << std::endl;
    }

    file.close();
    std::cout << "Successfully saved " << buses.size() << " buses to " << filename << std::endl;
    return true;
}

// Save drivers to file
bool DataSaver::saveDrivers(const std::string &filename, const std::vector<Driver> &drivers)
{
    std::ofstream file(filename);

    if (!file.is_open())
    {
        std::cerr << "Error: Could not open file " << filename << " for writing." << std::endl;
        return false;
    }

    for (const auto &driver : drivers)
    {
        file << driver.getId() << ","
             << driver.getName() << ","
             << driver.getContactInfo() << ","
             << driver.getLicenseDetails() << std::endl;
    }

    file.close();
    std::cout << "Successfully saved " << drivers.size() << " drivers to " << filename << std::endl;
    return true;
}

// Save routes to file
bool DataSaver::saveRoutes(const std::string &filename, const std::vector<Route> &routes)
{
    std::ofstream file(filename);

    if (!file.is_open())
    {
        std::cerr << "Error: Could not open file " << filename << " for writing." << std::endl;
        return false;
    }

    for (const auto &route : routes)
    {
        file << route.getId() << ","
             << route.getOrigin() << ","
             << route.getDestination() << ","
             << route.getStopsAsString() << ","
             << route.getEstimatedTravelTime() << std::endl;
    }

    file.close();
    std::cout << "Successfully saved " << routes.size() << " routes to " << filename << std::endl;
    return true;
}

// Save schedules to file
bool DataSaver::saveSchedules(const std::string &filename, const std::vector<Schedule> &schedules)
{
    std::ofstream file(filename);

    if (!file.is_open())
    {
        std::cerr << "Error: Could not open file " << filename << " for writing." << std::endl;
        return false;
    }

    for (const auto &schedule : schedules)
    {
        file << schedule.getId() << ","
             << schedule.getRouteId() << ","
             << schedule.getBusId() << ","
             << schedule.getDriverId() << ","
             << schedule.getDate() << ","
             << schedule.getDepartureTime() << ","
             << schedule.getArrivalTime() << std::endl;
    }

    file.close();
    std::cout << "Successfully saved " << schedules.size() << " schedules to " << filename << std::endl;
    return true;
}

// Save user credentials to file
bool DataSaver::saveCredentials(const std::string &filename, const std::vector<User> &users)
{
    std::ofstream file(filename);

    if (!file.is_open())
    {
        std::cerr << "Error: Could not open file " << filename << " for writing." << std::endl;
        return false;
    }

    for (const auto &user : users)
    {
        file << user.getUsername() << ","
             << user.getPassword() << ","
             << user.getRoleString() << std::endl;
    }

    file.close();
    std::cout << "Successfully saved " << users.size() << " users to " << filename << std::endl;
    return true;
}
