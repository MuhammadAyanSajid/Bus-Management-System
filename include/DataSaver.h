#ifndef DATASAVER_H
#define DATASAVER_H

#include <string>
#include <vector>
#include "Bus.h"
#include "Driver.h"
#include "Route.h"
#include "Schedule.h"
#include "User.h"

class DataSaver
{
public:
    // Save functions for each entity type
    static bool saveBuses(const std::string &filename, const std::vector<Bus> &buses);
    static bool saveDrivers(const std::string &filename, const std::vector<Driver> &drivers);
    static bool saveRoutes(const std::string &filename, const std::vector<Route> &routes);
    static bool saveSchedules(const std::string &filename, const std::vector<Schedule> &schedules);
    static bool saveCredentials(const std::string &filename, const std::vector<User> &users);
};

#endif // DATASAVER_H
