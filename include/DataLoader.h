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
    // Load functions for each entity type
    static std::vector<Bus> loadBuses(const std::string &filename);
    static std::vector<Driver> loadDrivers(const std::string &filename);
    static std::vector<Route> loadRoutes(const std::string &filename);
    static std::vector<Schedule> loadSchedules(const std::string &filename);
    static std::vector<User> loadCredentials(const std::string &filename);

    // Helper function to split CSV line
    static std::vector<std::string> splitCSV(const std::string &line, char delimiter = ',');

    // Helper function to parse key stops (pipe-separated within CSV)
    static std::vector<std::string> parseKeyStops(const std::string &stopsStr);

private:
    // Private helper for error logging
    static void logError(const std::string &filename, int lineNumber, const std::string &error);
};

#endif // DATALOADER_H
