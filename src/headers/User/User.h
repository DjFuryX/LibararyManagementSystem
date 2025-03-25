#ifndef USER_H
#define USER_H
#include <iostream>
using namespace std;
#include "src/headers/PasswordMangement/LoginInfo.h"
#include "src/headers/Books/BookQueue.h"
// user classs
class User
{
private:
    LoginInfo loginInfo;

public:
    User(/* args */) : loginInfo() { // initialize (composition) of loginInfo using its default constructor

                       };

    User(string username) : loginInfo(username) { // call primary constructor to create username

                            };

    User(string username, string password) : loginInfo(username, password) // primary constructor for Admin only
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

    virtual bool Login(string username, string userpassword) // registering for the first time
    {                                                        // Login Function

        if (username == loginInfo.GetUsername() && userpassword == loginInfo.GetPassword())
        {
            return true;
        }

        return false;
    }

    virtual int GetLibraryNumber()
    {
        return 0;
    }

   virtual void CheckinBook(Book book){

    }

    
   virtual void CheckOutBook(){

    }


    ~User() {

    };
};

#endif