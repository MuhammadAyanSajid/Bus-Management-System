#include "../include/SystemTester.h"
#include "../include/DataLoader.h"
#include <iostream>
#include <iomanip>

using namespace std;

SystemTester::SystemTester() : testsRun(0), testsPassed(0), testsFailed(0) {}

void SystemTester::logTest(const string &testName, bool passed, const string &message)
{
    testsRun++;
    if (passed)
    {
        testsPassed++;
        cout << "  [PASS] " << testName << endl;
    }
    else
    {
        testsFailed++;
        cout << "  [FAIL] " << testName;
        if (!message.empty())
        {
            cout << " - " << message;
        }
        cout << endl;
    }
}

void SystemTester::printTestHeader(const string &category)
{
    cout << "\n========================================" << endl;
    cout << "  " << category << endl;
    cout << "========================================" << endl;
}

bool SystemTester::testDataLoading()
{
    printTestHeader("DATA LOADING TESTS");

    vector<Bus> buses = DataLoader::loadBuses("data/buses.txt");
    logTest("Load buses from file", buses.size() > 0);

    vector<Driver> drivers = DataLoader::loadDrivers("data/drivers.txt");
    logTest("Load drivers from file", drivers.size() > 0);

    vector<Route> routes = DataLoader::loadRoutes("data/routes.txt");
    logTest("Load routes from file", routes.size() > 0);

    vector<Schedule> schedules = DataLoader::loadSchedules("data/schedules.txt");
    logTest("Load schedules from file", schedules.size() > 0);

    vector<User> users = DataLoader::loadCredentials("data/credentials.txt");
    logTest("Load credentials from file", users.size() > 0);

    vector<Bus> emptyBuses = DataLoader::loadBuses("data/nonexistent.txt");
    logTest("Handle missing file gracefully", emptyBuses.size() == 0);

    return true;
}

bool SystemTester::testBusValidation(BusManager &busManager)
{
    printTestHeader("BUS VALIDATION TESTS");

    Bus validBus("TEST001", 50, "Test Model", "Active");
    bool addValid = busManager.addBus(validBus);
    logTest("Add valid bus", addValid);

    Bus duplicateBus("TEST001", 40, "Another Model", "Active");
    bool addDuplicate = !busManager.addBus(duplicateBus);
    logTest("Reject duplicate bus ID", addDuplicate);

    Bus invalidCapacity("TEST002", -10, "Test Model", "Active");
    bool rejectNegative = !busManager.addBus(invalidCapacity);
    logTest("Reject negative capacity", rejectNegative);

    Bus zeroCapacity("TEST003", 0, "Test Model", "Active");
    bool rejectZero = !busManager.addBus(zeroCapacity);
    logTest("Reject zero capacity", rejectZero);

    Bus emptyId("", 50, "Test Model", "Active");
    bool rejectEmpty = !busManager.addBus(emptyId);
    logTest("Reject empty bus ID", rejectEmpty);

    Bus invalidStatus("TEST004", 50, "Test Model", "InvalidStatus");
    bool rejectStatus = !busManager.addBus(invalidStatus);
    logTest("Reject invalid status", rejectStatus);

    Bus *existingBus = busManager.findBus("TEST001");
    if (existingBus)
    {
        existingBus->setCapacity(60);
        bool updateSuccess = busManager.updateBus("TEST001", *existingBus);
        logTest("Update existing bus", updateSuccess);
    }

    bool removeSuccess = busManager.removeBus("TEST001");
    logTest("Remove bus", removeSuccess);

    bool removeNonExistent = !busManager.removeBus("NONEXISTENT");
    logTest("Handle removing non-existent bus", removeNonExistent);

    return true;
}

bool SystemTester::testDriverValidation(DriverManager &driverManager)
{
    printTestHeader("DRIVER VALIDATION TESTS");

    Driver validDriver("TEST_D001", "Test Driver", "555-0100", "Class A");
    bool addValid = driverManager.addDriver(validDriver);
    logTest("Add valid driver", addValid);

    Driver duplicateDriver("TEST_D001", "Another Driver", "555-0101", "Class B");
    bool addDuplicate = !driverManager.addDriver(duplicateDriver);
    logTest("Reject duplicate driver ID", addDuplicate);

    Driver emptyId("", "Test Driver", "555-0102", "Class A");
    bool rejectEmptyId = !driverManager.addDriver(emptyId);
    logTest("Reject empty driver ID", rejectEmptyId);

    Driver emptyName("TEST_D002", "", "555-0103", "Class A");
    bool rejectEmptyName = !driverManager.addDriver(emptyName);
    logTest("Reject empty driver name", rejectEmptyName);

    Driver emptyContact("TEST_D003", "Test Driver", "", "Class A");
    bool rejectEmptyContact = !driverManager.addDriver(emptyContact);
    logTest("Reject empty contact info", rejectEmptyContact);

    Driver emptyLicense("TEST_D004", "Test Driver", "555-0104", "");
    bool rejectEmptyLicense = !driverManager.addDriver(emptyLicense);
    logTest("Reject empty license details", rejectEmptyLicense);

    Driver *existingDriver = driverManager.findDriver("TEST_D001");
    if (existingDriver)
    {
        existingDriver->setContactInfo("555-9999");
        bool updateSuccess = driverManager.updateDriver("TEST_D001", *existingDriver);
        logTest("Update driver contact info", updateSuccess);
    }

    driverManager.removeDriver("TEST_D001");

    return true;
}

bool SystemTester::testRouteValidation(RouteManager &routeManager)
{
    printTestHeader("ROUTE VALIDATION TESTS");

    vector<string> stops = {"Stop1", "Stop2", "Stop3"};
    Route validRoute("TEST_R001", "Origin A", "Destination B", stops, 60);
    bool addValid = routeManager.addRoute(validRoute);
    logTest("Add valid route", addValid);

    Route duplicateRoute("TEST_R001", "Origin C", "Destination D", stops, 45);
    bool addDuplicate = !routeManager.addRoute(duplicateRoute);
    logTest("Reject duplicate route ID", addDuplicate);

    Route emptyId("", "Origin A", "Destination B", stops, 60);
    bool rejectEmptyId = !routeManager.addRoute(emptyId);
    logTest("Reject empty route ID", rejectEmptyId);

    Route emptyOrigin("TEST_R002", "", "Destination B", stops, 60);
    bool rejectEmptyOrigin = !routeManager.addRoute(emptyOrigin);
    logTest("Reject empty origin", rejectEmptyOrigin);

    Route emptyDestination("TEST_R003", "Origin A", "", stops, 60);
    bool rejectEmptyDest = !routeManager.addRoute(emptyDestination);
    logTest("Reject empty destination", rejectEmptyDest);

    Route sameOriginDest("TEST_R004", "SamePlace", "SamePlace", stops, 60);
    bool rejectSame = !routeManager.addRoute(sameOriginDest);
    logTest("Reject same origin and destination", rejectSame);

    Route negativeTime("TEST_R005", "Origin A", "Destination B", stops, -10);
    bool rejectNegative = !routeManager.addRoute(negativeTime);
    logTest("Reject negative travel time", rejectNegative);

    Route zeroTime("TEST_R006", "Origin A", "Destination B", stops, 0);
    bool rejectZero = !routeManager.addRoute(zeroTime);
    logTest("Reject zero travel time", rejectZero);

    routeManager.removeRoute("TEST_R001");

    return true;
}

bool SystemTester::testScheduleValidation(ScheduleManager &scheduleManager)
{
    printTestHeader("SCHEDULE VALIDATION TESTS");

    Schedule validSchedule("TEST_S001", "R001", "B001", "D101", "2025-12-01", "08:00", "09:00");
    bool addValid = scheduleManager.addSchedule(validSchedule);
    logTest("Add valid schedule", addValid);

    Schedule duplicateSchedule("TEST_S001", "R002", "B002", "D102", "2025-12-01", "10:00", "11:00");
    bool addDuplicate = !scheduleManager.addSchedule(duplicateSchedule);
    logTest("Reject duplicate schedule ID", addDuplicate);

    Schedule invalidRoute("TEST_S002", "INVALID_ROUTE", "B001", "D101", "2025-12-01", "12:00", "13:00");
    bool rejectInvalidRoute = !scheduleManager.addSchedule(invalidRoute);
    logTest("Reject invalid route reference", rejectInvalidRoute);

    Schedule invalidBus("TEST_S003", "R001", "INVALID_BUS", "D101", "2025-12-01", "12:00", "13:00");
    bool rejectInvalidBus = !scheduleManager.addSchedule(invalidBus);
    logTest("Reject invalid bus reference", rejectInvalidBus);

    Schedule invalidDriver("TEST_S004", "R001", "B001", "INVALID_DRIVER", "2025-12-01", "12:00", "13:00");
    bool rejectInvalidDriver = !scheduleManager.addSchedule(invalidDriver);
    logTest("Reject invalid driver reference", rejectInvalidDriver);

    Schedule invalidTime("TEST_S005", "R001", "B002", "D102", "2025-12-01", "15:00", "14:00");
    bool rejectInvalidTime = !scheduleManager.addSchedule(invalidTime);
    logTest("Reject departure after arrival", rejectInvalidTime);

    Schedule sameTime("TEST_S006", "R001", "B002", "D102", "2025-12-01", "15:00", "15:00");
    bool rejectSameTime = !scheduleManager.addSchedule(sameTime);
    logTest("Reject same departure and arrival time", rejectSameTime);

    scheduleManager.removeSchedule("TEST_S001");

    return true;
}

bool SystemTester::testScheduleOverlap(ScheduleManager &scheduleManager)
{
    printTestHeader("SCHEDULE OVERLAP TESTS");

    Schedule schedule1("OVERLAP_S001", "R001", "B004", "D103", "2025-12-15", "08:00", "10:00");
    bool add1 = scheduleManager.addSchedule(schedule1);
    logTest("Add first schedule", add1);

    Schedule busOverlap("OVERLAP_S002", "R002", "B004", "D104", "2025-12-15", "09:00", "11:00");
    bool rejectBusOverlap = !scheduleManager.addSchedule(busOverlap);
    logTest("Reject bus time overlap", rejectBusOverlap);

    Schedule driverOverlap("OVERLAP_S003", "R002", "B005", "D103", "2025-12-15", "09:30", "11:30");
    bool rejectDriverOverlap = !scheduleManager.addSchedule(driverOverlap);
    logTest("Reject driver time overlap", rejectDriverOverlap);

    Schedule differentDate("OVERLAP_S004", "R002", "B004", "D104", "2025-12-16", "09:00", "11:00");
    bool addDifferentDate = scheduleManager.addSchedule(differentDate);
    logTest("Allow same bus on different date", addDifferentDate);

    Schedule nonOverlapping("OVERLAP_S005", "R002", "B004", "D104", "2025-12-15", "10:00", "12:00");
    bool addNonOverlap = scheduleManager.addSchedule(nonOverlapping);
    logTest("Allow same bus at non-overlapping time", addNonOverlap);

    Schedule edgeCase("OVERLAP_S006", "R003", "B004", "D105", "2025-12-15", "12:00", "14:00");
    bool addEdgeCase = scheduleManager.addSchedule(edgeCase);
    logTest("Allow back-to-back schedules", addEdgeCase);

    scheduleManager.removeSchedule("OVERLAP_S001");
    scheduleManager.removeSchedule("OVERLAP_S004");
    scheduleManager.removeSchedule("OVERLAP_S005");
    scheduleManager.removeSchedule("OVERLAP_S006");

    return true;
}

bool SystemTester::testAuthentication(LoginManager &loginManager)
{
    printTestHeader("AUTHENTICATION TESTS");

    bool adminAuth = loginManager.authenticate("admin", "admin123", UserRole::ADMIN);
    logTest("Valid admin authentication", adminAuth);
    loginManager.logout();

    bool invalidPassword = !loginManager.authenticate("admin", "wrongpassword", UserRole::ADMIN);
    logTest("Reject invalid admin password", invalidPassword);

    bool nonExistent = !loginManager.authenticate("nonexistent", "password", UserRole::ADMIN);
    logTest("Reject non-existent user", nonExistent);

    bool driverAuth = loginManager.authenticate("D101", "driver101", UserRole::DRIVER);
    logTest("Valid driver authentication", driverAuth);
    loginManager.logout();

    bool wrongRole = !loginManager.authenticate("admin", "admin123", UserRole::DRIVER);
    logTest("Reject login with wrong role", wrongRole);

    bool caseSensitive = !loginManager.authenticate("ADMIN", "admin123", UserRole::ADMIN);
    logTest("Username is case-sensitive", caseSensitive);

    return true;
}

bool SystemTester::testCRUDOperations(RouteManager &rm, BusManager &bm,
                                      DriverManager &dm, ScheduleManager &sm)
{
    printTestHeader("CRUD OPERATIONS TESTS");

    Bus testBus("CRUD_B001", 55, "CRUD Test Model", "Active");
    bool busCreate = bm.addBus(testBus);
    Bus *foundBus = bm.findBus("CRUD_B001");
    bool busRead = (foundBus != nullptr);
    if (foundBus)
    {
        foundBus->setCapacity(65);
        bool busUpdate = bm.updateBus("CRUD_B001", *foundBus);
        bool busDelete = bm.removeBus("CRUD_B001");
        logTest("Bus CRUD cycle (Create-Read-Update-Delete)",
                busCreate && busRead && busUpdate && busDelete);
    }

    Driver testDriver("CRUD_D001", "CRUD Test Driver", "555-CRUD", "Class Test");
    bool driverCreate = dm.addDriver(testDriver);
    Driver *foundDriver = dm.findDriver("CRUD_D001");
    bool driverRead = (foundDriver != nullptr);
    if (foundDriver)
    {
        foundDriver->setContactInfo("555-UPDATED");
        bool driverUpdate = dm.updateDriver("CRUD_D001", *foundDriver);
        bool driverDelete = dm.removeDriver("CRUD_D001");
        logTest("Driver CRUD cycle (Create-Read-Update-Delete)",
                driverCreate && driverRead && driverUpdate && driverDelete);
    }

    vector<string> testStops = {"CRUDStop1", "CRUDStop2"};
    Route testRoute("CRUD_R001", "CRUD Origin", "CRUD Dest", testStops, 45);
    bool routeCreate = rm.addRoute(testRoute);
    Route *foundRoute = rm.findRoute("CRUD_R001");
    bool routeRead = (foundRoute != nullptr);
    if (foundRoute)
    {
        foundRoute->setEstimatedTravelTime(50);
        bool routeUpdate = rm.updateRoute("CRUD_R001", *foundRoute);
        bool routeDelete = rm.removeRoute("CRUD_R001");
        logTest("Route CRUD cycle (Create-Read-Update-Delete)",
                routeCreate && routeRead && routeUpdate && routeDelete);
    }

    return true;
}

bool SystemTester::testEdgeCases(RouteManager &rm, BusManager &bm,
                                 DriverManager &dm, ScheduleManager &sm)
{
    printTestHeader("EDGE CASE TESTS");

    Bus longIdBus("THIS_IS_A_VERY_LONG_BUS_ID_TO_TEST_LIMITS", 50, "Test", "Active");
    bool handleLongId = bm.addBus(longIdBus);
    logTest("Handle very long ID", handleLongId);
    if (handleLongId)
        bm.removeBus("THIS_IS_A_VERY_LONG_BUS_ID_TO_TEST_LIMITS");

    Driver specialChar("EDGE_D001", "Test-Driver's Name (Special)", "555-0000", "Class A");
    bool handleSpecialChar = dm.addDriver(specialChar);
    logTest("Handle special characters in names", handleSpecialChar);
    if (handleSpecialChar)
        dm.removeDriver("EDGE_D001");

    Bus maxCapacity("EDGE_B001", 999999, "Test", "Active");
    bool handleMaxCap = bm.addBus(maxCapacity);
    logTest("Handle very large capacity", handleMaxCap);
    if (handleMaxCap)
        bm.removeBus("EDGE_B001");

    vector<string> manyStops;
    for (int i = 1; i <= 20; i++)
    {
        manyStops.push_back("Stop" + to_string(i));
    }
    Route manyStopsRoute("EDGE_R001", "Start", "End", manyStops, 180);
    bool handleManyStops = rm.addRoute(manyStopsRoute);
    logTest("Handle route with many stops", handleManyStops);
    if (handleManyStops)
        rm.removeRoute("EDGE_R001");

    Schedule midnightSchedule("EDGE_S001", "R001", "B001", "D101", "2025-12-20", "00:00", "01:00");
    bool handleMidnight = sm.addSchedule(midnightSchedule);
    logTest("Handle midnight schedule", handleMidnight);
    if (handleMidnight)
        sm.removeSchedule("EDGE_S001");

    Schedule lateNight("EDGE_S002", "R001", "B002", "D102", "2025-12-20", "23:00", "23:59");
    bool handleLateNight = sm.addSchedule(lateNight);
    logTest("Handle late night schedule", handleLateNight);
    if (handleLateNight)
        sm.removeSchedule("EDGE_S002");

    return true;
}

void SystemTester::runAllTests(RouteManager &rm, BusManager &bm, DriverManager &dm,
                               ScheduleManager &sm, LoginManager &lm)
{
    cout << "\n";
    cout << "========================================" << endl;
    cout << "  BUS MANAGEMENT SYSTEM TEST SUITE" << endl;
    cout << "========================================" << endl;

    testDataLoading();
    testBusValidation(bm);
    testDriverValidation(dm);
    testRouteValidation(rm);
    testScheduleValidation(sm);
    testScheduleOverlap(sm);
    testAuthentication(lm);
    testCRUDOperations(rm, bm, dm, sm);
    testEdgeCases(rm, bm, dm, sm);
}

void SystemTester::displayResults()
{
    cout << "\n";
    cout << "========================================" << endl;
    cout << "  TEST RESULTS SUMMARY" << endl;
    cout << "========================================" << endl;
    cout << "Total Tests Run:    " << testsRun << endl;
    cout << "Tests Passed:       " << testsPassed << " ("
         << fixed << setprecision(1)
         << (testsRun > 0 ? (testsPassed * 100.0 / testsRun) : 0) << "%)" << endl;
    cout << "Tests Failed:       " << testsFailed << endl;
    cout << "========================================" << endl;

    if (testsFailed == 0)
    {
        cout << "\nâœ“ ALL TESTS PASSED! System is working correctly." << endl;
    }
    else
    {
        cout << "\nâœ— Some tests failed. Please review the results above." << endl;
    }
    cout << "\n";
}
