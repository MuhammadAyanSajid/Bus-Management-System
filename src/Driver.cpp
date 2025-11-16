#include "../include/Driver.h"
#include <iomanip>

using namespace std;

Driver::Driver() : id(""), name(""), contactInfo(""), licenseDetails("") {}
Driver::Driver(const string &id, const string &name,
               const string &contactInfo, const string &licenseDetails)
    : id(id), name(name), contactInfo(contactInfo), licenseDetails(licenseDetails) {}

string Driver::getId() const
{
    return id;
}

string Driver::getName() const
{
    return name;
}

string Driver::getContactInfo() const
{
    return contactInfo;
}

string Driver::getLicenseDetails() const
{
    return licenseDetails;
}

void Driver::setId(const string &id)
{
    this->id = id;
}

void Driver::setName(const string &name)
{
    this->name = name;
}

void Driver::setContactInfo(const string &contactInfo)
{
    this->contactInfo = contactInfo;
}

void Driver::setLicenseDetails(const string &licenseDetails)
{
    this->licenseDetails = licenseDetails;
}

void Driver::display() const
{
    cout << left
         << setw(10) << id
         << setw(20) << name
         << setw(15) << contactInfo
         << setw(15) << licenseDetails
         << endl;
}
