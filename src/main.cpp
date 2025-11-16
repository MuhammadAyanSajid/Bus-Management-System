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

string trim(const string &str)
{
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == string::npos)
        return "";
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, (last - first + 1));
}

void clearInputBuffer()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

string getInput(const string &prompt)
{
    string input;
    cout << prompt;
    getline(cin, input);
    return input;
}

int getIntInput(const string &prompt)
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

void displayMainMenu()
{
    cout << "\n========================================" << endl;
    cout << "   BUS MANAGEMENT SYSTEM" << endl;
    cout << "========================================" << endl;
    cout << "1. Admin Login" << endl;
    cout << "2. Driver Login" << endl;
    cout << "3. Passenger Services" << endl;
    cout << "4. Exit" << endl;
    cout << "========================================" << endl;
}

int main()
{
    const string DATA_PATH = "data/";
    const string BUSES_FILE = DATA_PATH + "buses.txt";
    const string DRIVERS_FILE = DATA_PATH + "drivers.txt";
    const string ROUTES_FILE = DATA_PATH + "routes.txt";
    const string SCHEDULES_FILE = DATA_PATH + "schedules.txt";
    const string CREDENTIALS_FILE = DATA_PATH + "credentials.txt";

    cout << "\n========================================" << endl;
    cout << "   INITIALIZING SYSTEM..." << endl;
    cout << "========================================" << endl;

    vector<Bus> buses = DataLoader::loadBuses(BUSES_FILE);
    vector<Driver> drivers = DataLoader::loadDrivers(DRIVERS_FILE);
    vector<Route> routes = DataLoader::loadRoutes(ROUTES_FILE);
    vector<Schedule> schedules = DataLoader::loadSchedules(SCHEDULES_FILE);
    vector<User> users = DataLoader::loadCredentials(CREDENTIALS_FILE);

    cout << "\nSystem initialized successfully!" << endl;
    cout << "\nPress Enter to continue...";
    cin.get();
    system("cls");

    LoginManager loginManager(users);
    RouteManager routeManager(routes, ROUTES_FILE);
    BusManager busManager(buses, BUSES_FILE);
    DriverManager driverManager(drivers, DRIVERS_FILE);
    ScheduleManager scheduleManager(schedules, routes, buses, drivers, SCHEDULES_FILE);

    bool running = true;

    while (running)
    {
        system("cls");
        displayMainMenu();
        int choice = getIntInput("Enter your choice: ");

        switch (choice)
        {
        case 1:
        {
            system("cls");
            loginManager.displayLoginScreen("ADMIN");
            clearInputBuffer();
            string username = trim(getInput("Username: "));
            string password = trim(getInput("Password: "));

            if (username.empty())
            {
                cout << "\nError: Username cannot be empty." << endl;
                break;
            }
            if (password.empty())
            {
                cout << "\nError: Password cannot be empty." << endl;
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
        {
            system("cls");
            loginManager.displayLoginScreen("DRIVER");
            clearInputBuffer();
            string username = trim(getInput("Username: "));
            string password = trim(getInput("Password: "));

            if (username.empty())
            {
                cout << "\nError: Username cannot be empty." << endl;
                break;
            }
            if (password.empty())
            {
                cout << "\nError: Password cannot be empty." << endl;
                break;
            }

            if (loginManager.authenticate(username, password, UserRole::DRIVER))
            {
                string driverId = username;
                DriverDashboard driverDashboard(scheduleManager, driverManager, busManager, loginManager.getCurrentUser(), driverId);
                driverDashboard.show();
                loginManager.logout();
            }
            break;
        }

        case 3:
        {
            system("cls");
            PassengerMenu passengerMenu(routeManager);
            passengerMenu.show();
            break;
        }

        case 4:
        {
            system("cls");
            cout << "\n========================================" << endl;
            cout << "   Thank you for using" << endl;
            cout << "   Bus Management System" << endl;
            cout << "========================================" << endl;
            running = false;
            break;
        }

        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
