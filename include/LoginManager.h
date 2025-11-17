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
    LoginManager(vector<User> &userList);

    bool authenticate(const string &username, const string &password, UserRole expectedRole);

    User *getCurrentUser() const;

    void logout();

    bool isLoggedIn() const;

    void displayLoginScreen(const string &roleType) const;

    User *findUser(const string &username);
};

#endif
