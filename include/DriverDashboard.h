#ifndef DRIVERDASHBOARD_H
#define DRIVERDASHBOARD_H

#include "ScheduleManager.h"
#include "DriverManager.h"
#include "BusManager.h"
#include "User.h"
#include <fstream>

class DriverDashboard
{
private:
    ScheduleManager &scheduleManager;
    DriverManager &driverManager;
    BusManager &busManager;
    User *driver;
    std::string driverId;

    // Helper functions
    void clearInputBuffer();
    std::string getInput(const std::string &prompt);
    int getIntInput(const std::string &prompt);

    // Dashboard functions
    void viewAssignedSchedule();
    void viewPersonalProfile();
    void updateContactInfo();
    void requestDayOff();
    void viewBusDetails();

public:
    // Constructor
    DriverDashboard(ScheduleManager &sm, DriverManager &dm, BusManager &bm, User *driverUser, const std::string &dId);

    // Main dashboard
    void show();

    // Display menu
    void displayMenu() const;
};

#endif // DRIVERDASHBOARD_H
