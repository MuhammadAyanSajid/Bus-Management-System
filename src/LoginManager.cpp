#include "../include/LoginManager.h"
#include <iostream>
#include <iomanip>

LoginManager::LoginManager(std::vector<User> &userList)
    : users(userList), currentUser(nullptr) {}

void LoginManager::displayLoginScreen(const std::string &roleType) const
{
    std::cout << "\n";
    std::cout << "========================================" << std::endl;
    std::cout << "   " << roleType << " LOGIN" << std::endl;
    std::cout << "========================================" << std::endl;
}

bool LoginManager::authenticate(const std::string &username, const std::string &password, UserRole expectedRole)
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
                    std::cout << "\nLogin successful! Welcome, " << username << "." << std::endl;
                    return true;
                }
                else
                {
                    std::cout << "\nError: You don't have " << user.getRoleString() << " privileges." << std::endl;
                    return false;
                }
            }
            else
            {
                std::cout << "\nError: Incorrect password." << std::endl;
                return false;
            }
        }
    }
    std::cout << "\nError: User not found." << std::endl;
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
        std::cout << "\nLogging out " << currentUser->getUsername() << "..." << std::endl;
        currentUser = nullptr;
        std::cout << "Logged out successfully." << std::endl;
    }
}

bool LoginManager::isLoggedIn() const
{
    return currentUser != nullptr;
}

User *LoginManager::findUser(const std::string &username)
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
