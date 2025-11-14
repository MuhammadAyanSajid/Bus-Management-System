#include "../include/AdminDashboard.h"
#include <iostream>
#include <limits>
#include <sstream>

// Constructor
AdminDashboard::AdminDashboard(RouteManager &rm, BusManager &bm, DriverManager &dm, ScheduleManager &sm, User *adminUser)
    : routeManager(rm), busManager(bm), driverManager(dm), scheduleManager(sm), admin(adminUser) {}

// Clear input buffer
void AdminDashboard::clearInputBuffer()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Get string input
std::string AdminDashboard::getInput(const std::string &prompt)
{
    std::string input;
    std::cout << prompt;
    std::getline(std::cin, input);
    return input;
}

// Get integer input
int AdminDashboard::getIntInput(const std::string &prompt)
{
    int value;
    while (true)
    {
        std::cout << prompt;
        if (std::cin >> value)
        {
            clearInputBuffer();
            return value;
        }
        else
        {
            std::cout << "Invalid input. Please enter a number." << std::endl;
            clearInputBuffer();
        }
    }
}

// Display main menu
void AdminDashboard::displayMenu() const
{
    std::cout << "\n========================================" << std::endl;
    std::cout << "       ADMIN DASHBOARD" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "1. Manage Routes" << std::endl;
    std::cout << "2. Manage Schedules" << std::endl;
    std::cout << "3. Manage Buses" << std::endl;
    std::cout << "4. Manage Drivers" << std::endl;
    std::cout << "5. Logout" << std::endl;
    std::cout << "========================================" << std::endl;
}

// Main dashboard loop
void AdminDashboard::show()
{
    int choice;
    bool running = true;

    std::cout << "\nWelcome to Admin Dashboard, " << admin->getUsername() << "!" << std::endl;

    while (running)
    {
        displayMenu();
        choice = getIntInput("Enter your choice: ");

        switch (choice)
        {
        case 1:
            manageRoutes();
            break;
        case 2:
            manageSchedules();
            break;
        case 3:
            manageBuses();
            break;
        case 4:
            manageDrivers();
            break;
        case 5:
            std::cout << "\nLogging out..." << std::endl;
            running = false;
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }
}

// Manage Routes
void AdminDashboard::manageRoutes()
{
    int choice;
    bool back = false;

    while (!back)
    {
        std::cout << "\n--- Manage Routes ---" << std::endl;
        std::cout << "1. View All Routes" << std::endl;
        std::cout << "2. Add Route" << std::endl;
        std::cout << "3. Update Route" << std::endl;
        std::cout << "4. Remove Route" << std::endl;
        std::cout << "5. Back to Main Menu" << std::endl;

        choice = getIntInput("Enter your choice: ");

        switch (choice)
        {
        case 1:
            viewRoutes();
            break;
        case 2:
            addRoute();
            break;
        case 3:
            updateRoute();
            break;
        case 4:
            removeRoute();
            break;
        case 5:
            back = true;
            break;
        default:
            std::cout << "Invalid choice." << std::endl;
        }
    }
}

// View Routes
void AdminDashboard::viewRoutes()
{
    std::cout << "\n";
    routeManager.displayAllRoutes();
}

// Add Route
void AdminDashboard::addRoute()
{
    std::cout << "\n--- Add New Route ---" << std::endl;

    clearInputBuffer();
    std::string id = getInput("Enter Route ID: ");
    std::string origin = getInput("Enter Origin: ");
    std::string destination = getInput("Enter Destination: ");
    std::string stopsInput = getInput("Enter Key Stops (separated by |): ");
    int travelTime = getIntInput("Enter Estimated Travel Time (minutes): ");

    // Parse stops
    std::vector<std::string> stops;
    std::stringstream ss(stopsInput);
    std::string stop;
    while (std::getline(ss, stop, '|'))
    {
        stops.push_back(stop);
    }

    Route newRoute(id, origin, destination, stops, travelTime);
    routeManager.addRoute(newRoute);
}

// Update Route
void AdminDashboard::updateRoute()
{
    std::cout << "\n--- Update Route ---" << std::endl;

    clearInputBuffer();
    std::string id = getInput("Enter Route ID to update: ");

    Route *route = routeManager.findRoute(id);
    if (!route)
    {
        std::cout << "Route not found." << std::endl;
        return;
    }

    std::cout << "\nCurrent Route Information:" << std::endl;
    routeManager.displayAllRoutes();

    std::string origin = getInput("Enter New Origin (or press Enter to keep current): ");
    std::string destination = getInput("Enter New Destination (or press Enter to keep current): ");
    std::string stopsInput = getInput("Enter New Key Stops (separated by | or press Enter to keep current): ");

    std::cout << "Enter New Travel Time (or 0 to keep current): ";
    int travelTime;
    std::cin >> travelTime;
    clearInputBuffer();

    // Update only if new values provided
    if (!origin.empty())
        route->setOrigin(origin);
    if (!destination.empty())
        route->setDestination(destination);
    if (!stopsInput.empty())
    {
        std::vector<std::string> stops;
        std::stringstream ss(stopsInput);
        std::string stop;
        while (std::getline(ss, stop, '|'))
        {
            stops.push_back(stop);
        }
        route->setKeyStops(stops);
    }
    if (travelTime > 0)
        route->setEstimatedTravelTime(travelTime);

    routeManager.updateRoute(id, *route);
}

// Remove Route
void AdminDashboard::removeRoute()
{
    std::cout << "\n--- Remove Route ---" << std::endl;

    clearInputBuffer();
    std::string id = getInput("Enter Route ID to remove: ");

    std::string confirm = getInput("Are you sure you want to remove this route? (yes/no): ");
    if (confirm == "yes" || confirm == "y")
    {
        routeManager.removeRoute(id);
    }
    else
    {
        std::cout << "Operation cancelled." << std::endl;
    }
}

// Manage Buses
void AdminDashboard::manageBuses()
{
    int choice;
    bool back = false;

    while (!back)
    {
        std::cout << "\n--- Manage Buses ---" << std::endl;
        std::cout << "1. View All Buses" << std::endl;
        std::cout << "2. Add Bus" << std::endl;
        std::cout << "3. Update Bus" << std::endl;
        std::cout << "4. Remove Bus" << std::endl;
        std::cout << "5. Back to Main Menu" << std::endl;

        choice = getIntInput("Enter your choice: ");

        switch (choice)
        {
        case 1:
            viewBuses();
            break;
        case 2:
            addBus();
            break;
        case 3:
            updateBus();
            break;
        case 4:
            removeBus();
            break;
        case 5:
            back = true;
            break;
        default:
            std::cout << "Invalid choice." << std::endl;
        }
    }
}

// View Buses
void AdminDashboard::viewBuses()
{
    std::cout << "\n";
    busManager.displayAllBuses();
}

// Add Bus
void AdminDashboard::addBus()
{
    std::cout << "\n--- Add New Bus ---" << std::endl;

    clearInputBuffer();
    std::string id = getInput("Enter Bus ID: ");
    int capacity = getIntInput("Enter Capacity: ");
    clearInputBuffer();
    std::string model = getInput("Enter Model: ");
    std::string status = getInput("Enter Status (Active/Maintenance/Inactive): ");

    Bus newBus(id, capacity, model, status);
    busManager.addBus(newBus);
}

// Update Bus
void AdminDashboard::updateBus()
{
    std::cout << "\n--- Update Bus ---" << std::endl;

    clearInputBuffer();
    std::string id = getInput("Enter Bus ID to update: ");

    Bus *bus = busManager.findBus(id);
    if (!bus)
    {
        std::cout << "Bus not found." << std::endl;
        return;
    }

    std::cout << "\nCurrent Bus Information:" << std::endl;
    busManager.displayAllBuses();

    std::cout << "Enter New Capacity (or 0 to keep current): ";
    int capacity;
    std::cin >> capacity;
    clearInputBuffer();

    std::string model = getInput("Enter New Model (or press Enter to keep current): ");
    std::string status = getInput("Enter New Status (or press Enter to keep current): ");

    // Update only if new values provided
    if (capacity > 0)
        bus->setCapacity(capacity);
    if (!model.empty())
        bus->setModel(model);
    if (!status.empty())
        bus->setStatus(status);

    busManager.updateBus(id, *bus);
}

// Remove Bus
void AdminDashboard::removeBus()
{
    std::cout << "\n--- Remove Bus ---" << std::endl;

    clearInputBuffer();
    std::string id = getInput("Enter Bus ID to remove: ");

    std::string confirm = getInput("Are you sure you want to remove this bus? (yes/no): ");
    if (confirm == "yes" || confirm == "y")
    {
        busManager.removeBus(id);
    }
    else
    {
        std::cout << "Operation cancelled." << std::endl;
    }
}

// Manage Drivers
void AdminDashboard::manageDrivers()
{
    int choice;
    bool back = false;

    while (!back)
    {
        std::cout << "\n--- Manage Drivers ---" << std::endl;
        std::cout << "1. View All Drivers" << std::endl;
        std::cout << "2. Add Driver" << std::endl;
        std::cout << "3. Update Driver" << std::endl;
        std::cout << "4. Remove Driver" << std::endl;
        std::cout << "5. Back to Main Menu" << std::endl;

        choice = getIntInput("Enter your choice: ");

        switch (choice)
        {
        case 1:
            viewDrivers();
            break;
        case 2:
            addDriver();
            break;
        case 3:
            updateDriver();
            break;
        case 4:
            removeDriver();
            break;
        case 5:
            back = true;
            break;
        default:
            std::cout << "Invalid choice." << std::endl;
        }
    }
}

// View Drivers
void AdminDashboard::viewDrivers()
{
    std::cout << "\n";
    driverManager.displayAllDrivers();
}

// Add Driver
void AdminDashboard::addDriver()
{
    std::cout << "\n--- Add New Driver ---" << std::endl;

    clearInputBuffer();
    std::string id = getInput("Enter Driver ID: ");
    std::string name = getInput("Enter Name: ");
    std::string contact = getInput("Enter Contact Info: ");
    std::string license = getInput("Enter License Details: ");

    Driver newDriver(id, name, contact, license);
    driverManager.addDriver(newDriver);
}

// Update Driver
void AdminDashboard::updateDriver()
{
    std::cout << "\n--- Update Driver ---" << std::endl;

    clearInputBuffer();
    std::string id = getInput("Enter Driver ID to update: ");

    Driver *driver = driverManager.findDriver(id);
    if (!driver)
    {
        std::cout << "Driver not found." << std::endl;
        return;
    }

    std::cout << "\nCurrent Driver Information:" << std::endl;
    driverManager.displayAllDrivers();

    std::string name = getInput("Enter New Name (or press Enter to keep current): ");
    std::string contact = getInput("Enter New Contact Info (or press Enter to keep current): ");
    std::string license = getInput("Enter New License Details (or press Enter to keep current): ");

    // Update only if new values provided
    if (!name.empty())
        driver->setName(name);
    if (!contact.empty())
        driver->setContactInfo(contact);
    if (!license.empty())
        driver->setLicenseDetails(license);

    driverManager.updateDriver(id, *driver);
}

// Remove Driver
void AdminDashboard::removeDriver()
{
    std::cout << "\n--- Remove Driver ---" << std::endl;

    clearInputBuffer();
    std::string id = getInput("Enter Driver ID to remove: ");

    std::string confirm = getInput("Are you sure you want to remove this driver? (yes/no): ");
    if (confirm == "yes" || confirm == "y")
    {
        driverManager.removeDriver(id);
    }
    else
    {
        std::cout << "Operation cancelled." << std::endl;
    }
}

// Manage Schedules
void AdminDashboard::manageSchedules()
{
    int choice;
    bool back = false;

    while (!back)
    {
        std::cout << "\n--- Manage Schedules ---" << std::endl;
        std::cout << "1. View All Schedules" << std::endl;
        std::cout << "2. Add Schedule" << std::endl;
        std::cout << "3. Update Schedule" << std::endl;
        std::cout << "4. Remove Schedule" << std::endl;
        std::cout << "5. Back to Main Menu" << std::endl;

        choice = getIntInput("Enter your choice: ");

        switch (choice)
        {
        case 1:
            viewSchedules();
            break;
        case 2:
            addSchedule();
            break;
        case 3:
            updateSchedule();
            break;
        case 4:
            removeSchedule();
            break;
        case 5:
            back = true;
            break;
        default:
            std::cout << "Invalid choice." << std::endl;
        }
    }
}

// View Schedules
void AdminDashboard::viewSchedules()
{
    std::cout << "\n";
    scheduleManager.displayAllSchedules();
}

// Add Schedule
void AdminDashboard::addSchedule()
{
    std::cout << "\n--- Add New Schedule ---" << std::endl;

    clearInputBuffer();
    std::string id = getInput("Enter Schedule ID: ");
    std::string routeId = getInput("Enter Route ID: ");
    std::string busId = getInput("Enter Bus ID: ");
    std::string driverId = getInput("Enter Driver ID: ");
    std::string date = getInput("Enter Date (YYYY-MM-DD): ");
    std::string departureTime = getInput("Enter Departure Time (HH:MM): ");
    std::string arrivalTime = getInput("Enter Arrival Time (HH:MM): ");

    Schedule newSchedule(id, routeId, busId, driverId, date, departureTime, arrivalTime);
    scheduleManager.addSchedule(newSchedule);
}

// Update Schedule
void AdminDashboard::updateSchedule()
{
    std::cout << "\n--- Update Schedule ---" << std::endl;

    clearInputBuffer();
    std::string id = getInput("Enter Schedule ID to update: ");

    Schedule *schedule = scheduleManager.findSchedule(id);
    if (!schedule)
    {
        std::cout << "Schedule not found." << std::endl;
        return;
    }

    std::cout << "\nCurrent Schedule Information:" << std::endl;
    scheduleManager.displayAllSchedules();

    std::string routeId = getInput("Enter New Route ID (or press Enter to keep current): ");
    std::string busId = getInput("Enter New Bus ID (or press Enter to keep current): ");
    std::string driverId = getInput("Enter New Driver ID (or press Enter to keep current): ");
    std::string date = getInput("Enter New Date (or press Enter to keep current): ");
    std::string departureTime = getInput("Enter New Departure Time (or press Enter to keep current): ");
    std::string arrivalTime = getInput("Enter New Arrival Time (or press Enter to keep current): ");

    // Update only if new values provided
    if (!routeId.empty())
        schedule->setRouteId(routeId);
    if (!busId.empty())
        schedule->setBusId(busId);
    if (!driverId.empty())
        schedule->setDriverId(driverId);
    if (!date.empty())
        schedule->setDate(date);
    if (!departureTime.empty())
        schedule->setDepartureTime(departureTime);
    if (!arrivalTime.empty())
        schedule->setArrivalTime(arrivalTime);

    scheduleManager.updateSchedule(id, *schedule);
}

// Remove Schedule
void AdminDashboard::removeSchedule()
{
    std::cout << "\n--- Remove Schedule ---" << std::endl;

    clearInputBuffer();
    std::string id = getInput("Enter Schedule ID to remove: ");

    std::string confirm = getInput("Are you sure you want to remove this schedule? (yes/no): ");
    if (confirm == "yes" || confirm == "y")
    {
        scheduleManager.removeSchedule(id);
    }
    else
    {
        std::cout << "Operation cancelled." << std::endl;
    }
}
