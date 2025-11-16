#include "../include/ScheduleManager.h"
#include "../include/DataSaver.h"
#include "../include/DisplayManager.h"
#include <iostream>
#include <algorithm>

ScheduleManager::ScheduleManager(std::vector<Schedule> &scheduleList,
                                 std::vector<Route> &routeList,
                                 std::vector<Bus> &busList,
                                 std::vector<Driver> &driverList,
                                 const std::string &filename)
    : schedules(scheduleList), routes(routeList), buses(busList), drivers(driverList), dataFile(filename) {}

bool ScheduleManager::hasValidReferences(const Schedule &schedule) const
{
    bool routeExists = std::any_of(routes.begin(), routes.end(),
                                   [&schedule](const Route &r)
                                   { return r.getId() == schedule.getRouteId(); });

    if (!routeExists)
    {
        std::cout << "Error: Route ID " << schedule.getRouteId() << " not found." << std::endl;
        return false;
    }

    bool busExists = std::any_of(buses.begin(), buses.end(),
                                 [&schedule](const Bus &b)
                                 { return b.getId() == schedule.getBusId(); });

    if (!busExists)
    {
        std::cout << "Error: Bus ID " << schedule.getBusId() << " not found." << std::endl;
        return false;
    }

    bool driverExists = std::any_of(drivers.begin(), drivers.end(),
                                    [&schedule](const Driver &d)
                                    { return d.getId() == schedule.getDriverId(); });

    if (!driverExists)
    {
        std::cout << "Error: Driver ID " << schedule.getDriverId() << " not found." << std::endl;
        return false;
    }

    return true;
}

bool ScheduleManager::hasBusOverlap(const Schedule &newSchedule, const std::string &excludeScheduleId) const
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
                std::cout << "Error: Bus " << newSchedule.getBusId()
                          << " is already scheduled on " << newSchedule.getDate()
                          << " from " << existingSchedule.getDepartureTime()
                          << " to " << existingSchedule.getArrivalTime() << std::endl;
                return true;
            }
        }
    }
    return false;
}

bool ScheduleManager::hasDriverOverlap(const Schedule &newSchedule, const std::string &excludeScheduleId) const
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
                std::cout << "Error: Driver " << newSchedule.getDriverId()
                          << " is already assigned on " << newSchedule.getDate()
                          << " from " << existingSchedule.getDepartureTime()
                          << " to " << existingSchedule.getArrivalTime() << std::endl;
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
        std::cout << "Error: Schedule ID cannot be empty." << std::endl;
        return false;
    }

    if (schedule.getRouteId().empty() || schedule.getBusId().empty() ||
        schedule.getDriverId().empty())
    {
        std::cout << "Error: Route, Bus, and Driver IDs must be provided." << std::endl;
        return false;
    }

    if (schedule.getDate().empty())
    {
        std::cout << "Error: Date must be provided." << std::endl;
        return false;
    }

    if (schedule.getDepartureTime().empty() || schedule.getArrivalTime().empty())
    {
        std::cout << "Error: Departure and arrival times must be provided." << std::endl;
        return false;
    }

    if (schedule.getDepartureTime() >= schedule.getArrivalTime())
    {
        std::cout << "Error: Departure time must be before arrival time." << std::endl;
        return false;
    }

    return true;
}

bool ScheduleManager::scheduleExists(const std::string &scheduleId) const
{
    return std::any_of(schedules.begin(), schedules.end(),
                       [&scheduleId](const Schedule &s)
                       { return s.getId() == scheduleId; });
}

Schedule *ScheduleManager::findSchedule(const std::string &scheduleId)
{
    auto it = std::find_if(schedules.begin(), schedules.end(),
                           [&scheduleId](const Schedule &s)
                           { return s.getId() == scheduleId; });

    if (it != schedules.end())
    {
        return &(*it);
    }
    return nullptr;
}

std::vector<Schedule> ScheduleManager::getSchedulesByDriver(const std::string &driverId) const
{
    std::vector<Schedule> result;
    for (const auto &schedule : schedules)
    {
        if (schedule.getDriverId() == driverId)
        {
            result.push_back(schedule);
        }
    }
    return result;
}

std::vector<Schedule> ScheduleManager::getSchedulesByDate(const std::string &date) const
{
    std::vector<Schedule> result;
    for (const auto &schedule : schedules)
    {
        if (schedule.getDate() == date)
        {
            result.push_back(schedule);
        }
    }
    return result;
}

std::vector<Schedule> ScheduleManager::getSchedulesByBus(const std::string &busId) const
{
    std::vector<Schedule> result;
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
        std::cout << "Error: Schedule with ID " << newSchedule.getId() << " already exists." << std::endl;
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
    std::cout << "Schedule " << newSchedule.getId() << " added successfully." << std::endl;

    return saveToFile();
}

bool ScheduleManager::updateSchedule(const std::string &scheduleId, const Schedule &updatedSchedule)
{
    Schedule *schedule = findSchedule(scheduleId);
    if (!schedule)
    {
        std::cout << "Error: Schedule with ID " << scheduleId << " not found." << std::endl;
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
    std::cout << "Schedule " << scheduleId << " updated successfully." << std::endl;

    return saveToFile();
}

bool ScheduleManager::removeSchedule(const std::string &scheduleId)
{
    auto it = std::find_if(schedules.begin(), schedules.end(),
                           [&scheduleId](const Schedule &s)
                           { return s.getId() == scheduleId; });

    if (it == schedules.end())
    {
        std::cout << "Error: Schedule with ID " << scheduleId << " not found." << std::endl;
        return false;
    }

    schedules.erase(it);
    std::cout << "Schedule " << scheduleId << " removed successfully." << std::endl;

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
