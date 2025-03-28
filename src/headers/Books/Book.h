/**contains the book information in the libray such as
 *  title,author, ISBN and Id of patron who rented the book if any*/
#ifndef BOOK_H
#define BOOK_H
#include <iostream>
using namespace std;

class Book
{ // class attributes
private:
    string title;  // book title
    string author; // book author
    int ISBN;      // book ID (ISBN)
    int renteeID;  // Id of Patron who current has the book checked out

public:
    // Default Constructor
    Book()
    {
        title = "NotSet";
        author = "NotSet";
        ISBN = 0;
        renteeID = 0;
    }
    // Primary Constructor
    Book(string nTitle, string nAuthor, int nISBN)
    {
        title = nTitle;
        author = nAuthor;
        ISBN = nISBN;
        renteeID = 0;
    }

    // Copy Constructor
    Book(const Book &newBook)
    {
        title = newBook.title;
        author = newBook.author;
        ISBN = newBook.ISBN;
        renteeID = newBook.renteeID;
    }

    // Copy Pointer Constructor
    Book(Book *book)
    {
        title = book->title;
        author = book->author;
        ISBN = book->ISBN;
        renteeID = book->renteeID;
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
    void SetRenteeID(int id)
    {

        renteeID = id;
    }

    // display book details
    void Display()
    {
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "ISBN: " << ISBN << endl;
        cout << "Book Rentee ID: " << renteeID << endl;
    }

    ~Book() {}
};

// Overrides How the objects of this class are stored as string
ostream &operator<<(ostream &out, Book c)
{ // out is the filestream and c is the book object
    out << c.getISBN() << "|" << c.getTitle() << "|" << c.getAuthor() << "|" << c.getRenteeID() << endl;
    // outputs in the format |ISBN|Title|Author|RenteeId
    // return file stream
    return out;
}

// Overrides How the objects of the book class is read from a file
istream &operator>>(istream &is, Book &b)
{

    // tempororary varaibles to hold class atributes
    int ISBN = 0, renteeID = 0;
    string title, author;
    char delim; // delim is to read the '|' character

    // Read input values separated by '|'
    is >> ISBN >> delim;      // read book ISBN
    getline(is, title, '|');  // read book Title
    getline(is, author, '|'); // read book author
    is >> renteeID;
    is.get(); // ensure empty values are not read
    // use muttators to set vaules
    b.setISBN(ISBN);
    b.setTitle(title);
    b.setAuthor(author);
    b.SetRenteeID(renteeID);
    // return stream;
    return is;
}

#endif