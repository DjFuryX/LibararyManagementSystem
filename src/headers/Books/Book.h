#ifndef BOOK_H
#define BOOK_H

#include <iostream>
using namespace std;

#include"src/headers/User/Patron.h"

class Book
{
private:
    string title;
    string author;
    int ISBN;
    Patron *rentee;

public:
    // Constructor
    Book()
    {
        title = "NotSet";
        author = "NotSet";
        ISBN = 0;
        rentee = NULL;
    }

    Book(string nTitle, string nAuthor, int nISBN)
    {
        title = nTitle;
        author = nAuthor;
        ISBN = nISBN;
        rentee = NULL;
    }

    Book(int nISBN, string nTitle, string nAuthor)
    {
        title = nTitle;
        author = nAuthor;
        ISBN = nISBN;
        rentee = NULL;
    }

    Book(const Book &newBook)
    {
        title = newBook.title;
        author = newBook.author;
        ISBN = newBook.ISBN;
        rentee = newBook.rentee;
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
    int getISBN()
    {
        return ISBN;
    }
    Patron *getRentee()
    {
        return rentee;
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
    void setISBN(int nISBN)
    {
        ISBN = nISBN;
    }
    void Addrentee(Patron *barrower)
    {
        rentee = barrower;
    }

    // display book details
    void displayBookInfo()
    {

        cout << "Title: " << title << "\n";
        cout << "Author: " << author << "\n";
        cout << "ISBN: " << ISBN << "\n";
        if (rentee != NULL)
        {
            cout << "Book Rentee: " << rentee->GetUsername() << "\n";
        }
    }

    ~Book() {}
};

#endif