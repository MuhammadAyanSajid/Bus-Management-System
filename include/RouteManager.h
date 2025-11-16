#ifndef ROUTEMANAGER_H
#define ROUTEMANAGER_H

#include <string>
#include <vector>
#include "Route.h"

using std::string;
using std::vector;

class RouteManager
{
private:
    vector<Route> &routes;
    string dataFile;

public:
    // Constructor
    RouteManager(vector<Route> &routeList, const string &filename);

    // CRUD operations
    bool addRoute(const Route &newRoute);
    bool updateRoute(const string &routeId, const Route &updatedRoute);
    bool removeRoute(const string &routeId);

    // Query operations
    Route *findRoute(const string &routeId);
    bool routeExists(const string &routeId) const;

    // Save to file
    bool saveToFile();

    // Display all routes
    void displayAllRoutes() const;

    // Validation
    bool validateRoute(const Route &route) const;
};

#endif // ROUTEMANAGER_H
