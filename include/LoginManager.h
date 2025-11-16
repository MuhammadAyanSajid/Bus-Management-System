#ifndef LOGINMANAGER_H
#define LOGINMANAGER_H

#include <string>
#include <vector>
#include "User.h"

using std::string;
using std::vector;

class LoginManager
{
private:
    vector<User> &users;
    User *currentUser;

public:
    // Constructor
    LoginManager(vector<User> &userList);

    // Authentication
    bool authenticate(const string &username, const string &password, UserRole expectedRole);

    // Get current logged-in user
    User *getCurrentUser() const;

    // Logout
    void logout();

    // Check if a user is logged in
    bool isLoggedIn() const;

    // Display login screen
    void displayLoginScreen(const string &roleType) const;

    // Find user by username
    User *findUser(const string &username);
};

#endif // LOGINMANAGER_H
