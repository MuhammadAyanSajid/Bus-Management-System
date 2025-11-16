#ifndef BUS_H
#define BUS_H

#include <string>
#include <iostream>

class Bus
{
private:
    std::string id;
    int capacity;
    std::string model;
    std::string status;

public:
    Bus();
    Bus(const std::string &id, int capacity, const std::string &model, const std::string &status);

    std::string getId() const;
    int getCapacity() const;
    std::string getModel() const;
    std::string getStatus() const;

    void setId(const std::string &id);
    void setCapacity(int capacity);
    void setModel(const std::string &model);
    void setStatus(const std::string &status);

    void display() const;
};

#endif