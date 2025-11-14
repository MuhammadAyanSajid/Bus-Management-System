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

    // Helper functions for menu operations
    void manageRoutes();
    void manageSchedules();
    void manageBuses();
    void manageDrivers();

    // CRUD helper functions
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

    // Input helpers
    void clearInputBuffer();
    std::string getInput(const std::string &prompt);
    int getIntInput(const std::string &prompt);

public:
    // Constructor
    AdminDashboard(RouteManager &rm, BusManager &bm, DriverManager &dm, ScheduleManager &sm, User *adminUser);

    // Main dashboard
    void show();

    // Display menu
    void displayMenu() const;
};

#endif // ADMINDASHBOARD_H
