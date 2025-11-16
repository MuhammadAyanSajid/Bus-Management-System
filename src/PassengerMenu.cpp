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

    system("cls");
    cout << "\nWelcome to Passenger Services!" << endl;
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
            system("cls");
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
    system("cls");
    cout << "\n--- All Available Routes ---" << endl;
    routeManager.displayAllRoutes();
}

void PassengerMenu::searchByOrigin()
{
    system("cls");
    cout << "\n--- Search by Origin ---" << endl;

    clearInputBuffer();
    string origin = trim(getInput("Enter origin location: "));

    if (!validateNotEmpty(origin, "Origin"))
    {
        return;
    }

    cout << "\nSearching for routes starting from: " << origin << endl;
    cout << "\nNote: Displaying all routes. Look for routes with matching origin." << endl;
    routeManager.displayAllRoutes();
}

void PassengerMenu::searchByDestination()
{
    system("cls");
    cout << "\n--- Search by Destination ---" << endl;

    clearInputBuffer();
    string destination = trim(getInput("Enter destination location: "));

    if (!validateNotEmpty(destination, "Destination"))
    {
        return;
    }

    cout << "\nSearching for routes ending at: " << destination << endl;
    cout << "\nNote: Displaying all routes. Look for routes with matching destination." << endl;
    routeManager.displayAllRoutes();
}

void PassengerMenu::searchByStop()
{
    system("cls");
    cout << "\n--- Search by Stop ---" << endl;

    clearInputBuffer();
    string stop = trim(getInput("Enter stop name: "));

    if (!validateNotEmpty(stop, "Stop name"))
    {
        return;
    }

    cout << "\nSearching for routes passing through: " << stop << endl;
    cout << "\nNote: Displaying all routes. Look for routes with matching stop in Key Stops column." << endl;
    routeManager.displayAllRoutes();
}

void PassengerMenu::viewTravelTime()
{
    system("cls");
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
