//overal System manager handles input and flow of program
#ifndef LIBRARYMANAGEMENT_H
#define LIBRARYMANAGEMENT_H
#include "User/PatronLinkList.h"
#include "Books/BookBST.h"
#include "Statistics/Statistics.h"

class LibraryManagement
{
private:
    /* data */
    //list of patrons
    PatronLinkList patronList;

    //link list of books
    //---- BooKList bookList
    //Binary search tree of books 
    BookBST bookList;
    //stack of books //checkout system
    //TO DO---- BookStack bookstack;

    //Statistic object
    Statistics stats;

public:
    LibraryManagement(/* args */){

    }
    ~LibraryManagement(){

    }

    PatronLinkList GetPatronList(){

        return patronList;
    }

    void SetPatronList(PatronLinkList plist){

        patronList =plist;
    }


};

#endif