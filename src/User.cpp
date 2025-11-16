#include "../include/User.h"
#include <iomanip>

User::User() : username(""), password(""), role(UserRole::PASSENGER) {}
User::User(const std::string &username, const std::string &password, UserRole role)
    : username(username), password(password), role(role) {}

// Getters
std::string User::getUsername() const
{
    return username;
}

std::string User::getPassword() const
{
    return password;
}

UserRole User::getRole() const
{
    return role;
}

std::string User::getRoleString() const
{
    switch (role)
    {
    case UserRole::ADMIN:
        return "Admin";
    case UserRole::DRIVER:
        return "Driver";
    case UserRole::PASSENGER:
        return "Passenger";
    default:
        return "Unknown";
    }
}

void User::setUsername(const std::string &username)
{
    this->username = username;
}

void User::setPassword(const std::string &password)
{
    this->password = password;
}

void User::setRole(UserRole role)
{
    this->role = role;
}

bool User::authenticate(const std::string &inputUsername, const std::string &inputPassword) const
{
    return (username == inputUsername && password == inputPassword);
}

void User::display() const
{
    std::cout << std::left
              << std::setw(15) << username
              << std::setw(15) << "********"
              << std::setw(15) << getRoleString()
              << std::endl;
}

UserRole User::stringToRole(const std::string &roleStr)
{
    if (roleStr == "Admin" || roleStr == "ADMIN" || roleStr == "admin")
    {
        return UserRole::ADMIN;
    }
    else if (roleStr == "Driver" || roleStr == "DRIVER" || roleStr == "driver")
    {
        return UserRole::DRIVER;
    }
    else
    {
        return UserRole::PASSENGER;
    }
}
