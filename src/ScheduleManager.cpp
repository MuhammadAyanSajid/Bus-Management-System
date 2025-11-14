#include "../include/ScheduleManager.h"
#include "../include/DataSaver.h"
#include "../include/DisplayManager.h"
#include <iostream>
#include <algorithm>

// Constructor
ScheduleManager::ScheduleManager(std::vector<Schedule> &scheduleList,
                                 std::vector<Route> &routeList,
                                 std::vector<Bus> &busList,
                                 std::vector<Driver> &driverList,
                                 const std::string &filename)
    : schedules(scheduleList), routes(routeList), buses(busList), drivers(driverList), dataFile(filename) {}

// Check if valid references exist
bool ScheduleManager::hasValidReferences(const Schedule &schedule) const
{
    // Check if route exists
    bool routeExists = std::any_of(routes.begin(), routes.end(),
                                   [&schedule](const Route &r)
                                   { return r.getId() == schedule.getRouteId(); });

    if (!routeExists)
    {
        std::cout << "Error: Route ID " << schedule.getRouteId() << " not found." << std::endl;
        return false;
    }

    // Check if bus exists
    bool busExists = std::any_of(buses.begin(), buses.end(),
                                 [&schedule](const Bus &b)
                                 { return b.getId() == schedule.getBusId(); });

    if (!busExists)
    {
        std::cout << "Error: Bus ID " << schedule.getBusId() << " not found." << std::endl;
        return false;
    }

    // Check if driver exists
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

// Check for bus overlap
bool ScheduleManager::hasBusOverlap(const Schedule &newSchedule, const std::string &excludeScheduleId) const
{
    for (const auto &existingSchedule : schedules)
    {
        // Skip the schedule being updated
        if (existingSchedule.getId() == excludeScheduleId)
        {
            continue;
        }

        // Check if same bus and same date
        if (existingSchedule.getBusId() == newSchedule.getBusId() &&
            existingSchedule.getDate() == newSchedule.getDate())
        {

            // Check for time overlap
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

// Check for driver overlap
bool ScheduleManager::hasDriverOverlap(const Schedule &newSchedule, const std::string &excludeScheduleId) const
{
    for (const auto &existingSchedule : schedules)
    {
        // Skip the schedule being updated
        if (existingSchedule.getId() == excludeScheduleId)
        {
            continue;
        }

        // Check if same driver and same date
        if (existingSchedule.getDriverId() == newSchedule.getDriverId() &&
            existingSchedule.getDate() == newSchedule.getDate())
        {

            // Check for time overlap
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

// Validate schedule
bool ScheduleManager::validateSchedule(const Schedule &schedule) const
{
    // Check if ID is not empty
    if (schedule.getId().empty())
    {
        std::cout << "Error: Schedule ID cannot be empty." << std::endl;
        return false;
    }

    // Check if all IDs are provided
    if (schedule.getRouteId().empty() || schedule.getBusId().empty() ||
        schedule.getDriverId().empty())
    {
        std::cout << "Error: Route, Bus, and Driver IDs must be provided." << std::endl;
        return false;
    }

    // Check if date is provided
    if (schedule.getDate().empty())
    {
        std::cout << "Error: Date must be provided." << std::endl;
        return false;
    }

    // Check if times are provided
    if (schedule.getDepartureTime().empty() || schedule.getArrivalTime().empty())
    {
        std::cout << "Error: Departure and arrival times must be provided." << std::endl;
        return false;
    }

    // Check if departure is before arrival
    if (schedule.getDepartureTime() >= schedule.getArrivalTime())
    {
        std::cout << "Error: Departure time must be before arrival time." << std::endl;
        return false;
    }

    return true;
}

// Check if schedule exists
bool ScheduleManager::scheduleExists(const std::string &scheduleId) const
{
    return std::any_of(schedules.begin(), schedules.end(),
                       [&scheduleId](const Schedule &s)
                       { return s.getId() == scheduleId; });
}

// Find schedule by ID
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

// Get schedules by driver
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

// Get schedules by date
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

// Get schedules by bus
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

// Add new schedule
bool ScheduleManager::addSchedule(const Schedule &newSchedule)
{
    // Validate schedule
    if (!validateSchedule(newSchedule))
    {
        return false;
    }

    // Check if schedule ID already exists
    if (scheduleExists(newSchedule.getId()))
    {
        std::cout << "Error: Schedule with ID " << newSchedule.getId() << " already exists." << std::endl;
        return false;
    }

    // Check valid references
    if (!hasValidReferences(newSchedule))
    {
        return false;
    }

    // Check for bus overlap
    if (hasBusOverlap(newSchedule))
    {
        return false;
    }

    // Check for driver overlap
    if (hasDriverOverlap(newSchedule))
    {
        return false;
    }

    // Add schedule
    schedules.push_back(newSchedule);
    std::cout << "Schedule " << newSchedule.getId() << " added successfully." << std::endl;

    // Save to file
    return saveToFile();
}

// Update existing schedule
bool ScheduleManager::updateSchedule(const std::string &scheduleId, const Schedule &updatedSchedule)
{
    // Find schedule
    Schedule *schedule = findSchedule(scheduleId);
    if (!schedule)
    {
        std::cout << "Error: Schedule with ID " << scheduleId << " not found." << std::endl;
        return false;
    }

    // Validate updated schedule
    if (!validateSchedule(updatedSchedule))
    {
        return false;
    }

    // Check valid references
    if (!hasValidReferences(updatedSchedule))
    {
        return false;
    }

    // Check for bus overlap (excluding current schedule)
    if (hasBusOverlap(updatedSchedule, scheduleId))
    {
        return false;
    }

    // Check for driver overlap (excluding current schedule)
    if (hasDriverOverlap(updatedSchedule, scheduleId))
    {
        return false;
    }

    // Update schedule
    *schedule = updatedSchedule;
    std::cout << "Schedule " << scheduleId << " updated successfully." << std::endl;

    // Save to file
    return saveToFile();
}

// Remove schedule
bool ScheduleManager::removeSchedule(const std::string &scheduleId)
{
    // Find schedule
    auto it = std::find_if(schedules.begin(), schedules.end(),
                           [&scheduleId](const Schedule &s)
                           { return s.getId() == scheduleId; });

    if (it == schedules.end())
    {
        std::cout << "Error: Schedule with ID " << scheduleId << " not found." << std::endl;
        return false;
    }

    // Remove schedule
    schedules.erase(it);
    std::cout << "Schedule " << scheduleId << " removed successfully." << std::endl;

    // Save to file
    return saveToFile();
}

// Save to file
bool ScheduleManager::saveToFile()
{
    return DataSaver::saveSchedules(dataFile, schedules);
}

// Display all schedules
void ScheduleManager::displayAllSchedules() const
{
    DisplayManager::displaySchedules(schedules);
}

// Display single schedule
void ScheduleManager::displaySchedule(const Schedule &schedule) const
{
    DisplayManager::displaySchedule(schedule);
}
