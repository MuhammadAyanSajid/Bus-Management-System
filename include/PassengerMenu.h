#ifndef PASSENGERMENU_H
#define PASSENGERMENU_H

#include "RouteManager.h"
#include <vector>

using std::string;
using std::vector;

class PassengerMenu
{
private:
    RouteManager &routeManager;

    void clearInputBuffer();
    string getInput(const string &prompt);
    int getIntInput(const string &prompt);

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
