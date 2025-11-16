#ifndef USER_H
#define USER_H

#include <string>
#include <iostream>

using std::string;

enum class UserRole
{
    ADMIN,
    DRIVER,
    PASSENGER
};

class User
{
private:
    string username;
    string password;
    UserRole role;

public:
    User();
    User(const string &username, const string &password, UserRole role);

    string getUsername() const;
    string getPassword() const;
    UserRole getRole() const;
    string getRoleString() const;

    void setUsername(const string &username);
    void setPassword(const string &password);
    void setRole(UserRole role);

    bool authenticate(const string &inputUsername, const string &inputPassword) const;

    void display() const;

    static UserRole stringToRole(const string &roleStr);
};

#endif