#include "../include/RouteManager.h"
#include "../include/DataSaver.h"
#include "../include/DisplayManager.h"
#include <iostream>
#include <algorithm>

// Constructor
RouteManager::RouteManager(std::vector<Route> &routeList, const std::string &filename)
    : routes(routeList), dataFile(filename) {}

// Validate route
bool RouteManager::validateRoute(const Route &route) const
{
    // Check if ID is not empty
    if (route.getId().empty())
    {
        std::cout << "Error: Route ID cannot be empty." << std::endl;
        return false;
    }

    // Check if origin and destination are provided
    if (route.getOrigin().empty() || route.getDestination().empty())
    {
        std::cout << "Error: Origin and destination must be provided." << std::endl;
        return false;
    }

    // Check if at least origin and destination are different
    if (route.getOrigin() == route.getDestination())
    {
        std::cout << "Error: Origin and destination must be different." << std::endl;
        return false;
    }

    // Check if travel time is positive
    if (route.getEstimatedTravelTime() <= 0)
    {
        std::cout << "Error: Travel time must be positive." << std::endl;
        return false;
    }

    return true;
}

// Check if route exists
bool RouteManager::routeExists(const std::string &routeId) const
{
    return std::any_of(routes.begin(), routes.end(),
                       [&routeId](const Route &r)
                       { return r.getId() == routeId; });
}

// Find route by ID
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

// Add new route
bool RouteManager::addRoute(const Route &newRoute)
{
    // Validate route
    if (!validateRoute(newRoute))
    {
        return false;
    }

    // Check if route ID already exists
    if (routeExists(newRoute.getId()))
    {
        std::cout << "Error: Route with ID " << newRoute.getId() << " already exists." << std::endl;
        return false;
    }

    // Add route
    routes.push_back(newRoute);
    std::cout << "Route " << newRoute.getId() << " added successfully." << std::endl;

    // Save to file
    return saveToFile();
}

// Update existing route
bool RouteManager::updateRoute(const std::string &routeId, const Route &updatedRoute)
{
    // Find route
    Route *route = findRoute(routeId);
    if (!route)
    {
        std::cout << "Error: Route with ID " << routeId << " not found." << std::endl;
        return false;
    }

    // Validate updated route
    if (!validateRoute(updatedRoute))
    {
        return false;
    }

    // Update route
    *route = updatedRoute;
    std::cout << "Route " << routeId << " updated successfully." << std::endl;

    // Save to file
    return saveToFile();
}

// Remove route
bool RouteManager::removeRoute(const std::string &routeId)
{
    // Find route
    auto it = std::find_if(routes.begin(), routes.end(),
                           [&routeId](const Route &r)
                           { return r.getId() == routeId; });

    if (it == routes.end())
    {
        std::cout << "Error: Route with ID " << routeId << " not found." << std::endl;
        return false;
    }

    // Remove route
    routes.erase(it);
    std::cout << "Route " << routeId << " removed successfully." << std::endl;

    // Save to file
    return saveToFile();
}

// Save to file
bool RouteManager::saveToFile()
{
    return DataSaver::saveRoutes(dataFile, routes);
}

// Display all routes
void RouteManager::displayAllRoutes() const
{
    DisplayManager::displayRoutes(routes);
}
