#include "../include/DriverDashboard.h"
#include "../include/DisplayManager.h"
#include <cstdlib>

static string trim(const string &str)
{
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == string::npos)
        return "";
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, (last - first + 1));
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

DriverDashboard::DriverDashboard(ScheduleManager &sm, DriverManager &dm, BusManager &bm, User *driverUser, const string &dId)
    : scheduleManager(sm), driverManager(dm), busManager(bm), driver(driverUser), driverId(dId) {}

void DriverDashboard::clearInputBuffer()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

string DriverDashboard::getInput(const string &prompt)
{
    string input;
    cout << prompt;
    getline(cin, input);
    return input;
}

int DriverDashboard::getIntInput(const string &prompt)
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

void DriverDashboard::displayMenu() const
{
    cout << "\n========================================" << endl;
    cout << "       DRIVER DASHBOARD" << endl;
    cout << "========================================" << endl;
    cout << "1. View Assigned Schedule" << endl;
    cout << "2. View Personal Profile" << endl;
    cout << "3. Update Contact Information" << endl;
    cout << "4. Request Day Off" << endl;
    cout << "5. View Bus Details" << endl;
    cout << "6. Logout" << endl;
    cout << "========================================" << endl;
}

void DriverDashboard::show()
{
    int choice;
    bool running = true;

    system("cls");
    cout << "\nWelcome to Driver Dashboard, " << driver->getUsername() << "!" << endl;
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
            viewAssignedSchedule();
            break;
        case 2:
            viewPersonalProfile();
            break;
        case 3:
            updateContactInfo();
            break;
        case 4:
            requestDayOff();
            break;
        case 5:
            viewBusDetails();
            break;
        case 6:
            system("cls");
            cout << "\nLogging out..." << endl;
            running = false;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }
}

void DriverDashboard::viewAssignedSchedule()
{
    system("cls");
    cout << "\n--- My Assigned Schedules ---" << endl;

    clearInputBuffer();
    string date = trim(getInput("Enter date to view schedules (YYYY-MM-DD) or press Enter for all: "));

    if (!date.empty() && !validateDate(date))
    {
        return;
    }

    vector<Schedule> driverSchedules = scheduleManager.getSchedulesByDriver(driverId);

    if (driverSchedules.empty())
    {
        cout << "No schedules assigned to you." << endl;
        return;
    }

    if (!date.empty())
    {
        vector<Schedule> filteredSchedules;
        for (const auto &schedule : driverSchedules)
        {
            if (schedule.getDate() == date)
            {
                filteredSchedules.push_back(schedule);
            }
        }
        driverSchedules = filteredSchedules;
    }

    if (driverSchedules.empty())
    {
        cout << "No schedules found for the specified date." << endl;
        return;
    }

    cout << "\n";
    DisplayManager::displaySchedules(driverSchedules);
}

void DriverDashboard::viewPersonalProfile()
{
    system("cls");
    cout << "\n--- My Profile ---" << endl;

    Driver *driverProfile = driverManager.findDriver(driverId);
    if (driverProfile)
    {
        cout << "\n";
        DisplayManager::displayDriver(*driverProfile);
    }
    else
    {
        cout << "Driver profile not found." << endl;
    }
}

void DriverDashboard::updateContactInfo()
{
    system("cls");
    cout << "\n--- Update Contact Information ---" << endl;

    Driver *driverProfile = driverManager.findDriver(driverId);
    if (!driverProfile)
    {
        cout << "Driver profile not found." << endl;
        return;
    }

    cout << "Current Contact Info: " << driverProfile->getContactInfo() << endl;

    clearInputBuffer();
    string newContact;
    do
    {
        newContact = trim(getInput("Enter new contact information (or press Enter to cancel): "));
        if (newContact.empty())
        {
            cout << "Update cancelled." << endl;
            return;
        }
    } while (!validateContact(newContact));

    driverProfile->setContactInfo(newContact);
    if (driverManager.updateDriver(driverId, *driverProfile))
    {
        cout << "Contact information updated successfully." << endl;
    }
}

void DriverDashboard::requestDayOff()
{
    system("cls");
    cout << "\n--- Request Day Off ---" << endl;

    clearInputBuffer();

    string date;
    do
    {
        date = trim(getInput("Enter date for day off (YYYY-MM-DD): "));
    } while (!validateDate(date));

    string reason = trim(getInput("Enter reason (optional): "));

    ofstream logFile("data/dayoff_requests.txt", ios::app);
    if (logFile.is_open())
    {
        logFile << driverId << "," << date << "," << reason << endl;
        logFile.close();
        cout << "Day off request submitted successfully." << endl;
        cout << "An administrator will review your request." << endl;
    }
    else
    {
        cout << "Error: Could not submit day off request." << endl;
    }
}

void DriverDashboard::viewBusDetails()
{
    system("cls");
    cout << "\n--- Bus Details ---" << endl;

    clearInputBuffer();
    string busId = getInput("Enter Bus ID to view details: ");

    Bus *bus = busManager.findBus(busId);
    if (bus)
    {
        cout << "\n";
        DisplayManager::displayBus(*bus);
    }
    else
    {
        cout << "Bus not found." << endl;
    }
}
