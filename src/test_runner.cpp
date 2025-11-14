#include <iostream>
#include "../include/DataLoader.h"
#include "../include/RouteManager.h"
#include "../include/BusManager.h"
#include "../include/DriverManager.h"
#include "../include/ScheduleManager.h"
#include "../include/LoginManager.h"
#include "../include/SystemTester.h"

int main()
{
    std::cout << "\n";
    std::cout << "========================================" << std::endl;
    std::cout << "  INITIALIZING TEST ENVIRONMENT" << std::endl;
    std::cout << "========================================" << std::endl;

    // Load all data
    const std::string DATA_PATH = "data/";
    std::vector<Bus> buses = DataLoader::loadBuses(DATA_PATH + "buses.txt");
    std::vector<Driver> drivers = DataLoader::loadDrivers(DATA_PATH + "drivers.txt");
    std::vector<Route> routes = DataLoader::loadRoutes(DATA_PATH + "routes.txt");
    std::vector<Schedule> schedules = DataLoader::loadSchedules(DATA_PATH + "schedules.txt");
    std::vector<User> users = DataLoader::loadCredentials(DATA_PATH + "credentials.txt");

    std::cout << "\nTest environment initialized successfully!\n";

    // Create managers
    LoginManager loginManager(users);
    RouteManager routeManager(routes, DATA_PATH + "routes.txt");
    BusManager busManager(buses, DATA_PATH + "buses.txt");
    DriverManager driverManager(drivers, DATA_PATH + "drivers.txt");
    ScheduleManager scheduleManager(schedules, routes, buses, drivers, DATA_PATH + "schedules.txt");

    // Create and run tester
    SystemTester tester;
    tester.runAllTests(routeManager, busManager, driverManager, scheduleManager, loginManager);

    // Display results
    tester.displayResults();

    return 0;
}
