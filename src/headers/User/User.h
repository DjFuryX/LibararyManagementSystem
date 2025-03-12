#ifndef USER_H
#define USER_H
#include <iostream>
using namespace std;
#include "src/headers/PasswordMangement/LoginInfo.h"
//user classs
class User
{
private:
    LoginInfo loginInfo;

public:
    User(/* args */) : loginInfo() { // initialize (composition) of loginInfo using its default constructor

                       };

    User(string username) : loginInfo(username) { // call primary constructor to create username

                            };

    User(string username, string LoginInfo) : loginInfo(username, LoginInfo) // primary constructor for Admin only
    {
    }

    // Accessors
    LoginInfo *GetLoginInfo()
    {
        return &loginInfo;
    }

    // Mutators
    void SetLoginInfo(LoginInfo userPassword)
    {
       loginInfo = userPassword;
    }

   virtual bool Login(string username, string userpassword)
    { // Login Function

        if (username == loginInfo.GetUsername() && userpassword == loginInfo.GetPassword())
        {
            return true;
        }

        return false;
    }

    ~User() {

    };
};

#endif