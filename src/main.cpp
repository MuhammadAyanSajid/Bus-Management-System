#include <iostream>
#include <string>
#include <limits>
#include "../include/DataLoader.h"
#include "../include/DisplayManager.h"
#include "../include/LoginManager.h"
#include "../include/RouteManager.h"
#include "../include/BusManager.h"
#include "../include/DriverManager.h"
#include "../include/ScheduleManager.h"
#include "../include/AdminDashboard.h"
#include "../include/DriverDashboard.h"
#include "../include/PassengerMenu.h"

// Helper function to trim whitespace
std::string trim(const std::string &str)
{
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == std::string::npos)
        return "";
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, (last - first + 1));
}

// Helper function to clear input buffer
void clearInputBuffer()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Helper function to get input
std::string getInput(const std::string &prompt)
{
    std::string input;
    std::cout << prompt;
    std::getline(std::cin, input);
    return input;
}

// Helper function to get integer input
int getIntInput(const std::string &prompt)
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
void displayMainMenu()
{
    std::cout << "\n========================================" << std::endl;
    std::cout << "   BUS MANAGEMENT SYSTEM" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "1. Admin Login" << std::endl;
    std::cout << "2. Driver Login" << std::endl;
    std::cout << "3. Passenger Services" << std::endl;
    std::cout << "4. Exit" << std::endl;
    std::cout << "========================================" << std::endl;
}

int main()
{
    // Define data file paths
    const std::string DATA_PATH = "data/";
    const std::string BUSES_FILE = DATA_PATH + "buses.txt";
    const std::string DRIVERS_FILE = DATA_PATH + "drivers.txt";
    const std::string ROUTES_FILE = DATA_PATH + "routes.txt";
    const std::string SCHEDULES_FILE = DATA_PATH + "schedules.txt";
    const std::string CREDENTIALS_FILE = DATA_PATH + "credentials.txt";

    // Load all data
    std::cout << "\n========================================" << std::endl;
    std::cout << "   INITIALIZING SYSTEM..." << std::endl;
    std::cout << "========================================" << std::endl;

    std::vector<Bus> buses = DataLoader::loadBuses(BUSES_FILE);
    std::vector<Driver> drivers = DataLoader::loadDrivers(DRIVERS_FILE);
    std::vector<Route> routes = DataLoader::loadRoutes(ROUTES_FILE);
    std::vector<Schedule> schedules = DataLoader::loadSchedules(SCHEDULES_FILE);
    std::vector<User> users = DataLoader::loadCredentials(CREDENTIALS_FILE);

    std::cout << "\nSystem initialized successfully!" << std::endl;

    // Create managers
    LoginManager loginManager(users);
    RouteManager routeManager(routes, ROUTES_FILE);
    BusManager busManager(buses, BUSES_FILE);
    DriverManager driverManager(drivers, DRIVERS_FILE);
    ScheduleManager scheduleManager(schedules, routes, buses, drivers, SCHEDULES_FILE);

    // Main application loop
    bool running = true;

    while (running)
    {
        displayMainMenu();
        int choice = getIntInput("Enter your choice: ");

        switch (choice)
        {
        case 1:
        { // Admin Login
            loginManager.displayLoginScreen("ADMIN");
            clearInputBuffer();
            std::string username = trim(getInput("Username: "));
            std::string password = trim(getInput("Password: "));

            if (username.empty())
            {
                std::cout << "\nError: Username cannot be empty." << std::endl;
                break;
            }
            if (password.empty())
            {
                std::cout << "\nError: Password cannot be empty." << std::endl;
                break;
            }

            if (loginManager.authenticate(username, password, UserRole::ADMIN))
            {
                AdminDashboard adminDashboard(routeManager, busManager, driverManager, scheduleManager, loginManager.getCurrentUser());
                adminDashboard.show();
                loginManager.logout();
            }
            break;
        }

        case 2:
        { // Driver Login
            loginManager.displayLoginScreen("DRIVER");
            clearInputBuffer();
            std::string username = trim(getInput("Username: "));
            std::string password = trim(getInput("Password: "));

            if (username.empty())
            {
                std::cout << "\nError: Username cannot be empty." << std::endl;
                break;
            }
            if (password.empty())
            {
                std::cout << "\nError: Password cannot be empty." << std::endl;
                break;
            }

            if (loginManager.authenticate(username, password, UserRole::DRIVER))
            {
                // Try to find driver ID (username might be driver ID)
                std::string driverId = username;
                DriverDashboard driverDashboard(scheduleManager, driverManager, busManager, loginManager.getCurrentUser(), driverId);
                driverDashboard.show();
                loginManager.logout();
            }
            break;
        }

        case 3:
        { // Passenger Services
            PassengerMenu passengerMenu(routeManager);
            passengerMenu.show();
            break;
        }

        case 4:
        { // Exit
            std::cout << "\n========================================" << std::endl;
            std::cout << "   Thank you for using" << std::endl;
            std::cout << "   Bus Management System" << std::endl;
            std::cout << "========================================" << std::endl;
            running = false;
            break;
        }

        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }

    return 0;
}
