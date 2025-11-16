#ifndef DISPLAYMANAGER_H
#define DISPLAYMANAGER_H

#include <vector>
#include "Bus.h"
#include "Driver.h"
#include "Route.h"
#include "Schedule.h"
#include "User.h"

using std::vector;

class DisplayManager
{
public:
    static void displayBuses(const vector<Bus> &buses);
    static void displayDrivers(const vector<Driver> &drivers);
    static void displayRoutes(const vector<Route> &routes);
    static void displaySchedules(const vector<Schedule> &schedules);
    static void displayUsers(const vector<User> &users);

    static void displayBus(const Bus &bus);
    static void displayDriver(const Driver &driver);
    static void displayRoute(const Route &route);
    static void displaySchedule(const Schedule &schedule);

    static void printSeparator(int width = 100);
    static void printHeader(const string &title);
};

#endif
