#ifndef ADMINDASHBOARD_H
#define ADMINDASHBOARD_H

#include "RouteManager.h"
#include "BusManager.h"
#include "DriverManager.h"
#include "ScheduleManager.h"
#include "User.h"

class AdminDashboard
{
private:
    RouteManager &routeManager;
    BusManager &busManager;
    DriverManager &driverManager;
    ScheduleManager &scheduleManager;
    User *admin;

    void manageRoutes();
    void manageSchedules();
    void manageBuses();
    void manageDrivers();

    void addRoute();
    void updateRoute();
    void removeRoute();
    void viewRoutes();

    void addBus();
    void updateBus();
    void removeBus();
    void viewBuses();

    void addDriver();
    void updateDriver();
    void removeDriver();
    void viewDrivers();

    void addSchedule();
    void updateSchedule();
    void removeSchedule();
    void viewSchedules();

    void clearInputBuffer();
    string getInput(const string &prompt);
    int getIntInput(const string &prompt);

public:
    AdminDashboard(RouteManager &rm, BusManager &bm, DriverManager &dm, ScheduleManager &sm, User *adminUser);

    void show();

    void displayMenu() const;
};

#endif
