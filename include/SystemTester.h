#ifndef SYSTEMTESTER_H
#define SYSTEMTESTER_H

#include <string>
#include <vector>
#include "RouteManager.h"
#include "BusManager.h"
#include "DriverManager.h"
#include "ScheduleManager.h"
#include "LoginManager.h"

class SystemTester
{
private:
    int testsRun;
    int testsPassed;
    int testsFailed;

    // Test result tracking
    void logTest(const std::string &testName, bool passed, const std::string &message = "");
    void printTestHeader(const std::string &category);

    // Individual test methods
    bool testDataLoading();
    bool testBusValidation(BusManager &busManager);
    bool testDriverValidation(DriverManager &driverManager);
    bool testRouteValidation(RouteManager &routeManager);
    bool testScheduleValidation(ScheduleManager &scheduleManager);
    bool testScheduleOverlap(ScheduleManager &scheduleManager);
    bool testAuthentication(LoginManager &loginManager);
    bool testCRUDOperations(RouteManager &rm, BusManager &bm, DriverManager &dm, ScheduleManager &sm);
    bool testEdgeCases(RouteManager &rm, BusManager &bm, DriverManager &dm, ScheduleManager &sm);

public:
    SystemTester();

    // Run all tests
    void runAllTests(RouteManager &rm, BusManager &bm, DriverManager &dm,
                     ScheduleManager &sm, LoginManager &lm);

    // Display results
    void displayResults();
};

#endif // SYSTEMTESTER_H
