#include "../include/Driver.h"
#include <iomanip>

Driver::Driver() : id(""), name(""), contactInfo(""), licenseDetails("") {}
Driver::Driver(const std::string &id, const std::string &name,
               const std::string &contactInfo, const std::string &licenseDetails)
    : id(id), name(name), contactInfo(contactInfo), licenseDetails(licenseDetails) {}

std::string Driver::getId() const
{
    return id;
}

std::string Driver::getName() const
{
    return name;
}

std::string Driver::getContactInfo() const
{
    return contactInfo;
}

std::string Driver::getLicenseDetails() const
{
    return licenseDetails;
}

void Driver::setId(const std::string &id)
{
    this->id = id;
}

void Driver::setName(const std::string &name)
{
    this->name = name;
}

void Driver::setContactInfo(const std::string &contactInfo)
{
    this->contactInfo = contactInfo;
}

void Driver::setLicenseDetails(const std::string &licenseDetails)
{
    this->licenseDetails = licenseDetails;
}

void Driver::display() const
{
    std::cout << std::left
              << std::setw(10) << id
              << std::setw(20) << name
              << std::setw(15) << contactInfo
              << std::setw(15) << licenseDetails
              << std::endl;
}
