#ifndef USER_H
#define USER_H
#include <iostream>
using namespace std;
#include "src/headers/PasswordMangement/Password.h"
//user classs
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

    Password *GetPasswordPtr()
    {
        return &password;
    }

    // Mutators
    void SetName(string name)
    {
        password.SetUsername(name);
    }

    void SetPassword(string userPassword)
    {
        password.SetPassword(userPassword);
    }

    int generatetandomNumber(int min, int max)
    {
        return password.GenerateRandomNumber(min, max);
    }


    string GenerateTempPassword(){
        return password.GenerateTemporayPassword();
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