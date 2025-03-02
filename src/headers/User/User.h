
#ifndef USER_H
#define USER_H
#include "src/headers/PasswordMangement/Password.h"

#include <iostream>
using namespace std;

// abstract user classs
class User
{
private:
    Password password;

public:
    User(/* args */) : password() { // initialize (composition) of password using its default constructor

                       };

    User(string username) : password(username) { // call primary constructor to create username

                            };

    User(string username, string Password) : password(username, Password) // primary constructor for Admin only
    {
    }

    // Accessors
    string GetName()
    {
        return password.GetUsername();
    }

    string GetPassword()
    {
        return password.GetPassword();
    }

    // Mutators
    void SetName(string name)
    {
        password.SetUsername(name);
    }

    int generatetandomNumber(int min, int max)
    {
        return password.GenerateRandomNumber(min, max);
    }

    bool Login(string username, string password)
    { // Login Function to determine if user is a admin or Patron

        if (username == GetName() && password == GetPassword())
        {
            return true;
        }

        return false;
    }

    ~User() {

    };
};

#endif