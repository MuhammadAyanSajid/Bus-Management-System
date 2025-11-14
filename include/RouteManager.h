#ifndef ROUTEMANAGER_H
#define ROUTEMANAGER_H

#include <string>
#include <vector>
#include "Route.h"

class RouteManager
{
private:
    std::vector<Route> &routes;
    std::string dataFile;

public:
    // Constructor
    RouteManager(std::vector<Route> &routeList, const std::string &filename);

    // CRUD operations
    bool addRoute(const Route &newRoute);
    bool updateRoute(const std::string &routeId, const Route &updatedRoute);
    bool removeRoute(const std::string &routeId);

    // Query operations
    Route *findRoute(const std::string &routeId);
    bool routeExists(const std::string &routeId) const;

    // Save to file
    bool saveToFile();

    // Display all routes
    void displayAllRoutes() const;

    // Validation
    bool validateRoute(const Route &route) const;
};

#endif // ROUTEMANAGER_H
