#ifndef DISPLAYMANAGER_H
#define DISPLAYMANAGER_H

#include <vector>
#include "Bus.h"
#include "Driver.h"
#include "Route.h"
#include "Schedule.h"
#include "User.h"

class DisplayManager
{
public:
    // Display functions for each entity type
    static void displayBuses(const std::vector<Bus> &buses);
    static void displayDrivers(const std::vector<Driver> &drivers);
    static void displayRoutes(const std::vector<Route> &routes);
    static void displaySchedules(const std::vector<Schedule> &schedules);
    static void displayUsers(const std::vector<User> &users);

    // Display single entities
    static void displayBus(const Bus &bus);
    static void displayDriver(const Driver &driver);
    static void displayRoute(const Route &route);
    static void displaySchedule(const Schedule &schedule);

    // Helper functions for formatted output
    static void printSeparator(int width = 100);
    static void printHeader(const std::string &title);
};

#endif // DISPLAYMANAGER_H
