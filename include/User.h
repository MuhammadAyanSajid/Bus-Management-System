#ifndef USER_H
#define USER_H

#include <string>
#include <iostream>

enum class UserRole
{
    ADMIN,
    DRIVER,
    PASSENGER
};

class User
{
private:
    std::string username;
    std::string password;
    UserRole role;

public:
    User();
    User(const std::string &username, const std::string &password, UserRole role);

    std::string getUsername() const;
    std::string getPassword() const;
    UserRole getRole() const;
    std::string getRoleString() const;

    void setUsername(const std::string &username);
    void setPassword(const std::string &password);
    void setRole(UserRole role);

    bool authenticate(const std::string &inputUsername, const std::string &inputPassword) const;

    void display() const;

    static UserRole stringToRole(const std::string &roleStr);
};

#endif