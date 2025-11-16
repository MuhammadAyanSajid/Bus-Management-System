#ifndef DATALOADER_H
#define DATALOADER_H

#include <string>
#include <vector>
#include "Bus.h"
#include "Driver.h"
#include "Route.h"
#include "Schedule.h"
#include "User.h"

using std::string;
using std::vector;

class DataLoader
{
public:
    static vector<Bus> loadBuses(const string &filename);
    static vector<Driver> loadDrivers(const string &filename);
    static vector<Route> loadRoutes(const string &filename);
    static vector<Schedule> loadSchedules(const string &filename);
    static vector<User> loadCredentials(const string &filename);

    static vector<string> splitCSV(const string &line, char delimiter = ',');

    static vector<string> parseKeyStops(const string &stopsStr);

private:
    static void logError(const string &filename, int lineNumber, const string &error);
};

#endif
