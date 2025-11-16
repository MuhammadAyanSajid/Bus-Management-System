#include "../include/DataLoader.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

vector<string> DataLoader::splitCSV(const string &line, char delimiter)
{
    vector<string> tokens;
    stringstream ss(line);
    string token;

    while (getline(ss, token, delimiter))
    {
        tokens.push_back(token);
    }

    return tokens;
}

vector<string> DataLoader::parseKeyStops(const string &stopsStr)
{
    return splitCSV(stopsStr, '|');
}

void DataLoader::logError(const string &filename, int lineNumber, const string &error)
{
    cerr << "Error in " << filename << " at line " << lineNumber << ": " << error << endl;
}

vector<Bus> DataLoader::loadBuses(const string &filename)
{
    vector<Bus> buses;
    ifstream file(filename);

    if (!file.is_open())
    {
        cerr << "Error: Could not open file " << filename << endl;
        return buses;
    }

    string line;
    int lineNumber = 0;

    while (getline(file, line))
    {
        lineNumber++;

        if (line.empty())
        {
            continue;
        }

        vector<string> tokens = splitCSV(line);

        if (tokens.size() != 4)
        {
            logError(filename, lineNumber, "Expected 4 fields, got " + to_string(tokens.size()));
            continue;
        }

        try
        {
            string id = tokens[0];
            int capacity = stoi(tokens[1]);
            string model = tokens[2];
            string status = tokens[3];

            buses.push_back(Bus(id, capacity, model, status));
        }
        catch (const exception &e)
        {
            logError(filename, lineNumber, "Parsing error: " + string(e.what()));
        }
    }

    file.close();
    cout << "Loaded " << buses.size() << " buses from " << filename << endl;
    return buses;
}

vector<Driver> DataLoader::loadDrivers(const string &filename)
{
    vector<Driver> drivers;
    ifstream file(filename);

    if (!file.is_open())
    {
        cerr << "Error: Could not open file " << filename << endl;
        return drivers;
    }

    string line;
    int lineNumber = 0;

    while (getline(file, line))
    {
        lineNumber++;

        if (line.empty())
        {
            continue;
        }

        vector<string> tokens = splitCSV(line);

        if (tokens.size() != 4)
        {
            logError(filename, lineNumber, "Expected 4 fields, got " + to_string(tokens.size()));
            continue;
        }

        string id = tokens[0];
        string name = tokens[1];
        string contactInfo = tokens[2];
        string licenseDetails = tokens[3];

        drivers.push_back(Driver(id, name, contactInfo, licenseDetails));
    }

    file.close();
    cout << "Loaded " << drivers.size() << " drivers from " << filename << endl;
    return drivers;
}

vector<Route> DataLoader::loadRoutes(const string &filename)
{
    vector<Route> routes;
    ifstream file(filename);

    if (!file.is_open())
    {
        cerr << "Error: Could not open file " << filename << endl;
        return routes;
    }

    string line;
    int lineNumber = 0;

    while (getline(file, line))
    {
        lineNumber++;

        if (line.empty())
        {
            continue;
        }

        vector<string> tokens = splitCSV(line);

        if (tokens.size() != 5)
        {
            logError(filename, lineNumber, "Expected 5 fields, got " + to_string(tokens.size()));
            continue;
        }

        try
        {
            string id = tokens[0];
            string origin = tokens[1];
            string destination = tokens[2];
            vector<string> keyStops = parseKeyStops(tokens[3]);
            int estimatedTravelTime = stoi(tokens[4]);

            routes.push_back(Route(id, origin, destination, keyStops, estimatedTravelTime));
        }
        catch (const exception &e)
        {
            logError(filename, lineNumber, "Parsing error: " + string(e.what()));
        }
    }

    file.close();
    cout << "Loaded " << routes.size() << " routes from " << filename << endl;
    return routes;
}

vector<Schedule> DataLoader::loadSchedules(const string &filename)
{
    vector<Schedule> schedules;
    ifstream file(filename);

    if (!file.is_open())
    {
        cerr << "Error: Could not open file " << filename << endl;
        return schedules;
    }

    string line;
    int lineNumber = 0;

    while (getline(file, line))
    {
        lineNumber++;

        if (line.empty())
        {
            continue;
        }

        vector<string> tokens = splitCSV(line);

        if (tokens.size() != 7)
        {
            logError(filename, lineNumber, "Expected 7 fields, got " + to_string(tokens.size()));
            continue;
        }

        string id = tokens[0];
        string routeId = tokens[1];
        string busId = tokens[2];
        string driverId = tokens[3];
        string date = tokens[4];
        string departureTime = tokens[5];
        string arrivalTime = tokens[6];

        schedules.push_back(Schedule(id, routeId, busId, driverId, date, departureTime, arrivalTime));
    }

    file.close();
    cout << "Loaded " << schedules.size() << " schedules from " << filename << endl;
    return schedules;
}

vector<User> DataLoader::loadCredentials(const string &filename)
{
    vector<User> users;
    ifstream file(filename);

    if (!file.is_open())
    {
        cerr << "Error: Could not open file " << filename << endl;
        return users;
    }

    string line;
    int lineNumber = 0;

    while (getline(file, line))
    {
        lineNumber++;

        if (line.empty())
        {
            continue;
        }

        vector<string> tokens = splitCSV(line);

        if (tokens.size() != 3)
        {
            logError(filename, lineNumber, "Expected 3 fields, got " + to_string(tokens.size()));
            continue;
        }

        string username = tokens[0];
        string password = tokens[1];
        UserRole role = User::stringToRole(tokens[2]);

        users.push_back(User(username, password, role));
    }

    file.close();
    cout << "Loaded " << users.size() << " user credentials from " << filename << endl;
    return users;
}
