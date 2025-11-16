#ifndef BUS_H
#define BUS_H

#include <string>
#include <iostream>

using std::string;

class Bus
{
private:
    string id;
    int capacity;
    string model;
    string status;

public:
    Bus();
    Bus(const string &id, int capacity, const string &model, const string &status);

    string getId() const;
    int getCapacity() const;
    string getModel() const;
    string getStatus() const;

    void setId(const string &id);
    void setCapacity(int capacity);
    void setModel(const string &model);
    void setStatus(const string &status);

    void display() const;
};

#endif