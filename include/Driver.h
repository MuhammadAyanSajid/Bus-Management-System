#ifndef DRIVER_H
#define DRIVER_H

#include <string>
#include <iostream>

using std::string;

class Driver
{
private:
    string id;
    string name;
    string contactInfo;
    string licenseDetails;

public:
    Driver();
    Driver(const string &id, const string &name,
           const string &contactInfo, const string &licenseDetails);

    string getId() const;
    string getName() const;
    string getContactInfo() const;
    string getLicenseDetails() const;

    void setId(const string &id);
    void setName(const string &name);
    void setContactInfo(const string &contactInfo);
    void setLicenseDetails(const string &licenseDetails);

    void display() const;
};

#endif