#ifndef BOOK_H
#define BOOK_H

#include <iostream>
using namespace std;

#include "src/headers/User/Patron.h"

class Book
{
private:
    string title;
    string author;
    int ISBN;
    Patron *rentee;

    int renteeID;// only for assinging rentee pointer when reading from file

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
    void SetRenteeID(int id){
        renteeID=id;
    }
    void Setrentee(Patron *barrower)
    {
        rentee = barrower;
    }

    // display book details
    void Display()
    {

        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "ISBN: " << ISBN << endl;
        if (rentee != NULL)
        {
            cout << "Book Rentee: " << rentee->GetLoginInfo()->GetUsername() << endl;
        }
    }

    ~Book() {}
};

// Overrides How the objects of this class are stored as string
ostream &operator<<(ostream &out, Book c)
{
    out << c.getISBN() << "|" << c.getTitle() << "|" << c.getAuthor();

    if (c.getRentee() != NULL)
    {

        out << "|" << c.getRentee()->GetLibraryNumber();
    }
    else
    {
        out << "|" << "0000";
    }

    out << endl;

    return out;
}

// Overrides How the objects of the book class is read from a file
istream &operator>>(istream &is, Book &b)
{

    // tempororary varaibles to hold class atributes
    int ISBN=0,renteeID=0;
    string title, author;
    char delim;

    // Read input values separated by '|'
    is >> ISBN >> delim; // read book ISBN
    getline(is, title, '|');       // read book Title
    getline(is, author,'|');        // read book author
    is>>renteeID;
    is.get();// ensure empty values are not read
    // use muttators to set vaules
    b.setISBN(ISBN);
    b.setTitle(title);
    b.setAuthor(author);
    b.SetRenteeID(renteeID);
    b.Setrentee(NULL);// TO DO set to null for now should change later

    
    // return stream;
    return is;
}



#endif