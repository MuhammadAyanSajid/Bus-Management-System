#include "../include/Bus.h"
#include <iomanip>

using namespace std;

Bus::Bus() : id(""), capacity(0), model(""), status("Inactive") {}
Bus::Bus(const string &id, int capacity, const string &model, const string &status)
    : id(id), capacity(capacity), model(model), status(status) {}

// Getters
string Bus::getId() const
{
    return id;
}

int Bus::getCapacity() const
{
    return capacity;
}

string Bus::getModel() const
{
    return model;
}

string Bus::getStatus() const
{
    return status;
}

void Bus::setId(const string &id)
{
    this->id = id;
}

void Bus::setCapacity(int capacity)
{
    this->capacity = capacity;
}

void Bus::setModel(const string &model)
{
    this->model = model;
}

void Bus::setStatus(const string &status)
{
    this->status = status;
}

void Bus::display() const
{
    cout << left
         << setw(10) << id
         << setw(12) << capacity
         << setw(15) << model
         << setw(15) << status
         << endl;
}
