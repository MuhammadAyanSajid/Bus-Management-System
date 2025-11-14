#ifndef SCHEDULEMANAGER_H
#define SCHEDULEMANAGER_H

#include <string>
#include <vector>
#include "Schedule.h"
#include "Route.h"
#include "Bus.h"
#include "Driver.h"

class ScheduleManager
{
private:
    std::vector<Schedule> &schedules;
    std::vector<Route> &routes;
    std::vector<Bus> &buses;
    std::vector<Driver> &drivers;
    std::string dataFile;

public:
    // Constructor
    ScheduleManager(std::vector<Schedule> &scheduleList,
                    std::vector<Route> &routeList,
                    std::vector<Bus> &busList,
                    std::vector<Driver> &driverList,
                    const std::string &filename);

    // CRUD operations
    bool addSchedule(const Schedule &newSchedule);
    bool updateSchedule(const std::string &scheduleId, const Schedule &updatedSchedule);
    bool removeSchedule(const std::string &scheduleId);

    // Query operations
    Schedule *findSchedule(const std::string &scheduleId);
    bool scheduleExists(const std::string &scheduleId) const;
    std::vector<Schedule> getSchedulesByDriver(const std::string &driverId) const;
    std::vector<Schedule> getSchedulesByDate(const std::string &date) const;
    std::vector<Schedule> getSchedulesByBus(const std::string &busId) const;

    // Save to file
    bool saveToFile();

    // Display schedules
    void displayAllSchedules() const;
    void displaySchedule(const Schedule &schedule) const;

    // Validation and business logic
    bool validateSchedule(const Schedule &schedule) const;
    bool hasValidReferences(const Schedule &schedule) const;
    bool hasBusOverlap(const Schedule &schedule, const std::string &excludeScheduleId = "") const;
    bool hasDriverOverlap(const Schedule &schedule, const std::string &excludeScheduleId = "") const;
};

#endif // SCHEDULEMANAGER_H
