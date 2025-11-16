#include "../include/DataLoader.h"
#include <fstream>
#include <sstream>
#include <iostream>

std::vector<std::string> DataLoader::splitCSV(const std::string &line, char delimiter)
{
    std::vector<std::string> tokens;
    std::stringstream ss(line);
    std::string token;

    while (std::getline(ss, token, delimiter))
    {
        tokens.push_back(token);
    }

    return tokens;
}

std::vector<std::string> DataLoader::parseKeyStops(const std::string &stopsStr)
{
    return splitCSV(stopsStr, '|');
}

void DataLoader::logError(const std::string &filename, int lineNumber, const std::string &error)
{
    std::cerr << "Error in " << filename << " at line " << lineNumber << ": " << error << std::endl;
}

std::vector<Bus> DataLoader::loadBuses(const std::string &filename)
{
    std::vector<Bus> buses;
    std::ifstream file(filename);

    if (!file.is_open())
    {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return buses;
    }

    std::string line;
    int lineNumber = 0;

    while (std::getline(file, line))
    {
        lineNumber++;

        if (line.empty())
        {
            continue;
        }

        std::vector<std::string> tokens = splitCSV(line);

        if (tokens.size() != 4)
        {
            logError(filename, lineNumber, "Expected 4 fields, got " + std::to_string(tokens.size()));
            continue;
        }

        try
        {
            std::string id = tokens[0];
            int capacity = std::stoi(tokens[1]);
            std::string model = tokens[2];
            std::string status = tokens[3];

            buses.push_back(Bus(id, capacity, model, status));
        }
        catch (const std::exception &e)
        {
            logError(filename, lineNumber, "Parsing error: " + std::string(e.what()));
        }
    }

    file.close();
    std::cout << "Loaded " << buses.size() << " buses from " << filename << std::endl;
    return buses;
}

std::vector<Driver> DataLoader::loadDrivers(const std::string &filename)
{
    std::vector<Driver> drivers;
    std::ifstream file(filename);

    if (!file.is_open())
    {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return drivers;
    }

    std::string line;
    int lineNumber = 0;

    while (std::getline(file, line))
    {
        lineNumber++;

        if (line.empty())
        {
            continue;
        }

        std::vector<std::string> tokens = splitCSV(line);

        if (tokens.size() != 4)
        {
            logError(filename, lineNumber, "Expected 4 fields, got " + std::to_string(tokens.size()));
            continue;
        }

        std::string id = tokens[0];
        std::string name = tokens[1];
        std::string contactInfo = tokens[2];
        std::string licenseDetails = tokens[3];

        drivers.push_back(Driver(id, name, contactInfo, licenseDetails));
    }

    file.close();
    std::cout << "Loaded " << drivers.size() << " drivers from " << filename << std::endl;
    return drivers;
}

std::vector<Route> DataLoader::loadRoutes(const std::string &filename)
{
    std::vector<Route> routes;
    std::ifstream file(filename);

    if (!file.is_open())
    {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return routes;
    }

    std::string line;
    int lineNumber = 0;

    while (std::getline(file, line))
    {
        lineNumber++;

        if (line.empty())
        {
            continue;
        }

        std::vector<std::string> tokens = splitCSV(line);

        if (tokens.size() != 5)
        {
            logError(filename, lineNumber, "Expected 5 fields, got " + std::to_string(tokens.size()));
            continue;
        }

        try
        {
            std::string id = tokens[0];
            std::string origin = tokens[1];
            std::string destination = tokens[2];
            std::vector<std::string> keyStops = parseKeyStops(tokens[3]);
            int estimatedTravelTime = std::stoi(tokens[4]);

            routes.push_back(Route(id, origin, destination, keyStops, estimatedTravelTime));
        }
        catch (const std::exception &e)
        {
            logError(filename, lineNumber, "Parsing error: " + std::string(e.what()));
        }
    }

    file.close();
    std::cout << "Loaded " << routes.size() << " routes from " << filename << std::endl;
    return routes;
}

std::vector<Schedule> DataLoader::loadSchedules(const std::string &filename)
{
    std::vector<Schedule> schedules;
    std::ifstream file(filename);

    if (!file.is_open())
    {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return schedules;
    }

    std::string line;
    int lineNumber = 0;

    while (std::getline(file, line))
    {
        lineNumber++;

        if (line.empty())
        {
            continue;
        }

        std::vector<std::string> tokens = splitCSV(line);

        if (tokens.size() != 7)
        {
            logError(filename, lineNumber, "Expected 7 fields, got " + std::to_string(tokens.size()));
            continue;
        }

        std::string id = tokens[0];
        std::string routeId = tokens[1];
        std::string busId = tokens[2];
        std::string driverId = tokens[3];
        std::string date = tokens[4];
        std::string departureTime = tokens[5];
        std::string arrivalTime = tokens[6];

        schedules.push_back(Schedule(id, routeId, busId, driverId, date, departureTime, arrivalTime));
    }

    file.close();
    std::cout << "Loaded " << schedules.size() << " schedules from " << filename << std::endl;
    return schedules;
}

std::vector<User> DataLoader::loadCredentials(const std::string &filename)
{
    std::vector<User> users;
    std::ifstream file(filename);

    if (!file.is_open())
    {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return users;
    }

    std::string line;
    int lineNumber = 0;

    while (std::getline(file, line))
    {
        lineNumber++;

        if (line.empty())
        {
            continue;
        }

        std::vector<std::string> tokens = splitCSV(line);

        if (tokens.size() != 3)
        {
            logError(filename, lineNumber, "Expected 3 fields, got " + std::to_string(tokens.size()));
            continue;
        }

        std::string username = tokens[0];
        std::string password = tokens[1];
        UserRole role = User::stringToRole(tokens[2]);

        users.push_back(User(username, password, role));
    }

    file.close();
    std::cout << "Loaded " << users.size() << " user credentials from " << filename << std::endl;
    return users;
}
