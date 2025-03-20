#ifndef BOOK_H
#define BOOK_H

#include <iostream>
using namespace std;

class Book
{
private:
    string title;
    string author;
    int ISBN;
    int renteeID;
public:
    // Constructor
    Book()
    {
        title = "NotSet";
        author = "NotSet";
        ISBN = 0;
        renteeID = 0;
    }

    Book(string nTitle, string nAuthor, int nISBN)
    {
        title = nTitle;
        author = nAuthor;
        ISBN = nISBN;
        renteeID = 0;
    }

    Book(int nISBN, string nTitle, string nAuthor)
    {
        title = nTitle;
        author = nAuthor;
        ISBN = nISBN;
        renteeID = 0;
    }

    Book(const Book &newBook)
    {
        title = newBook.title;
        author = newBook.author;
        ISBN = newBook.ISBN;
        renteeID = newBook.renteeID;
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
    int getRenteeID()
    {
        return renteeID;
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
    void SetrenteeID(int patronId)
    {
        renteeID = patronId;
    }

    // display book details
    void Display()
    {

        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "ISBN: " << ISBN << endl;
        cout << "Book Rentee ID: " <<renteeID<< endl;
        
    }

    ~Book() {}
};

// Overrides How the objects of this class are stored as string
ostream &operator<<(ostream &out, Book c)
{
    out << c.getISBN() << "|" << c.getTitle() << "|" << c.getAuthor()<< "|" << c.getRenteeID()<< endl;

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
    // return stream;
    return is;
}



#endif