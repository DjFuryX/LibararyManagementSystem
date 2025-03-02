
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

    string GetName()
    {
        return password.GetUsername();
    }

    void SetName(string name)
    {
        password.SetUsername(name);
    }

    int generatetandomNumber(int min,int max){
        return password.GenerateRandomNumber(min,max);
    }

    virtual void Login(){}; //login function

    ~User() {

    };
};

#endif