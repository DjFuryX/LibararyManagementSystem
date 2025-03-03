/*- totalBooks: int
- TotalPatrons: int
- TotalCurrentCheckouts: int*/
#ifndef STATISTICS_H
#define STATISTICS_H

class Statistics
{
private:
    int totalBooks;
    int totalPatrons;
    int currentCheckouts;

public:
    Statistics(/* args */)
    {
        totalBooks = 0;
        totalPatrons = 0;
        currentCheckouts = 0;
    };
    ~Statistics(){};
};
#endif