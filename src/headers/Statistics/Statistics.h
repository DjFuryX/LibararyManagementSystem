#ifndef STATISTICS_H
#define STATISTICS_H
#include <iostream>
using namespace std;
/** Statistics class to store information on the total books, total checkouts and total patrons in the library */
class Statistics
{
private:
    int totalBooks; // Total number of books in the library 
    int totalPatrons; // Totalnumber of registered Patrons
    int currentCheckouts; // Nummber of books checked out

public:
    Statistics()
    {
        totalBooks = 0;
        totalPatrons = 0;
        currentCheckouts = 0;
    };

    // Getter Methods
    int getTotalBooks()
    {
        return totalBooks;
    }

    int getTotalPatrons()
    {
        return totalPatrons;
    }

    int getTotalCurrentCheckouts()
    {
        return currentCheckouts;
    }

    // Setters 
    void setTotalBooks(int nTotalBooks) //adds accepted int to book total
    {
        totalBooks += nTotalBooks;
    }

    void setTotalPatrons(int nTotalPatrons) //adds accepted int to patron total
    {
        totalPatrons += nTotalPatrons;
    }

    void setTotCheckouts(int nTotalCurrentCheckouts) //adds accepted int to checkout total
    {
        currentCheckouts += nTotalCurrentCheckouts;
    }

    void ReduceTotalCheckouts(int checkouts) // reduces checkout once a book is returned 
    {
        currentCheckouts-=checkouts;
    }

    // Display statistics
    void displayStatistics()
    {
        cout << "Total Books: " << totalBooks << endl;
        cout << "Total Patrons: " << totalPatrons << endl;
        cout << "Total Current Checkouts: " << currentCheckouts << endl;
    }

    ~Statistics() {} //destructor
};
#endif