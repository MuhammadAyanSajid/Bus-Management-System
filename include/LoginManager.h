#ifndef LOGINMANAGER_H
#define LOGINMANAGER_H

#include <string>
#include <vector>
#include "User.h"

class LoginManager
{
private:
    std::vector<User> &users;
    User *currentUser;

public:
    // Constructor
    LoginManager(std::vector<User> &userList);

    // Authentication
    bool authenticate(const std::string &username, const std::string &password, UserRole expectedRole);

    // Get current logged-in user
    User *getCurrentUser() const;

    // Logout
    void logout();

    // Check if a user is logged in
    bool isLoggedIn() const;

    // Display login screen
    void displayLoginScreen(const std::string &roleType) const;

    // Find user by username
    User *findUser(const std::string &username);
};

#endif // LOGINMANAGER_H
