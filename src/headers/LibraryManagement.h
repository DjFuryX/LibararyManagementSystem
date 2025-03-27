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
    // list of patrons
    PatronLinkList patronList;
    // Binary search tree of books
    BookBST bookList;
    // stack of books //checkout system
    BookStack bookstack;

    // Statistic object
    Statistics statistics;

    User *user;

public:
    LibraryManagement() : patronList(), bookList(), statistics()
    {
        user = new User;
    }

    PatronLinkList *GetPatronList()// 
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

    Statistics *Getstats()
    {
        return &statistics;
    }

    ~LibraryManagement()
    {
    }
};

#endif