#include "../include/AdminDashboard.h"
#include <iostream>
#include <limits>
#include <sstream>
#include <algorithm>
#include <regex>

// Constructor
AdminDashboard::AdminDashboard(RouteManager &rm, BusManager &bm, DriverManager &dm, ScheduleManager &sm, User *adminUser)
    : routeManager(rm), busManager(bm), driverManager(dm), scheduleManager(sm), admin(adminUser) {}

// Helper function to trim whitespace
static std::string trim(const std::string &str)
{
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == std::string::npos)
        return "";
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, (last - first + 1));
}

// Validate ID format (alphanumeric, no spaces, 1-20 chars)
static bool validateId(const std::string &id)
{
    std::string trimmedId = trim(id);
    if (trimmedId.empty() || trimmedId.length() > 20)
    {
        std::cout << "Error: ID must be 1-20 characters long and cannot be empty." << std::endl;
        return false;
    }
    if (trimmedId.find(' ') != std::string::npos)
    {
        std::cout << "Error: ID cannot contain spaces." << std::endl;
        return false;
    }
    return true;
}

// Validate non-empty string
static bool validateNotEmpty(const std::string &str, const std::string &fieldName)
{
    std::string trimmedStr = trim(str);
    if (trimmedStr.empty())
    {
        std::cout << "Error: " << fieldName << " cannot be empty." << std::endl;
        return false;
    }
    return true;
}

// Validate date format (YYYY-MM-DD)
static bool validateDate(const std::string &date)
{
    std::regex dateRegex(R"(^\d{4}-\d{2}-\d{2}$)");
    if (!std::regex_match(date, dateRegex))
    {
        std::cout << "Error: Date must be in YYYY-MM-DD format (e.g., 2025-11-16)." << std::endl;
        return false;
    }
    // Basic validation of month and day ranges
    int year = std::stoi(date.substr(0, 4));
    int month = std::stoi(date.substr(5, 2));
    int day = std::stoi(date.substr(8, 2));
    if (month < 1 || month > 12)
    {
        std::cout << "Error: Month must be between 01 and 12." << std::endl;
        return false;
    }
    if (day < 1 || day > 31)
    {
        std::cout << "Error: Day must be between 01 and 31." << std::endl;
        return false;
    }
    if (year < 2000 || year > 2100)
    {
        std::cout << "Error: Year must be between 2000 and 2100." << std::endl;
        return false;
    }
    return true;
}

// Validate time format (HH:MM)
static bool validateTime(const std::string &time)
{
    std::regex timeRegex(R"(^([0-1]\d|2[0-3]):([0-5]\d)$)");
    if (!std::regex_match(time, timeRegex))
    {
        std::cout << "Error: Time must be in HH:MM format (e.g., 14:30, 09:00)." << std::endl;
        return false;
    }
    return true;
}

// Validate status
static bool validateStatus(const std::string &status)
{
    std::string upperStatus = status;
    std::transform(upperStatus.begin(), upperStatus.end(), upperStatus.begin(), ::toupper);
    if (upperStatus != "ACTIVE" && upperStatus != "MAINTENANCE" && upperStatus != "INACTIVE")
    {
        std::cout << "Error: Status must be Active, Maintenance, or Inactive." << std::endl;
        return false;
    }
    return true;
}

// Validate positive integer
static bool validatePositiveInt(int value, const std::string &fieldName)
{
    if (value <= 0)
    {
        std::cout << "Error: " << fieldName << " must be a positive number." << std::endl;
        return false;
    }
    return true;
}

// Validate contact info (basic phone/email format)
static bool validateContact(const std::string &contact)
{
    std::string trimmedContact = trim(contact);
    if (trimmedContact.empty())
    {
        std::cout << "Error: Contact information cannot be empty." << std::endl;
        return false;
    }
    if (trimmedContact.length() < 7)
    {
        std::cout << "Error: Contact information seems too short. Please provide valid phone or email." << std::endl;
        return false;
    }
    return true;
}

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

    // Validate ID
    std::string id;
    do
    {
        id = trim(getInput("Enter Route ID: "));
    } while (!validateId(id));

    // Validate origin
    std::string origin;
    do
    {
        origin = trim(getInput("Enter Origin: "));
    } while (!validateNotEmpty(origin, "Origin"));

    // Validate destination
    std::string destination;
    do
    {
        destination = trim(getInput("Enter Destination: "));
    } while (!validateNotEmpty(destination, "Destination"));

    // Check origin != destination
    if (origin == destination)
    {
        std::cout << "Error: Origin and Destination cannot be the same." << std::endl;
        return;
    }

    // Validate stops
    std::string stopsInput;
    do
    {
        stopsInput = trim(getInput("Enter Key Stops (separated by |): "));
    } while (!validateNotEmpty(stopsInput, "Key Stops"));

    // Validate travel time
    int travelTime;
    do
    {
        travelTime = getIntInput("Enter Estimated Travel Time (minutes): ");
    } while (!validatePositiveInt(travelTime, "Travel Time"));

    // Parse stops
    std::vector<std::string> stops;
    std::stringstream ss(stopsInput);
    std::string stop;
    while (std::getline(ss, stop, '|'))
    {
        std::string trimmedStop = trim(stop);
        if (!trimmedStop.empty())
        {
            stops.push_back(trimmedStop);
        }
    }

    if (stops.empty())
    {
        std::cout << "Error: At least one key stop is required." << std::endl;
        return;
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

    std::string origin = trim(getInput("Enter New Origin (or press Enter to keep current): "));
    std::string destination = trim(getInput("Enter New Destination (or press Enter to keep current): "));
    std::string stopsInput = trim(getInput("Enter New Key Stops (separated by | or press Enter to keep current): "));

    std::cout << "Enter New Travel Time (or 0 to keep current): ";
    int travelTime;
    std::cin >> travelTime;
    clearInputBuffer();

    // Validate travel time if provided
    if (travelTime < 0)
    {
        std::cout << "Error: Travel time cannot be negative." << std::endl;
        return;
    }

    // Update only if new values provided
    if (!origin.empty())
    {
        if (validateNotEmpty(origin, "Origin"))
            route->setOrigin(origin);
        else
            return;
    }
    if (!destination.empty())
    {
        if (validateNotEmpty(destination, "Destination"))
            route->setDestination(destination);
        else
            return;
    }
    if (!stopsInput.empty())
    {
        std::vector<std::string> stops;
        std::stringstream ss(stopsInput);
        std::string stop;
        while (std::getline(ss, stop, '|'))
        {
            std::string trimmedStop = trim(stop);
            if (!trimmedStop.empty())
            {
                stops.push_back(trimmedStop);
            }
        }
        if (!stops.empty())
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

    // Validate ID
    std::string id;
    do
    {
        id = trim(getInput("Enter Bus ID: "));
    } while (!validateId(id));

    // Validate capacity
    int capacity;
    do
    {
        capacity = getIntInput("Enter Capacity: ");
    } while (!validatePositiveInt(capacity, "Capacity"));

    clearInputBuffer();

    // Validate model
    std::string model;
    do
    {
        model = trim(getInput("Enter Model: "));
    } while (!validateNotEmpty(model, "Model"));

    // Validate status
    std::string status;
    do
    {
        status = trim(getInput("Enter Status (Active/Maintenance/Inactive): "));
    } while (!validateStatus(status));

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

    // Validate capacity if provided
    if (capacity < 0)
    {
        std::cout << "Error: Capacity cannot be negative." << std::endl;
        return;
    }

    std::string model = trim(getInput("Enter New Model (or press Enter to keep current): "));
    std::string status = trim(getInput("Enter New Status (or press Enter to keep current): "));

    // Update only if new values provided
    if (capacity > 0)
        bus->setCapacity(capacity);
    if (!model.empty())
    {
        if (validateNotEmpty(model, "Model"))
            bus->setModel(model);
        else
            return;
    }
    if (!status.empty())
    {
        if (validateStatus(status))
            bus->setStatus(status);
        else
            return;
    }

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

    // Validate ID
    std::string id;
    do
    {
        id = trim(getInput("Enter Driver ID: "));
    } while (!validateId(id));

    // Validate name
    std::string name;
    do
    {
        name = trim(getInput("Enter Name: "));
    } while (!validateNotEmpty(name, "Name"));

    // Validate contact
    std::string contact;
    do
    {
        contact = trim(getInput("Enter Contact Info: "));
    } while (!validateContact(contact));

    // Validate license
    std::string license;
    do
    {
        license = trim(getInput("Enter License Details: "));
    } while (!validateNotEmpty(license, "License Details"));

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

    std::string name = trim(getInput("Enter New Name (or press Enter to keep current): "));
    std::string contact = trim(getInput("Enter New Contact Info (or press Enter to keep current): "));
    std::string license = trim(getInput("Enter New License Details (or press Enter to keep current): "));

    // Update only if new values provided
    if (!name.empty())
    {
        if (validateNotEmpty(name, "Name"))
            driver->setName(name);
        else
            return;
    }
    if (!contact.empty())
    {
        if (validateContact(contact))
            driver->setContactInfo(contact);
        else
            return;
    }
    if (!license.empty())
    {
        if (validateNotEmpty(license, "License Details"))
            driver->setLicenseDetails(license);
        else
            return;
    }

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

    // Validate schedule ID
    std::string id;
    do
    {
        id = trim(getInput("Enter Schedule ID: "));
    } while (!validateId(id));

    // Validate route ID
    std::string routeId;
    do
    {
        routeId = trim(getInput("Enter Route ID: "));
    } while (!validateId(routeId));

    // Validate bus ID
    std::string busId;
    do
    {
        busId = trim(getInput("Enter Bus ID: "));
    } while (!validateId(busId));

    // Validate driver ID
    std::string driverId;
    do
    {
        driverId = trim(getInput("Enter Driver ID: "));
    } while (!validateId(driverId));

    // Validate date
    std::string date;
    do
    {
        date = trim(getInput("Enter Date (YYYY-MM-DD): "));
    } while (!validateDate(date));

    // Validate departure time
    std::string departureTime;
    do
    {
        departureTime = trim(getInput("Enter Departure Time (HH:MM): "));
    } while (!validateTime(departureTime));

    // Validate arrival time
    std::string arrivalTime;
    do
    {
        arrivalTime = trim(getInput("Enter Arrival Time (HH:MM): "));
    } while (!validateTime(arrivalTime));

    // Check departure before arrival
    if (departureTime >= arrivalTime)
    {
        std::cout << "Error: Departure time must be before arrival time." << std::endl;
        return;
    }

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

    std::string routeId = trim(getInput("Enter New Route ID (or press Enter to keep current): "));
    std::string busId = trim(getInput("Enter New Bus ID (or press Enter to keep current): "));
    std::string driverId = trim(getInput("Enter New Driver ID (or press Enter to keep current): "));
    std::string date = trim(getInput("Enter New Date (or press Enter to keep current): "));
    std::string departureTime = trim(getInput("Enter New Departure Time (or press Enter to keep current): "));
    std::string arrivalTime = trim(getInput("Enter New Arrival Time (or press Enter to keep current): "));

    // Validate if new values provided
    if (!routeId.empty() && !validateId(routeId))
        return;
    if (!busId.empty() && !validateId(busId))
        return;
    if (!driverId.empty() && !validateId(driverId))
        return;
    if (!date.empty() && !validateDate(date))
        return;
    if (!departureTime.empty() && !validateTime(departureTime))
        return;
    if (!arrivalTime.empty() && !validateTime(arrivalTime))
        return;

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
