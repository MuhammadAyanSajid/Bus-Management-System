#include "../include/DisplayManager.h"
#include <iostream>
#include <iomanip>

void DisplayManager::printSeparator(int width)
{
    std::cout << std::string(width, '=') << std::endl;
}

void DisplayManager::printHeader(const std::string &title)
{
    printSeparator();
    std::cout << "| " << std::left << std::setw(96) << title << " |" << std::endl;
    printSeparator();
}

void DisplayManager::displayBuses(const std::vector<Bus> &buses)
{
    printHeader("BUS INFORMATION");

    if (buses.empty())
    {
        std::cout << "No buses found." << std::endl;
        printSeparator();
        return;
    }

    std::cout << std::left
              << std::setw(10) << "Bus ID"
              << std::setw(12) << "Capacity"
              << std::setw(15) << "Model"
              << std::setw(15) << "Status"
              << std::endl;
    printSeparator();

    for (const auto &bus : buses)
    {
        bus.display();
    }

    printSeparator();
    std::cout << "Total Buses: " << buses.size() << std::endl;
    printSeparator();
}

void DisplayManager::displayDrivers(const std::vector<Driver> &drivers)
{
    printHeader("DRIVER INFORMATION");

    if (drivers.empty())
    {
        std::cout << "No drivers found." << std::endl;
        printSeparator();
        return;
    }

    std::cout << std::left
              << std::setw(10) << "Driver ID"
              << std::setw(20) << "Name"
              << std::setw(15) << "Contact"
              << std::setw(15) << "License"
              << std::endl;
    printSeparator();

    for (const auto &driver : drivers)
    {
        driver.display();
    }

    printSeparator();
    std::cout << "Total Drivers: " << drivers.size() << std::endl;
    printSeparator();
}

void DisplayManager::displayRoutes(const std::vector<Route> &routes)
{
    printHeader("ROUTE INFORMATION");

    if (routes.empty())
    {
        std::cout << "No routes found." << std::endl;
        printSeparator();
        return;
    }

    std::cout << std::left
              << std::setw(10) << "Route ID"
              << std::setw(15) << "Origin"
              << std::setw(15) << "Destination"
              << std::setw(40) << "Key Stops"
              << std::setw(10) << "Time (min)"
              << std::endl;
    printSeparator();

    for (const auto &route : routes)
    {
        route.display();
    }

    printSeparator();
    std::cout << "Total Routes: " << routes.size() << std::endl;
    printSeparator();
}

void DisplayManager::displaySchedules(const std::vector<Schedule> &schedules)
{
    printHeader("SCHEDULE INFORMATION");

    if (schedules.empty())
    {
        std::cout << "No schedules found." << std::endl;
        printSeparator();
        return;
    }

    std::cout << std::left
              << std::setw(12) << "Schedule ID"
              << std::setw(12) << "Route ID"
              << std::setw(10) << "Bus ID"
              << std::setw(12) << "Driver ID"
              << std::setw(12) << "Date"
              << std::setw(10) << "Departure"
              << std::setw(10) << "Arrival"
              << std::endl;
    printSeparator();

    for (const auto &schedule : schedules)
    {
        schedule.display();
    }

    printSeparator();
    std::cout << "Total Schedules: " << schedules.size() << std::endl;
    printSeparator();
}

void DisplayManager::displayUsers(const std::vector<User> &users)
{
    printHeader("USER CREDENTIALS");

    if (users.empty())
    {
        std::cout << "No users found." << std::endl;
        printSeparator();
        return;
    }

    std::cout << std::left
              << std::setw(15) << "Username"
              << std::setw(15) << "Password"
              << std::setw(15) << "Role"
              << std::endl;
    printSeparator();

    for (const auto &user : users)
    {
        user.display();
    }

    printSeparator();
    std::cout << "Total Users: " << users.size() << std::endl;
    printSeparator();
}

void DisplayManager::displayBus(const Bus &bus)
{
    std::cout << std::left
              << std::setw(10) << "Bus ID"
              << std::setw(12) << "Capacity"
              << std::setw(15) << "Model"
              << std::setw(15) << "Status"
              << std::endl;
    printSeparator();
    bus.display();
}

void DisplayManager::displayDriver(const Driver &driver)
{
    std::cout << std::left
              << std::setw(10) << "Driver ID"
              << std::setw(20) << "Name"
              << std::setw(15) << "Contact"
              << std::setw(15) << "License"
              << std::endl;
    printSeparator();
    driver.display();
}

void DisplayManager::displayRoute(const Route &route)
{
    std::cout << std::left
              << std::setw(10) << "Route ID"
              << std::setw(15) << "Origin"
              << std::setw(15) << "Destination"
              << std::setw(40) << "Key Stops"
              << std::setw(10) << "Time (min)"
              << std::endl;
    printSeparator();
    route.display();
}

void DisplayManager::displaySchedule(const Schedule &schedule)
{
    std::cout << std::left
              << std::setw(12) << "Schedule ID"
              << std::setw(12) << "Route ID"
              << std::setw(10) << "Bus ID"
              << std::setw(12) << "Driver ID"
              << std::setw(12) << "Date"
              << std::setw(10) << "Departure"
              << std::setw(10) << "Arrival"
              << std::endl;
    printSeparator();
    schedule.display();
}
