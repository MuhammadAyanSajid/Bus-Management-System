#include "../include/DisplayManager.h"
#include <iostream>
#include <iomanip>

using namespace std;

void DisplayManager::printSeparator(int width)
{
    cout << string(width, '=') << endl;
}

void DisplayManager::printHeader(const string &title)
{
    printSeparator();
    cout << "| " << left << setw(96) << title << " |" << endl;
    printSeparator();
}

void DisplayManager::displayBuses(const vector<Bus> &buses)
{
    printHeader("BUS INFORMATION");

    if (buses.empty())
    {
        cout << "No buses found." << endl;
        printSeparator();
        return;
    }

    cout << left
         << setw(10) << "Bus ID"
         << setw(12) << "Capacity"
         << setw(15) << "Model"
         << setw(15) << "Status"
         << endl;
    printSeparator();

    for (const auto &bus : buses)
    {
        bus.display();
    }

    printSeparator();
    cout << "Total Buses: " << buses.size() << endl;
    printSeparator();
}

void DisplayManager::displayDrivers(const vector<Driver> &drivers)
{
    printHeader("DRIVER INFORMATION");

    if (drivers.empty())
    {
        cout << "No drivers found." << endl;
        printSeparator();
        return;
    }

    cout << left
         << setw(10) << "Driver ID"
         << setw(20) << "Name"
         << setw(15) << "Contact"
         << setw(15) << "License"
         << endl;
    printSeparator();

    for (const auto &driver : drivers)
    {
        driver.display();
    }

    printSeparator();
    cout << "Total Drivers: " << drivers.size() << endl;
    printSeparator();
}

void DisplayManager::displayRoutes(const vector<Route> &routes)
{
    printHeader("ROUTE INFORMATION");

    if (routes.empty())
    {
        cout << "No routes found." << endl;
        printSeparator();
        return;
    }

    cout << left
         << setw(10) << "Route ID"
         << setw(15) << "Origin"
         << setw(15) << "Destination"
         << setw(40) << "Key Stops"
         << setw(10) << "Time (min)"
         << endl;
    printSeparator();

    for (const auto &route : routes)
    {
        route.display();
    }

    printSeparator();
    cout << "Total Routes: " << routes.size() << endl;
    printSeparator();
}

void DisplayManager::displaySchedules(const vector<Schedule> &schedules)
{
    printHeader("SCHEDULE INFORMATION");

    if (schedules.empty())
    {
        cout << "No schedules found." << endl;
        printSeparator();
        return;
    }

    cout << left
         << setw(12) << "Schedule ID"
         << setw(12) << "Route ID"
         << setw(10) << "Bus ID"
         << setw(12) << "Driver ID"
         << setw(12) << "Date"
         << setw(10) << "Departure"
         << setw(10) << "Arrival"
         << endl;
    printSeparator();

    for (const auto &schedule : schedules)
    {
        schedule.display();
    }

    printSeparator();
    cout << "Total Schedules: " << schedules.size() << endl;
    printSeparator();
}

void DisplayManager::displayUsers(const vector<User> &users)
{
    printHeader("USER CREDENTIALS");

    if (users.empty())
    {
        cout << "No users found." << endl;
        printSeparator();
        return;
    }

    cout << left
         << setw(15) << "Username"
         << setw(15) << "Password"
         << setw(15) << "Role"
         << endl;
    printSeparator();

    for (const auto &user : users)
    {
        user.display();
    }

    printSeparator();
    cout << "Total Users: " << users.size() << endl;
    printSeparator();
}

void DisplayManager::displayBus(const Bus &bus)
{
    cout << left
         << setw(10) << "Bus ID"
         << setw(12) << "Capacity"
         << setw(15) << "Model"
         << setw(15) << "Status"
         << endl;
    printSeparator();
    bus.display();
}

void DisplayManager::displayDriver(const Driver &driver)
{
    cout << left
         << setw(10) << "Driver ID"
         << setw(20) << "Name"
         << setw(15) << "Contact"
         << setw(15) << "License"
         << endl;
    printSeparator();
    driver.display();
}

void DisplayManager::displayRoute(const Route &route)
{
    cout << left
         << setw(10) << "Route ID"
         << setw(15) << "Origin"
         << setw(15) << "Destination"
         << setw(40) << "Key Stops"
         << setw(10) << "Time (min)"
         << endl;
    printSeparator();
    route.display();
}

void DisplayManager::displaySchedule(const Schedule &schedule)
{
    cout << left
         << setw(12) << "Schedule ID"
         << setw(12) << "Route ID"
         << setw(10) << "Bus ID"
         << setw(12) << "Driver ID"
         << setw(12) << "Date"
         << setw(10) << "Departure"
         << setw(10) << "Arrival"
         << endl;
    printSeparator();
    schedule.display();
}
