#include "../include/Bus.h"
#include <iomanip>

Bus::Bus() : id(""), capacity(0), model(""), status("Inactive") {}
Bus::Bus(const std::string &id, int capacity, const std::string &model, const std::string &status)
    : id(id), capacity(capacity), model(model), status(status) {}

// Getters
std::string Bus::getId() const
{
    return id;
}

int Bus::getCapacity() const
{
    return capacity;
}

std::string Bus::getModel() const
{
    return model;
}

std::string Bus::getStatus() const
{
    return status;
}

void Bus::setId(const std::string &id)
{
    this->id = id;
}

void Bus::setCapacity(int capacity)
{
    this->capacity = capacity;
}

void Bus::setModel(const std::string &model)
{
    this->model = model;
}

void Bus::setStatus(const std::string &status)
{
    this->status = status;
}

void Bus::display() const
{
    std::cout << std::left
              << std::setw(10) << id
              << std::setw(12) << capacity
              << std::setw(15) << model
              << std::setw(15) << status
              << std::endl;
}
