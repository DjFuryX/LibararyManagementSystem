// Admin class with features such as add
// password and username should be "Admin"

#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"

class Admin:public User
{

public:
    Admin(/* args */):User("Admin","Admin")// initialize base class using its default constructor
    {//password and username set to "Admin"

    };

    ~Admin()
    //destructor
    { 

    };

};

#endif

