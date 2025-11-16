#include "../include/AdminDashboard.h"
#include <cstdlib>

AdminDashboard::AdminDashboard(RouteManager &rm, BusManager &bm, DriverManager &dm, ScheduleManager &sm, User *adminUser)
    : routeManager(rm), busManager(bm), driverManager(dm), scheduleManager(sm), admin(adminUser) {}

static string trim(const string &str)
{
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == string::npos)
        return "";
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, (last - first + 1));
}

static bool validateId(const string &id)
{
    string trimmedId = trim(id);
    if (trimmedId.empty() || trimmedId.length() > 20)
    {
        cout << "Error: ID must be 1-20 characters long and cannot be empty." << endl;
        return false;
    }
    if (trimmedId.find(' ') != string::npos)
    {
        cout << "Error: ID cannot contain spaces." << endl;
        return false;
    }
    return true;
}

static bool validateNotEmpty(const string &str, const string &fieldName)
{
    string trimmedStr = trim(str);
    if (trimmedStr.empty())
    {
        cout << "Error: " << fieldName << " cannot be empty." << endl;
        return false;
    }
    return true;
}

static bool validateDate(const string &date)
{
    regex dateRegex(R"(^\d{4}-\d{2}-\d{2}$)");
    if (!regex_match(date, dateRegex))
    {
        cout << "Error: Date must be in YYYY-MM-DD format (e.g., 2025-11-16)." << endl;
        return false;
    }
    int year = stoi(date.substr(0, 4));
    int month = stoi(date.substr(5, 2));
    int day = stoi(date.substr(8, 2));
    if (month < 1 || month > 12)
    {
        cout << "Error: Month must be between 01 and 12." << endl;
        return false;
    }
    if (day < 1 || day > 31)
    {
        cout << "Error: Day must be between 01 and 31." << endl;
        return false;
    }
    if (year < 2000 || year > 2100)
    {
        cout << "Error: Year must be between 2000 and 2100." << endl;
        return false;
    }
    return true;
}

static bool validateTime(const string &time)
{
    regex timeRegex(R"(^([0-1]\d|2[0-3]):([0-5]\d)$)");
    if (!regex_match(time, timeRegex))
    {
        cout << "Error: Time must be in HH:MM format (e.g., 14:30, 09:00)." << endl;
        return false;
    }
    return true;
}

static bool validateStatus(const string &status)
{
    string upperStatus = status;
    transform(upperStatus.begin(), upperStatus.end(), upperStatus.begin(), ::toupper);
    if (upperStatus != "ACTIVE" && upperStatus != "MAINTENANCE" && upperStatus != "INACTIVE")
    {
        cout << "Error: Status must be Active, Maintenance, or Inactive." << endl;
        return false;
    }
    return true;
}

static bool validatePositiveInt(int value, const string &fieldName)
{
    if (value <= 0)
    {
        cout << "Error: " << fieldName << " must be a positive number." << endl;
        return false;
    }
    return true;
}

static bool validateContact(const string &contact)
{
    string trimmedContact = trim(contact);
    if (trimmedContact.empty())
    {
        cout << "Error: Contact information cannot be empty." << endl;
        return false;
    }
    if (trimmedContact.length() < 7)
    {
        cout << "Error: Contact information seems too short. Please provide valid phone or email." << endl;
        return false;
    }
    return true;
}

void AdminDashboard::clearInputBuffer()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

string AdminDashboard::getInput(const string &prompt)
{
    string input;
    cout << prompt;
    getline(cin, input);
    return input;
}

int AdminDashboard::getIntInput(const string &prompt)
{
    int value;
    while (true)
    {
        cout << prompt;
        if (cin >> value)
        {
            clearInputBuffer();
            return value;
        }
        else
        {
            cout << "Invalid input. Please enter a number." << endl;
            clearInputBuffer();
        }
    }
}

void AdminDashboard::displayMenu() const
{
    cout << "\n========================================" << endl;
    cout << "       ADMIN DASHBOARD" << endl;
    cout << "========================================" << endl;
    cout << "1. Manage Routes" << endl;
    cout << "2. Manage Schedules" << endl;
    cout << "3. Manage Buses" << endl;
    cout << "4. Manage Drivers" << endl;
    cout << "5. Logout" << endl;
    cout << "========================================" << endl;
}

void AdminDashboard::show()
{
    int choice;
    bool running = true;

    system("cls");
    cout << "\nWelcome to Admin Dashboard, " << admin->getUsername() << "!" << endl;
    cout << "\nPress Enter to continue...";
    cin.get();

    while (running)
    {
        system("cls");
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
            system("cls");
            cout << "\nLogging out..." << endl;
            running = false;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }
}

void AdminDashboard::manageRoutes()
{
    int choice;
    bool back = false;

    while (!back)
    {
        system("cls");
        cout << "\n--- Manage Routes ---" << endl;
        cout << "1. View All Routes" << endl;
        cout << "2. Add Route" << endl;
        cout << "3. Update Route" << endl;
        cout << "4. Remove Route" << endl;
        cout << "5. Back to Main Menu" << endl;

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
            cout << "Invalid choice." << endl;
        }
    }
}

void AdminDashboard::viewRoutes()
{
    cout << "\n";
    routeManager.displayAllRoutes();
}

void AdminDashboard::addRoute()
{
    system("cls");
    cout << "\n--- Add New Route ---" << endl;

    clearInputBuffer();

    string id;
    do
    {
        id = trim(getInput("Enter Route ID: "));
    } while (!validateId(id));

    string origin;
    do
    {
        origin = trim(getInput("Enter Origin: "));
    } while (!validateNotEmpty(origin, "Origin"));

    string destination;
    do
    {
        destination = trim(getInput("Enter Destination: "));
    } while (!validateNotEmpty(destination, "Destination"));

    if (origin == destination)
    {
        cout << "Error: Origin and Destination cannot be the same." << endl;
        return;
    }

    string stopsInput;
    do
    {
        stopsInput = trim(getInput("Enter Key Stops (separated by |): "));
    } while (!validateNotEmpty(stopsInput, "Key Stops"));

    int travelTime;
    do
    {
        travelTime = getIntInput("Enter Estimated Travel Time (minutes): ");
    } while (!validatePositiveInt(travelTime, "Travel Time"));

    vector<string> stops;
    stringstream ss(stopsInput);
    string stop;
    while (getline(ss, stop, '|'))
    {
        string trimmedStop = trim(stop);
        if (!trimmedStop.empty())
        {
            stops.push_back(trimmedStop);
        }
    }

    if (stops.empty())
    {
        cout << "Error: At least one key stop is required." << endl;
        return;
    }

    Route newRoute(id, origin, destination, stops, travelTime);
    routeManager.addRoute(newRoute);
}

void AdminDashboard::updateRoute()
{
    system("cls");
    cout << "\n--- Update Route ---" << endl;

    clearInputBuffer();
    string id = getInput("Enter Route ID to update: ");

    Route *route = routeManager.findRoute(id);
    if (!route)
    {
        cout << "Route not found." << endl;
        return;
    }

    cout << "\nCurrent Route Information:" << endl;
    routeManager.displayAllRoutes();

    string origin = trim(getInput("Enter New Origin (or press Enter to keep current): "));
    string destination = trim(getInput("Enter New Destination (or press Enter to keep current): "));
    string stopsInput = trim(getInput("Enter New Key Stops (separated by | or press Enter to keep current): "));

    cout << "Enter New Travel Time (or 0 to keep current): ";
    int travelTime;
    cin >> travelTime;
    clearInputBuffer();

    if (travelTime < 0)
    {
        cout << "Error: Travel time cannot be negative." << endl;
        return;
    }

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
        vector<string> stops;
        stringstream ss(stopsInput);
        string stop;
        while (getline(ss, stop, '|'))
        {
            string trimmedStop = trim(stop);
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

void AdminDashboard::removeRoute()
{
    system("cls");
    cout << "\n--- Remove Route ---" << endl;

    clearInputBuffer();
    string id = getInput("Enter Route ID to remove: ");

    string confirm = getInput("Are you sure you want to remove this route? (yes/no): ");
    if (confirm == "yes" || confirm == "y")
    {
        routeManager.removeRoute(id);
    }
    else
    {
        cout << "Operation cancelled." << endl;
    }
}

void AdminDashboard::manageBuses()
{
    int choice;
    bool back = false;

    while (!back)
    {
        system("cls");
        cout << "\n--- Manage Buses ---" << endl;
        cout << "1. View All Buses" << endl;
        cout << "2. Add Bus" << endl;
        cout << "3. Update Bus" << endl;
        cout << "4. Remove Bus" << endl;
        cout << "5. Back to Main Menu" << endl;

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
            cout << "Invalid choice." << endl;
        }
    }
}

void AdminDashboard::viewBuses()
{
    cout << "\n";
    busManager.displayAllBuses();
}

void AdminDashboard::addBus()
{
    system("cls");
    cout << "\n--- Add New Bus ---" << endl;

    clearInputBuffer();

    string id;
    do
    {
        id = trim(getInput("Enter Bus ID: "));
    } while (!validateId(id));

    int capacity;
    do
    {
        capacity = getIntInput("Enter Capacity: ");
    } while (!validatePositiveInt(capacity, "Capacity"));

    clearInputBuffer();

    string model;
    do
    {
        model = trim(getInput("Enter Model: "));
    } while (!validateNotEmpty(model, "Model"));

    string status;
    do
    {
        status = trim(getInput("Enter Status (Active/Maintenance/Inactive): "));
    } while (!validateStatus(status));

    Bus newBus(id, capacity, model, status);
    busManager.addBus(newBus);
}

void AdminDashboard::updateBus()
{
    system("cls");
    cout << "\n--- Update Bus ---" << endl;

    clearInputBuffer();
    string id = getInput("Enter Bus ID to update: ");

    Bus *bus = busManager.findBus(id);
    if (!bus)
    {
        cout << "Bus not found." << endl;
        return;
    }

    cout << "\nCurrent Bus Information:" << endl;
    busManager.displayAllBuses();

    cout << "Enter New Capacity (or 0 to keep current): ";
    int capacity;
    cin >> capacity;
    clearInputBuffer();

    if (capacity < 0)
    {
        cout << "Error: Capacity cannot be negative." << endl;
        return;
    }

    string model = trim(getInput("Enter New Model (or press Enter to keep current): "));
    string status = trim(getInput("Enter New Status (or press Enter to keep current): "));

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

void AdminDashboard::removeBus()
{
    system("cls");
    cout << "\n--- Remove Bus ---" << endl;

    clearInputBuffer();
    string id = getInput("Enter Bus ID to remove: ");

    string confirm = getInput("Are you sure you want to remove this bus? (yes/no): ");
    if (confirm == "yes" || confirm == "y")
    {
        busManager.removeBus(id);
    }
    else
    {
        cout << "Operation cancelled." << endl;
    }
}

void AdminDashboard::manageDrivers()
{
    int choice;
    bool back = false;

    while (!back)
    {
        system("cls");
        cout << "\n--- Manage Drivers ---" << endl;
        cout << "1. View All Drivers" << endl;
        cout << "2. Add Driver" << endl;
        cout << "3. Update Driver" << endl;
        cout << "4. Remove Driver" << endl;
        cout << "5. Back to Main Menu" << endl;

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
            cout << "Invalid choice." << endl;
        }
    }
}

void AdminDashboard::viewDrivers()
{
    cout << "\n";
    driverManager.displayAllDrivers();
}

void AdminDashboard::addDriver()
{
    system("cls");
    cout << "\n--- Add New Driver ---" << endl;

    clearInputBuffer();

    string id;
    do
    {
        id = trim(getInput("Enter Driver ID: "));
    } while (!validateId(id));

    string name;
    do
    {
        name = trim(getInput("Enter Name: "));
    } while (!validateNotEmpty(name, "Name"));

    string contact;
    do
    {
        contact = trim(getInput("Enter Contact Info: "));
    } while (!validateContact(contact));

    string license;
    do
    {
        license = trim(getInput("Enter License Details: "));
    } while (!validateNotEmpty(license, "License Details"));

    Driver newDriver(id, name, contact, license);
    driverManager.addDriver(newDriver);
}

void AdminDashboard::updateDriver()
{
    system("cls");
    cout << "\n--- Update Driver ---" << endl;

    clearInputBuffer();
    string id = getInput("Enter Driver ID to update: ");

    Driver *driver = driverManager.findDriver(id);
    if (!driver)
    {
        cout << "Driver not found." << endl;
        return;
    }

    cout << "\nCurrent Driver Information:" << endl;
    driverManager.displayAllDrivers();

    string name = trim(getInput("Enter New Name (or press Enter to keep current): "));
    string contact = trim(getInput("Enter New Contact Info (or press Enter to keep current): "));
    string license = trim(getInput("Enter New License Details (or press Enter to keep current): "));

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

void AdminDashboard::removeDriver()
{
    system("cls");
    cout << "\n--- Remove Driver ---" << endl;

    clearInputBuffer();
    string id = getInput("Enter Driver ID to remove: ");

    string confirm = getInput("Are you sure you want to remove this driver? (yes/no): ");
    if (confirm == "yes" || confirm == "y")
    {
        driverManager.removeDriver(id);
    }
    else
    {
        cout << "Operation cancelled." << endl;
    }
}

void AdminDashboard::manageSchedules()
{
    int choice;
    bool back = false;

    while (!back)
    {
        system("cls");
        cout << "\n--- Manage Schedules ---" << endl;
        cout << "1. View All Schedules" << endl;
        cout << "2. Add Schedule" << endl;
        cout << "3. Update Schedule" << endl;
        cout << "4. Remove Schedule" << endl;
        cout << "5. Back to Main Menu" << endl;

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
            cout << "Invalid choice." << endl;
        }
    }
}

void AdminDashboard::viewSchedules()
{
    cout << "\n";
    scheduleManager.displayAllSchedules();
}

void AdminDashboard::addSchedule()
{
    system("cls");
    cout << "\n--- Add New Schedule ---" << endl;

    clearInputBuffer();

    string id;
    do
    {
        id = trim(getInput("Enter Schedule ID: "));
    } while (!validateId(id));

    string routeId;
    do
    {
        routeId = trim(getInput("Enter Route ID: "));
    } while (!validateId(routeId));

    string busId;
    do
    {
        busId = trim(getInput("Enter Bus ID: "));
    } while (!validateId(busId));

    string driverId;
    do
    {
        driverId = trim(getInput("Enter Driver ID: "));
    } while (!validateId(driverId));

    string date;
    do
    {
        date = trim(getInput("Enter Date (YYYY-MM-DD): "));
    } while (!validateDate(date));

    string departureTime;
    do
    {
        departureTime = trim(getInput("Enter Departure Time (HH:MM): "));
    } while (!validateTime(departureTime));

    string arrivalTime;
    do
    {
        arrivalTime = trim(getInput("Enter Arrival Time (HH:MM): "));
    } while (!validateTime(arrivalTime));

    if (departureTime >= arrivalTime)
    {
        cout << "Error: Departure time must be before arrival time." << endl;
        return;
    }

    Schedule newSchedule(id, routeId, busId, driverId, date, departureTime, arrivalTime);
    scheduleManager.addSchedule(newSchedule);
}

void AdminDashboard::updateSchedule()
{
    system("cls");
    cout << "\n--- Update Schedule ---" << endl;

    clearInputBuffer();
    string id = getInput("Enter Schedule ID to update: ");

    Schedule *schedule = scheduleManager.findSchedule(id);
    if (!schedule)
    {
        cout << "Schedule not found." << endl;
        return;
    }

    cout << "\nCurrent Schedule Information:" << endl;
    scheduleManager.displayAllSchedules();

    string routeId = trim(getInput("Enter New Route ID (or press Enter to keep current): "));
    string busId = trim(getInput("Enter New Bus ID (or press Enter to keep current): "));
    string driverId = trim(getInput("Enter New Driver ID (or press Enter to keep current): "));
    string date = trim(getInput("Enter New Date (or press Enter to keep current): "));
    string departureTime = trim(getInput("Enter New Departure Time (or press Enter to keep current): "));
    string arrivalTime = trim(getInput("Enter New Arrival Time (or press Enter to keep current): "));

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

void AdminDashboard::removeSchedule()
{
    system("cls");
    cout << "\n--- Remove Schedule ---" << endl;

    clearInputBuffer();
    string id = getInput("Enter Schedule ID to remove: ");

    string confirm = getInput("Are you sure you want to remove this schedule? (yes/no): ");
    if (confirm == "yes" || confirm == "y")
    {
        scheduleManager.removeSchedule(id);
    }
    else
    {
        cout << "Operation cancelled." << endl;
    }
}
