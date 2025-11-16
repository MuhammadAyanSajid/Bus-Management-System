#ifndef DATASAVER_H
#define DATASAVER_H

#include <string>
#include <vector>
#include "Bus.h"
#include "Driver.h"
#include "Route.h"
#include "Schedule.h"
#include "User.h"

using std::string;
using std::vector;

class DataSaver
{
public:
    // Save functions for each entity type
    static bool saveBuses(const string &filename, const vector<Bus> &buses);
    static bool saveDrivers(const string &filename, const vector<Driver> &drivers);
    static bool saveRoutes(const string &filename, const vector<Route> &routes);
    static bool saveSchedules(const string &filename, const vector<Schedule> &schedules);
    static bool saveCredentials(const string &filename, const vector<User> &users);
};

#endif // DATASAVER_H
