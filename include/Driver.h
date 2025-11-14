#ifndef DRIVER_H
#define DRIVER_H

#include <string>
#include <iostream>

class Driver {
private:
    std::string id;
    std::string name;
    std::string contactInfo;
    std::string licenseDetails;

public:
    // Constructors
    Driver();
    Driver(const std::string& id, const std::string& name, 
           const std::string& contactInfo, const std::string& licenseDetails);
    
    // Getters
    std::string getId() const;
    std::string getName() const;
    std::string getContactInfo() const;
    std::string getLicenseDetails() const;
    
    // Setters
    void setId(const std::string& id);
    void setName(const std::string& name);
    void setContactInfo(const std::string& contactInfo);
    void setLicenseDetails(const std::string& licenseDetails);
    
    // Display function
    void display() const;
};

#endif // DRIVER_H