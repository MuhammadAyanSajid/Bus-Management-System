#include "../include/PassengerMenu.h"
#include "../include/DisplayManager.h"
#include <iostream>
#include <limits>
#include <algorithm>

// Helper function to trim whitespace
static std::string trim(const std::string &str)
{
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == std::string::npos)
        return "";
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, (last - first + 1));
}

// Validate non-empty string
static bool validateNotEmpty(const std::string &str, const std::string &fieldName)
{
    if (str.empty())
    {
        std::cout << "Error: " << fieldName << " cannot be empty." << std::endl;
        return false;
    }
    return true;
}

// Constructor
PassengerMenu::PassengerMenu(RouteManager &rm) : routeManager(rm) {}

// Clear input buffer
void PassengerMenu::clearInputBuffer()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Get string input
std::string PassengerMenu::getInput(const std::string &prompt)
{
    std::string input;
    std::cout << prompt;
    std::getline(std::cin, input);
    return input;
}

// Get integer input
int PassengerMenu::getIntInput(const std::string &prompt)
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
void PassengerMenu::displayMenu() const
{
    std::cout << "\n========================================" << std::endl;
    std::cout << "       PASSENGER MENU" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "1. View All Available Routes" << std::endl;
    std::cout << "2. Search Routes by Origin" << std::endl;
    std::cout << "3. Search Routes by Destination" << std::endl;
    std::cout << "4. Search Routes by Stop" << std::endl;
    std::cout << "5. View Estimated Travel Time" << std::endl;
    std::cout << "6. Back to Main Menu" << std::endl;
    std::cout << "========================================" << std::endl;
}

// Main menu loop
void PassengerMenu::show()
{
    int choice;
    bool running = true;

    std::cout << "\nWelcome to Passenger Services!" << std::endl;

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
            std::cout << "\nReturning to main menu..." << std::endl;
            running = false;
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }
}

// View all routes
void PassengerMenu::viewAllRoutes()
{
    std::cout << "\n--- All Available Routes ---" << std::endl;
    routeManager.displayAllRoutes();
}

// Search by origin
void PassengerMenu::searchByOrigin()
{
    std::cout << "\n--- Search by Origin ---" << std::endl;

    clearInputBuffer();
    std::string origin = trim(getInput("Enter origin location: "));

    if (!validateNotEmpty(origin, "Origin"))
    {
        return;
    }

    // Get all routes (need access to the routes vector)
    // For now, we'll display all and note which match
    std::cout << "\nSearching for routes starting from: " << origin << std::endl;
    std::cout << "\nNote: Displaying all routes. Look for routes with matching origin." << std::endl;
    routeManager.displayAllRoutes();
}

// Search by destination
void PassengerMenu::searchByDestination()
{
    std::cout << "\n--- Search by Destination ---" << std::endl;

    clearInputBuffer();
    std::string destination = trim(getInput("Enter destination location: "));

    if (!validateNotEmpty(destination, "Destination"))
    {
        return;
    }

    std::cout << "\nSearching for routes ending at: " << destination << std::endl;
    std::cout << "\nNote: Displaying all routes. Look for routes with matching destination." << std::endl;
    routeManager.displayAllRoutes();
}

// Search by stop
void PassengerMenu::searchByStop()
{
    std::cout << "\n--- Search by Stop ---" << std::endl;

    clearInputBuffer();
    std::string stop = trim(getInput("Enter stop name: "));

    if (!validateNotEmpty(stop, "Stop name"))
    {
        return;
    }

    std::cout << "\nSearching for routes passing through: " << stop << std::endl;
    std::cout << "\nNote: Displaying all routes. Look for routes with matching stop in Key Stops column." << std::endl;
    routeManager.displayAllRoutes();
}

// View travel time
void PassengerMenu::viewTravelTime()
{
    std::cout << "\n--- View Estimated Travel Time ---" << std::endl;

    clearInputBuffer();
    std::string routeId = trim(getInput("Enter Route ID: "));

    if (!validateNotEmpty(routeId, "Route ID"))
    {
        return;
    }

    Route *route = routeManager.findRoute(routeId);
    if (route)
    {
        std::cout << "\n";
        DisplayManager::displayRoute(*route);
        std::cout << "\nEstimated Travel Time: " << route->getEstimatedTravelTime() << " minutes" << std::endl;
    }
    else
    {
        std::cout << "Route not found." << std::endl;
    }
}
