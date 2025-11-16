#include "../include/LoginManager.h"
#include <iostream>
#include <iomanip>

using namespace std;

LoginManager::LoginManager(vector<User> &userList)
    : users(userList), currentUser(nullptr) {}

void LoginManager::displayLoginScreen(const string &roleType) const
{
    cout << "\n";
    cout << "========================================" << endl;
    cout << "   " << roleType << " LOGIN" << endl;
    cout << "========================================" << endl;
}

bool LoginManager::authenticate(const string &username, const string &password, UserRole expectedRole)
{
    for (auto &user : users)
    {
        if (user.getUsername() == username)
        {
            if (user.getPassword() == password)
            {
                if (user.getRole() == expectedRole)
                {
                    currentUser = &user;
                    cout << "\nLogin successful! Welcome, " << username << "." << endl;
                    return true;
                }
                else
                {
                    cout << "\nError: You don't have " << user.getRoleString() << " privileges." << endl;
                    return false;
                }
            }
            else
            {
                cout << "\nError: Incorrect password." << endl;
                return false;
            }
        }
    }
    cout << "\nError: User not found." << endl;
    return false;
}

User *LoginManager::getCurrentUser() const
{
    return currentUser;
}

void LoginManager::logout()
{
    if (currentUser)
    {
        cout << "\nLogging out " << currentUser->getUsername() << "..." << endl;
        currentUser = nullptr;
        cout << "Logged out successfully." << endl;
    }
}

bool LoginManager::isLoggedIn() const
{
    return currentUser != nullptr;
}

User *LoginManager::findUser(const string &username)
{
    for (auto &user : users)
    {
        if (user.getUsername() == username)
        {
            return &user;
        }
    }
    return nullptr;
}
