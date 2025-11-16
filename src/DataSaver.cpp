#include "../include/DataSaver.h"
#include <fstream>
#include <iostream>

using namespace std;

bool DataSaver::saveBuses(const string &filename, const vector<Bus> &buses)
{
    ofstream file(filename);

    if (!file.is_open())
    {
        cerr << "Error: Could not open file " << filename << " for writing." << endl;
        return false;
    }

    for (const auto &bus : buses)
    {
        file << bus.getId() << ","
             << bus.getCapacity() << ","
             << bus.getModel() << ","
             << bus.getStatus() << endl;
    }

    file.close();
    cout << "Successfully saved " << buses.size() << " buses to " << filename << endl;
    return true;
}

bool DataSaver::saveDrivers(const string &filename, const vector<Driver> &drivers)
{
    ofstream file(filename);

    if (!file.is_open())
    {
        cerr << "Error: Could not open file " << filename << " for writing." << endl;
        return false;
    }

    for (const auto &driver : drivers)
    {
        file << driver.getId() << ","
             << driver.getName() << ","
             << driver.getContactInfo() << ","
             << driver.getLicenseDetails() << endl;
    }

    file.close();
    cout << "Successfully saved " << drivers.size() << " drivers to " << filename << endl;
    return true;
}

bool DataSaver::saveRoutes(const string &filename, const vector<Route> &routes)
{
    ofstream file(filename);

    if (!file.is_open())
    {
        cerr << "Error: Could not open file " << filename << " for writing." << endl;
        return false;
    }

    for (const auto &route : routes)
    {
        file << route.getId() << ","
             << route.getOrigin() << ","
             << route.getDestination() << ","
             << route.getStopsAsString() << ","
             << route.getEstimatedTravelTime() << endl;
    }

    file.close();
    cout << "Successfully saved " << routes.size() << " routes to " << filename << endl;
    return true;
}

bool DataSaver::saveSchedules(const string &filename, const vector<Schedule> &schedules)
{
    ofstream file(filename);

    if (!file.is_open())
    {
        cerr << "Error: Could not open file " << filename << " for writing." << endl;
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
             << schedule.getArrivalTime() << endl;
    }

    file.close();
    cout << "Successfully saved " << schedules.size() << " schedules to " << filename << endl;
    return true;
}

bool DataSaver::saveCredentials(const string &filename, const vector<User> &users)
{
    ofstream file(filename);

    if (!file.is_open())
    {
        cerr << "Error: Could not open file " << filename << " for writing." << endl;
        return false;
    }

    for (const auto &user : users)
    {
        file << user.getUsername() << ","
             << user.getPassword() << ","
             << user.getRoleString() << endl;
    }

    file.close();
    cout << "Successfully saved " << users.size() << " users to " << filename << endl;
    return true;
}
