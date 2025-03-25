/*- totalBooks: int
- TotalPatrons: int
- TotalCurrentCheckouts: int*/
#ifndef STATISTICS_H
#define STATISTICS_H
#include <iostream>
using namespace std;
class Statistics
{
private:
    int totalBooks;
    int totalPatrons;
    int currentCheckouts;

public:
    Statistics()
    {
        totalBooks = 0;
        totalPatrons = 0;
        currentCheckouts = 0;
    };

    // Getters
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
    void setTotalBooks(int nTotalBooks) //admin func later
    {
        totalBooks = nTotalBooks;
    }

    void setTotalPatrons(int nTotalPatrons) //done
    {
        totalPatrons = nTotalPatrons;
    }

    void setTotCheckouts(int nTotalCurrentCheckouts) //done
    {
        currentCheckouts += nTotalCurrentCheckouts;
    }

    void setBooktot(int x)
    {
        totalBooks+= x;
    }
   


    // Display statistics
    void displayStatistics()
    {
        cout << "Total Books: " << totalBooks << endl;
        cout << "Total Patrons: " << totalPatrons << endl;
        cout << "Total Current Checkouts: " << currentCheckouts << endl;
    }

    ~Statistics() {}
};
#endif