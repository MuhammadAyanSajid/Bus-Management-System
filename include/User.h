#ifndef USER_H
#define USER_H

#include <string>
#include <iostream>

enum class UserRole {
    ADMIN,
    DRIVER,
    PASSENGER
};

class User {
private:
    std::string username;
    std::string password;
    UserRole role;

public:
    // Constructors
    User();
    User(const std::string& username, const std::string& password, UserRole role);
    
    // Getters
    std::string getUsername() const;
    std::string getPassword() const;
    UserRole getRole() const;
    std::string getRoleString() const;
    
    // Setters
    void setUsername(const std::string& username);
    void setPassword(const std::string& password);
    void setRole(UserRole role);
    
    // Authentication
    bool authenticate(const std::string& inputUsername, const std::string& inputPassword) const;
    
    // Display function
    void display() const;
    
    // Static helper to convert string to UserRole
    static UserRole stringToRole(const std::string& roleStr);
};

#endif // USER_H