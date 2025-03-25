// overal System manager handles input and flow of program
#ifndef LIBRARYMANAGEMENT_H
#define LIBRARYMANAGEMENT_H
#include "User/PatronLinkList.h"
#include "Books/BookBST.h"
#include "Books/BookStack.h"
#include "Statistics/Statistics.h"
#include "User/Admin.h"
#include "User/Patron.h"
#include "Books/BookQueue.h"

class LibraryManagement
{
private:
    /* data */
    // list of patrons
    PatronLinkList patronList;

    // link list of books
    //---- BooKList bookList
    // Binary search tree of books
    BookBST bookList;
    // stack of books //checkout system
    BookStack bookstack;

    // Statistic object
    // TO Do
    Statistics statistics;

    User *user;

public:
    LibraryManagement(/* args */) : patronList(), bookList(), statistics()
    {
        user = new User;
    }

    PatronLinkList *GetPatronList()
    {

        return &patronList;
    }

    BookBST *GetBookBST(){
        return &bookList;
    }

    BookStack *GetBookStack(){
        
        return &bookstack;
    }

    void SetPatronList(PatronLinkList *plist)
    {

        patronList = *plist;
    }

    void SetUser(User *newUser)
    {
        user = newUser;
    }

    User *GetUser()
    {
        return user;
    }

    ~LibraryManagement()
    {
    }
};

#endif