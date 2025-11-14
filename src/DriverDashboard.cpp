#include "../include/DriverDashboard.h"
#include "../include/DisplayManager.h"
#include <iostream>
#include <limits>

// Constructor
DriverDashboard::DriverDashboard(ScheduleManager &sm, DriverManager &dm, BusManager &bm, User *driverUser, const std::string &dId)
    : scheduleManager(sm), driverManager(dm), busManager(bm), driver(driverUser), driverId(dId) {}

// Clear input buffer
void DriverDashboard::clearInputBuffer()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Get string input
std::string DriverDashboard::getInput(const std::string &prompt)
{
    std::string input;
    std::cout << prompt;
    std::getline(std::cin, input);
    return input;
}

// Get integer input
int DriverDashboard::getIntInput(const std::string &prompt)
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
void DriverDashboard::displayMenu() const
{
    std::cout << "\n========================================" << std::endl;
    std::cout << "       DRIVER DASHBOARD" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "1. View Assigned Schedule" << std::endl;
    std::cout << "2. View Personal Profile" << std::endl;
    std::cout << "3. Update Contact Information" << std::endl;
    std::cout << "4. Request Day Off" << std::endl;
    std::cout << "5. View Bus Details" << std::endl;
    std::cout << "6. Logout" << std::endl;
    std::cout << "========================================" << std::endl;
}

// Main dashboard loop
void DriverDashboard::show()
{
    int choice;
    bool running = true;

    std::cout << "\nWelcome to Driver Dashboard, " << driver->getUsername() << "!" << std::endl;

    while (running)
    {
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
            std::cout << "\nLogging out..." << std::endl;
            running = false;
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }
}

// View assigned schedule
void DriverDashboard::viewAssignedSchedule()
{
    std::cout << "\n--- My Assigned Schedules ---" << std::endl;

    clearInputBuffer();
    std::string date = getInput("Enter date to view schedules (YYYY-MM-DD) or press Enter for all: ");

    std::vector<Schedule> driverSchedules = scheduleManager.getSchedulesByDriver(driverId);

    if (driverSchedules.empty())
    {
        std::cout << "No schedules assigned to you." << std::endl;
        return;
    }

    // Filter by date if provided
    if (!date.empty())
    {
        std::vector<Schedule> filteredSchedules;
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
        std::cout << "No schedules found for the specified date." << std::endl;
        return;
    }

    std::cout << "\n";
    DisplayManager::displaySchedules(driverSchedules);
}

// View personal profile
void DriverDashboard::viewPersonalProfile()
{
    std::cout << "\n--- My Profile ---" << std::endl;

    Driver *driverProfile = driverManager.findDriver(driverId);
    if (driverProfile)
    {
        std::cout << "\n";
        DisplayManager::displayDriver(*driverProfile);
    }
    else
    {
        std::cout << "Driver profile not found." << std::endl;
    }
}

// Update contact information
void DriverDashboard::updateContactInfo()
{
    std::cout << "\n--- Update Contact Information ---" << std::endl;

    Driver *driverProfile = driverManager.findDriver(driverId);
    if (!driverProfile)
    {
        std::cout << "Driver profile not found." << std::endl;
        return;
    }

    std::cout << "Current Contact Info: " << driverProfile->getContactInfo() << std::endl;

    clearInputBuffer();
    std::string newContact = getInput("Enter new contact information: ");

    if (!newContact.empty())
    {
        driverProfile->setContactInfo(newContact);
        if (driverManager.updateDriver(driverId, *driverProfile))
        {
            std::cout << "Contact information updated successfully." << std::endl;
        }
    }
    else
    {
        std::cout << "Update cancelled." << std::endl;
    }
}

// Request day off
void DriverDashboard::requestDayOff()
{
    std::cout << "\n--- Request Day Off ---" << std::endl;

    clearInputBuffer();
    std::string date = getInput("Enter date for day off (YYYY-MM-DD): ");
    std::string reason = getInput("Enter reason (optional): ");

    // Log the request to a file
    std::ofstream logFile("data/dayoff_requests.txt", std::ios::app);
    if (logFile.is_open())
    {
        logFile << driverId << "," << date << "," << reason << std::endl;
        logFile.close();
        std::cout << "Day off request submitted successfully." << std::endl;
        std::cout << "An administrator will review your request." << std::endl;
    }
    else
    {
        std::cout << "Error: Could not submit day off request." << std::endl;
    }
}

// View bus details
void DriverDashboard::viewBusDetails()
{
    std::cout << "\n--- View Bus Details ---" << std::endl;

    clearInputBuffer();
    std::string busId = getInput("Enter Bus ID to view details: ");

    Bus *bus = busManager.findBus(busId);
    if (bus)
    {
        std::cout << "\n";
        DisplayManager::displayBus(*bus);
    }
    else
    {
        std::cout << "Bus not found." << std::endl;
    }
}
