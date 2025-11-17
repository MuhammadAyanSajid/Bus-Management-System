#ifndef SCHEDULEMANAGER_H
#define SCHEDULEMANAGER_H

#include <string>
#include <vector>
#include "Schedule.h"
#include "Route.h"
#include "Bus.h"
#include "Driver.h"

using std::string;
using std::vector;

class ScheduleManager
{
private:
    vector<Schedule> &schedules;
    vector<Route> &routes;
    vector<Bus> &buses;
    vector<Driver> &drivers;
    string dataFile;

public:
    ScheduleManager(vector<Schedule> &scheduleList,
                    vector<Route> &routeList,
                    vector<Bus> &busList,
                    vector<Driver> &driverList,
                    const string &filename);

    bool addSchedule(const Schedule &newSchedule);
    bool updateSchedule(const string &scheduleId, const Schedule &updatedSchedule);
    bool removeSchedule(const string &scheduleId);

    Schedule *findSchedule(const string &scheduleId);
    bool scheduleExists(const string &scheduleId) const;
    vector<Schedule> getSchedulesByDriver(const string &driverId) const;
    vector<Schedule> getSchedulesByDate(const string &date) const;
    vector<Schedule> getSchedulesByBus(const string &busId) const;

    bool saveToFile();

    void displayAllSchedules() const;
    void displaySchedule(const Schedule &schedule) const;

    bool validateSchedule(const Schedule &schedule) const;
    bool hasValidReferences(const Schedule &schedule) const;
    bool hasBusOverlap(const Schedule &schedule, const string &excludeScheduleId = "") const;
    bool hasDriverOverlap(const Schedule &schedule, const string &excludeScheduleId = "") const;
};

#endif 