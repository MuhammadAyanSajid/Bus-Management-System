#include "../include/PassengerMenu.h"
#include "../include/DisplayManager.h"
#include <iostream>
#include <limits>
#include <algorithm>
#include <cstdlib>

using namespace std;
#include <cstdlib>

static string trim(const string &str)
{
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == string::npos)
        return "";
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, (last - first + 1));
}

static bool validateNotEmpty(const string &str, const string &fieldName)
{
    if (str.empty())
    {
        cout << "Error: " << fieldName << " cannot be empty." << endl;
        return false;
    }
    return true;
}

PassengerMenu::PassengerMenu(RouteManager &rm) : routeManager(rm) {}

void PassengerMenu::clearInputBuffer()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

string PassengerMenu::getInput(const string &prompt)
{
    string input;
    cout << prompt;
    getline(cin, input);
    return input;
}

int PassengerMenu::getIntInput(const string &prompt)
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

void PassengerMenu::displayMenu() const
{
    cout << "\n========================================" << endl;
    cout << "       PASSENGER MENU" << endl;
    cout << "========================================" << endl;
    cout << "1. View All Available Routes" << endl;
    cout << "2. Search Routes by Origin" << endl;
    cout << "3. Search Routes by Destination" << endl;
    cout << "4. Search Routes by Stop" << endl;
    cout << "5. View Estimated Travel Time" << endl;
    cout << "6. Back to Main Menu" << endl;
    cout << "========================================" << endl;
}

void PassengerMenu::show()
{
    int choice;
    bool running = true;

    cout << "\nWelcome to Passenger Services!" << endl;
    cout << "\nPress Enter to continue...";
    cin.get();

    while (running)
    {

        displayMenu();
        choice = getIntInput("Enter your choice: ");

        switch (choice)
        {
        case 1:
            viewAllRoutes();
            break;
        case 2:
            searchByOrigin();
            break;
        case 3:
            searchByDestination();
            break;
        case 4:
            searchByStop();
            break;
        case 5:
            viewTravelTime();
            break;
        case 6:

            cout << "\nReturning to main menu..." << endl;
            running = false;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }
}

void PassengerMenu::viewAllRoutes()
{

    cout << "\n--- All Available Routes ---" << endl;
    routeManager.displayAllRoutes();
}

void PassengerMenu::searchByOrigin()
{

    cout << "\n--- Search by Origin ---" << endl;

    string origin = trim(getInput("Enter origin location: "));

    if (!validateNotEmpty(origin, "Origin"))
    {
        return;
    }

    cout << "\nSearching for routes starting from: " << origin << endl;
    vector<Route> foundRoutes = routeManager.findRoutesByOrigin(origin);
    if (foundRoutes.empty())
    {
        cout << "No routes found starting from " << origin << "." << endl;
    }
    else
    {
        DisplayManager::displayRoutes(foundRoutes);
    }
}

void PassengerMenu::searchByDestination()
{

    cout << "\n--- Search by Destination ---" << endl;

    string destination = trim(getInput("Enter destination location: "));

    if (!validateNotEmpty(destination, "Destination"))
    {
        return;
    }

    cout << "\nSearching for routes ending at: " << destination << endl;
    vector<Route> foundRoutes = routeManager.findRoutesByDestination(destination);
    if (foundRoutes.empty())
    {
        cout << "No routes found ending at " << destination << "." << endl;
    }
    else
    {
        DisplayManager::displayRoutes(foundRoutes);
    }
}

void PassengerMenu::searchByStop()
{

    cout << "\n--- Search by Stop ---" << endl;

    string stop = trim(getInput("Enter stop name: "));

    if (!validateNotEmpty(stop, "Stop name"))
    {
        return;
    }

    cout << "\nSearching for routes passing through: " << stop << endl;
    vector<Route> foundRoutes = routeManager.findRoutesByStop(stop);
    if (foundRoutes.empty())
    {
        cout << "No routes found passing through " << stop << "." << endl;
    }
    else
    {
        DisplayManager::displayRoutes(foundRoutes);
    }
}
void PassengerMenu::viewTravelTime()
{

    cout << "\n--- View Estimated Travel Time ---" << endl;

    clearInputBuffer();
    string routeId = trim(getInput("Enter Route ID: "));

    if (!validateNotEmpty(routeId, "Route ID"))
    {
        return;
    }

    Route *route = routeManager.findRoute(routeId);
    if (route)
    {
        cout << "\n";
        DisplayManager::displayRoute(*route);
        cout << "\nEstimated Travel Time: " << route->getEstimatedTravelTime() << " minutes" << endl;
    }
    else
    {
        cout << "Route not found." << endl;
    }
}
