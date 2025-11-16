#include "../include/ScheduleManager.h"
#include "../include/DataSaver.h"
#include "../include/DisplayManager.h"
#include <iostream>
#include <algorithm>

using namespace std;

ScheduleManager::ScheduleManager(vector<Schedule> &scheduleList,
                                 vector<Route> &routeList,
                                 vector<Bus> &busList,
                                 vector<Driver> &driverList,
                                 const string &filename)
    : schedules(scheduleList), routes(routeList), buses(busList), drivers(driverList), dataFile(filename) {}

bool ScheduleManager::hasValidReferences(const Schedule &schedule) const
{
    bool routeExists = any_of(routes.begin(), routes.end(),
                              [&schedule](const Route &r)
                              { return r.getId() == schedule.getRouteId(); });

    if (!routeExists)
    {
        cout << "Error: Route ID " << schedule.getRouteId() << " not found." << endl;
        return false;
    }

    bool busExists = any_of(buses.begin(), buses.end(),
                            [&schedule](const Bus &b)
                            { return b.getId() == schedule.getBusId(); });

    if (!busExists)
    {
        cout << "Error: Bus ID " << schedule.getBusId() << " not found." << endl;
        return false;
    }

    bool driverExists = any_of(drivers.begin(), drivers.end(),
                               [&schedule](const Driver &d)
                               { return d.getId() == schedule.getDriverId(); });

    if (!driverExists)
    {
        cout << "Error: Driver ID " << schedule.getDriverId() << " not found." << endl;
        return false;
    }

    return true;
}

bool ScheduleManager::hasBusOverlap(const Schedule &newSchedule, const string &excludeScheduleId) const
{
    for (const auto &existingSchedule : schedules)
    {
        if (existingSchedule.getId() == excludeScheduleId)
        {
            continue;
        }

        if (existingSchedule.getBusId() == newSchedule.getBusId() &&
            existingSchedule.getDate() == newSchedule.getDate())
        {

            if (existingSchedule.hasTimeOverlap(newSchedule))
            {
                cout << "Error: Bus " << newSchedule.getBusId()
                     << " is already scheduled on " << newSchedule.getDate()
                     << " from " << existingSchedule.getDepartureTime()
                     << " to " << existingSchedule.getArrivalTime() << endl;
                return true;
            }
        }
    }
    return false;
}

bool ScheduleManager::hasDriverOverlap(const Schedule &newSchedule, const string &excludeScheduleId) const
{
    for (const auto &existingSchedule : schedules)
    {
        if (existingSchedule.getId() == excludeScheduleId)
        {
            continue;
        }

        if (existingSchedule.getDriverId() == newSchedule.getDriverId() &&
            existingSchedule.getDate() == newSchedule.getDate())
        {

            if (existingSchedule.hasTimeOverlap(newSchedule))
            {
                cout << "Error: Driver " << newSchedule.getDriverId()
                     << " is already assigned on " << newSchedule.getDate()
                     << " from " << existingSchedule.getDepartureTime()
                     << " to " << existingSchedule.getArrivalTime() << endl;
                return true;
            }
        }
    }
    return false;
}

bool ScheduleManager::validateSchedule(const Schedule &schedule) const
{
    if (schedule.getId().empty())
    {
        cout << "Error: Schedule ID cannot be empty." << endl;
        return false;
    }

    if (schedule.getRouteId().empty() || schedule.getBusId().empty() ||
        schedule.getDriverId().empty())
    {
        cout << "Error: Route, Bus, and Driver IDs must be provided." << endl;
        return false;
    }

    if (schedule.getDate().empty())
    {
        cout << "Error: Date must be provided." << endl;
        return false;
    }

    if (schedule.getDepartureTime().empty() || schedule.getArrivalTime().empty())
    {
        cout << "Error: Departure and arrival times must be provided." << endl;
        return false;
    }

    if (schedule.getDepartureTime() >= schedule.getArrivalTime())
    {
        cout << "Error: Departure time must be before arrival time." << endl;
        return false;
    }

    return true;
}

bool ScheduleManager::scheduleExists(const string &scheduleId) const
{
    return any_of(schedules.begin(), schedules.end(),
                  [&scheduleId](const Schedule &s)
                  { return s.getId() == scheduleId; });
}

Schedule *ScheduleManager::findSchedule(const string &scheduleId)
{
    auto it = find_if(schedules.begin(), schedules.end(),
                      [&scheduleId](const Schedule &s)
                      { return s.getId() == scheduleId; });

    if (it != schedules.end())
    {
        return &(*it);
    }
    return nullptr;
}

vector<Schedule> ScheduleManager::getSchedulesByDriver(const string &driverId) const
{
    vector<Schedule> result;
    for (const auto &schedule : schedules)
    {
        if (schedule.getDriverId() == driverId)
        {
            result.push_back(schedule);
        }
    }
    return result;
}

vector<Schedule> ScheduleManager::getSchedulesByDate(const string &date) const
{
    vector<Schedule> result;
    for (const auto &schedule : schedules)
    {
        if (schedule.getDate() == date)
        {
            result.push_back(schedule);
        }
    }
    return result;
}

vector<Schedule> ScheduleManager::getSchedulesByBus(const string &busId) const
{
    vector<Schedule> result;
    for (const auto &schedule : schedules)
    {
        if (schedule.getBusId() == busId)
        {
            result.push_back(schedule);
        }
    }
    return result;
}

bool ScheduleManager::addSchedule(const Schedule &newSchedule)
{
    if (!validateSchedule(newSchedule))
    {
        return false;
    }

    if (scheduleExists(newSchedule.getId()))
    {
        cout << "Error: Schedule with ID " << newSchedule.getId() << " already exists." << endl;
        return false;
    }

    if (!hasValidReferences(newSchedule))
    {
        return false;
    }

    if (hasBusOverlap(newSchedule))
    {
        return false;
    }

    if (hasDriverOverlap(newSchedule))
    {
        return false;
    }

    schedules.push_back(newSchedule);
    cout << "Schedule " << newSchedule.getId() << " added successfully." << endl;

    return saveToFile();
}

bool ScheduleManager::updateSchedule(const string &scheduleId, const Schedule &updatedSchedule)
{
    Schedule *schedule = findSchedule(scheduleId);
    if (!schedule)
    {
        cout << "Error: Schedule with ID " << scheduleId << " not found." << endl;
        return false;
    }

    if (!validateSchedule(updatedSchedule))
    {
        return false;
    }

    if (!hasValidReferences(updatedSchedule))
    {
        return false;
    }

    if (hasBusOverlap(updatedSchedule, scheduleId))
    {
        return false;
    }

    if (hasDriverOverlap(updatedSchedule, scheduleId))
    {
        return false;
    }

    *schedule = updatedSchedule;
    cout << "Schedule " << scheduleId << " updated successfully." << endl;

    return saveToFile();
}

bool ScheduleManager::removeSchedule(const string &scheduleId)
{
    auto it = find_if(schedules.begin(), schedules.end(),
                      [&scheduleId](const Schedule &s)
                      { return s.getId() == scheduleId; });

    if (it == schedules.end())
    {
        cout << "Error: Schedule with ID " << scheduleId << " not found." << endl;
        return false;
    }

    schedules.erase(it);
    cout << "Schedule " << scheduleId << " removed successfully." << endl;

    return saveToFile();
}

bool ScheduleManager::saveToFile()
{
    return DataSaver::saveSchedules(dataFile, schedules);
}

void ScheduleManager::displayAllSchedules() const
{
    DisplayManager::displaySchedules(schedules);
}

void ScheduleManager::displaySchedule(const Schedule &schedule) const
{
    DisplayManager::displaySchedule(schedule);
}
