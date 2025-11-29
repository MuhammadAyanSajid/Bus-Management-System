#include "../include/RouteManager.h"
#include "../include/DataSaver.h"
#include "../include/DisplayManager.h"
#include <iostream>
#include <algorithm>

using namespace std;

RouteManager::RouteManager(vector<Route> &routeList, const string &filename)
    : routes(routeList), dataFile(filename) {}

bool RouteManager::validateRoute(const Route &route) const
{
    if (route.getId().empty())
    {
        cout << "Error: Route ID cannot be empty." << endl;
        return false;
    }

    if (route.getOrigin().empty() || route.getDestination().empty())
    {
        cout << "Error: Origin and destination must be provided." << endl;
        return false;
    }

    if (route.getOrigin() == route.getDestination())
    {
        cout << "Error: Origin and destination must be different." << endl;
        return false;
    }

    if (route.getEstimatedTravelTime() <= 0)
    {
        cout << "Error: Travel time must be positive." << endl;
        return false;
    }

    return true;
}

bool RouteManager::routeExists(const string &routeId) const
{
    return any_of(routes.begin(), routes.end(),
                  [&routeId](const Route &r)
                  { return r.getId() == routeId; });
}

Route *RouteManager::findRoute(const string &routeId)
{
    auto it = find_if(routes.begin(), routes.end(),
                      [&routeId](const Route &r)
                      { return r.getId() == routeId; });

    if (it != routes.end())
    {
        return &(*it);
    }
    return nullptr;
}

bool RouteManager::addRoute(const Route &newRoute)
{
    if (!validateRoute(newRoute))
    {
        return false;
    }

    if (routeExists(newRoute.getId()))
    {
        cout << "Error: Route with ID " << newRoute.getId() << " already exists." << endl;
        return false;
    }

    routes.push_back(newRoute);
    cout << "Route " << newRoute.getId() << " added successfully." << endl;

    return saveToFile();
}

bool RouteManager::updateRoute(const string &routeId, const Route &updatedRoute)
{
    Route *route = findRoute(routeId);
    if (!route)
    {
        cout << "Error: Route with ID " << routeId << " not found." << endl;
        return false;
    }

    if (!validateRoute(updatedRoute))
    {
        return false;
    }

    *route = updatedRoute;
    cout << "Route " << routeId << " updated successfully." << endl;

    return saveToFile();
}

bool RouteManager::removeRoute(const string &routeId)
{
    auto it = find_if(routes.begin(), routes.end(),
                      [&routeId](const Route &r)
                      { return r.getId() == routeId; });

    if (it == routes.end())
    {
        cout << "Error: Route with ID " << routeId << " not found." << endl;
        return false;
    }

    routes.erase(it);
    cout << "Route " << routeId << " removed successfully." << endl;

    return saveToFile();
}

bool RouteManager::saveToFile()
{
    return DataSaver::saveRoutes(dataFile, routes);
}

void RouteManager::displayAllRoutes() const
{
    DisplayManager::displayRoutes(routes);
}

vector<Route> RouteManager::findRoutesByOrigin(const string &origin) const
{
    vector<Route> foundRoutes;
    for (const auto &route : routes)
    {
        if (route.getOrigin() == origin)
        {
            foundRoutes.push_back(route);
        }
    }
    return foundRoutes;
}

vector<Route> RouteManager::findRoutesByDestination(const string &destination) const
{
    vector<Route> foundRoutes;
    for (const auto &route : routes)
    {
        if (route.getDestination() == destination)
        {
            foundRoutes.push_back(route);
        }
    }
    return foundRoutes;
}

vector<Route> RouteManager::findRoutesByStop(const string &stop) const
{
    vector<Route> foundRoutes;
    for (const auto &route : routes)
    {
        const auto &stops = route.getKeyStops();
        if (find(stops.begin(), stops.end(), stop) != stops.end())
        {
            foundRoutes.push_back(route);
        }
    }
    return foundRoutes;
}
