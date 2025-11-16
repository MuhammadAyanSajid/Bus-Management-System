#ifndef DATALOADER_H
#define DATALOADER_H

#include <string>
#include <vector>
#include "Bus.h"
#include "Driver.h"
#include "Route.h"
#include "Schedule.h"
#include "User.h"

class DataLoader
{
public:
    static std::vector<Bus> loadBuses(const std::string &filename);
    static std::vector<Driver> loadDrivers(const std::string &filename);
    static std::vector<Route> loadRoutes(const std::string &filename);
    static std::vector<Schedule> loadSchedules(const std::string &filename);
    static std::vector<User> loadCredentials(const std::string &filename);

    static std::vector<std::string> splitCSV(const std::string &line, char delimiter = ',');

    static std::vector<std::string> parseKeyStops(const std::string &stopsStr);

private:
    static void logError(const std::string &filename, int lineNumber, const std::string &error);
};

#endif
