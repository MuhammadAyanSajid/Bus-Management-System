#ifndef PASSENGERMENU_H
#define PASSENGERMENU_H

#include "RouteManager.h"
#include <vector>

class PassengerMenu
{
private:
    RouteManager &routeManager;

    // Helper functions
    void clearInputBuffer();
    std::string getInput(const std::string &prompt);
    int getIntInput(const std::string &prompt);

    // Menu functions
    void viewAllRoutes();
    void searchByOrigin();
    void searchByDestination();
    void searchByStop();
    void viewTravelTime();

public:
    // Constructor
    PassengerMenu(RouteManager &rm);

    // Main menu
    void show();

    // Display menu
    void displayMenu() const;
};

#endif // PASSENGERMENU_H
