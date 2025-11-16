#include "../include/RouteManager.h"
#include "../include/DataSaver.h"
#include "../include/DisplayManager.h"
#include <iostream>
#include <algorithm>

RouteManager::RouteManager(std::vector<Route> &routeList, const std::string &filename)
    : routes(routeList), dataFile(filename) {}

bool RouteManager::validateRoute(const Route &route) const
{
    if (route.getId().empty())
    {
        std::cout << "Error: Route ID cannot be empty." << std::endl;
        return false;
    }

    if (route.getOrigin().empty() || route.getDestination().empty())
    {
        std::cout << "Error: Origin and destination must be provided." << std::endl;
        return false;
    }

    if (route.getOrigin() == route.getDestination())
    {
        std::cout << "Error: Origin and destination must be different." << std::endl;
        return false;
    }

    if (route.getEstimatedTravelTime() <= 0)
    {
        std::cout << "Error: Travel time must be positive." << std::endl;
        return false;
    }

    return true;
}

bool RouteManager::routeExists(const std::string &routeId) const
{
    return std::any_of(routes.begin(), routes.end(),
                       [&routeId](const Route &r)
                       { return r.getId() == routeId; });
}

Route *RouteManager::findRoute(const std::string &routeId)
{
    auto it = std::find_if(routes.begin(), routes.end(),
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
        std::cout << "Error: Route with ID " << newRoute.getId() << " already exists." << std::endl;
        return false;
    }

    routes.push_back(newRoute);
    std::cout << "Route " << newRoute.getId() << " added successfully." << std::endl;

    return saveToFile();
}

bool RouteManager::updateRoute(const std::string &routeId, const Route &updatedRoute)
{
    Route *route = findRoute(routeId);
    if (!route)
    {
        std::cout << "Error: Route with ID " << routeId << " not found." << std::endl;
        return false;
    }

    if (!validateRoute(updatedRoute))
    {
        return false;
    }

    *route = updatedRoute;
    std::cout << "Route " << routeId << " updated successfully." << std::endl;

    return saveToFile();
}

bool RouteManager::removeRoute(const std::string &routeId)
{
    auto it = std::find_if(routes.begin(), routes.end(),
                           [&routeId](const Route &r)
                           { return r.getId() == routeId; });

    if (it == routes.end())
    {
        std::cout << "Error: Route with ID " << routeId << " not found." << std::endl;
        return false;
    }

    routes.erase(it);
    std::cout << "Route " << routeId << " removed successfully." << std::endl;

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
