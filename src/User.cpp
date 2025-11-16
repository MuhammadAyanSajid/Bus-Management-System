#include "../include/User.h"
#include <iomanip>

using namespace std;

User::User() : username(""), password(""), role(UserRole::PASSENGER) {}
User::User(const string &username, const string &password, UserRole role)
    : username(username), password(password), role(role) {}

// Getters
string User::getUsername() const
{
    return username;
}

string User::getPassword() const
{
    return password;
}

UserRole User::getRole() const
{
    return role;
}

string User::getRoleString() const
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

void User::setUsername(const string &username)
{
    this->username = username;
}

void User::setPassword(const string &password)
{
    this->password = password;
}

void User::setRole(UserRole role)
{
    this->role = role;
}

bool User::authenticate(const string &inputUsername, const string &inputPassword) const
{
    return (username == inputUsername && password == inputPassword);
}

void User::display() const
{
    cout << left
         << setw(15) << username
         << setw(15) << "********"
         << setw(15) << getRoleString()
         << endl;
}

UserRole User::stringToRole(const string &roleStr)
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
