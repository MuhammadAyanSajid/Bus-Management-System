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
    RouteManager(vector<Route> &routeList, const string &filename);

    bool addRoute(const Route &newRoute);
    bool updateRoute(const string &routeId, const Route &updatedRoute);
    bool removeRoute(const string &routeId);

    Route *findRoute(const string &routeId);
    bool routeExists(const string &routeId) const;

    bool saveToFile();

    void displayAllRoutes() const;

    vector<Route> findRoutesByOrigin(const string &origin) const;
    vector<Route> findRoutesByDestination(const string &destination) const;
    vector<Route> findRoutesByStop(const string &stop) const;

    bool validateRoute(const Route &route) const;
};

#endif
