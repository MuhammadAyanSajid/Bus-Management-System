#ifndef PASSENGERMENU_H
#define PASSENGERMENU_H

#include "RouteManager.h"
#include <vector>

class PassengerMenu
{
private:
    RouteManager &routeManager;

    void clearInputBuffer();
    std::string getInput(const std::string &prompt);
    int getIntInput(const std::string &prompt);

    void viewAllRoutes();
    void searchByOrigin();
    void searchByDestination();
    void searchByStop();
    void viewTravelTime();

public:
    PassengerMenu(RouteManager &rm);

    void show();

    void displayMenu() const;
};

#endif
