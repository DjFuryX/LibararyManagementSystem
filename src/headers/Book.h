#include <string>
#include <iostream>
#ifndef BOOK_H
#define BOOK_H

using namespace std;

class Book
{
private:
    string title;
    string author;
    string ISBN;
    bool isAvailabile;

public:
    // Constructor
    Book()
    {
        title = "NotSet";
        author = "NotSet";
        ISBN = "NotSet";
        isAvailabile = true;
    }

    Book(string nTitle, string nAuthor, string nISBN, bool availability)
    {
        title = nTitle;
        author = nAuthor;
        ISBN = nISBN;
        isAvailabile = availability;
    }

    // Getters
    string getTitle()
    {
        return title;
    }
    string getAuthor()
    {
        return author;
    }
    string getISBN()
    {
        return ISBN;
    }
    bool getAvailability()
    {
        return isAvailabile;
    }

    // Setter methods

    void setTitle(string nTitle)
    {
        title = nTitle;
    }
    void setAuthor(string nAuthor)
    {
        author = nAuthor;
    }
    void setISBN(string nISBN)
    {
        ISBN = nISBN;
    }
    void setAvailability(bool availability)
    {
        isAvailabile = availability;
    }

    // display book details
    void displayBookInfo()
    {

        cout << "Title: " << title << "\n";
        cout << "Author: " << author << "\n";
        cout << "ISBN: " << ISBN << "\n";
        cout << "Book Availabilty: " << isAvailabile << "\n";
    }
};

#endif