
#ifndef PATRON_H
#define PATRON_H
#include "User.h"
/**Patron class that stores user information - inherits from User class
 * Username
 * Password
 * Library Id - Generated Automaticaly and is a number between (5000 and 7000)
 */
class Patron : public User
{
private:
    int libraryID;   // Used as the Patron Library Card Number
    BookQueue queue; // queue of book checked out

public:
    // Constructor
    Patron() : User(), queue() // initialize base class using its default constructor
    {
        libraryID = 0;
    }

    // Primary
    Patron(string name) : User(name), queue() // Create patron and set username  //no password set
    {
        libraryID = 0;
    }

    // Getters
    int GetLibraryNumber()
    {
        return libraryID;
    }
    // return pointer to user queue so it can be modified
    BookQueue *GetUserQueue()
    {
        return &queue;
    }

    // Setter methods
    void SetLibraryNumber(int libNumb) // will propblaby not be used id is genereated automatically
    {
        libraryID = libNumb;
    }
    // function to add a  book to the queue
    void CheckinBook(Book book)
    {
        queue.Enqueue(book);
    }
    // function to deque book from queue
    void CheckOutBook()
    {
        queue.Dequeue();
    }

    // display patron details
    void Display()
    {
        cout << "Patron Name: " << GetLoginInfo()->GetUsername() << endl;
        cout << "Patron Library Number: " << libraryID << endl;
        cout << "Patron PassWord: " << GetLoginInfo()->GetPassword() << endl;
    }

    int GenerateLibraryID()
    {
        // uses random generation function from LoginInfo class
        return GetLoginInfo()->GenerateRandomNumber(5000, 7000); // new ID in range specified
    }

    bool Login(string username, string password)
    {
        // Login Function
        if (username == GetLoginInfo()->GetUsername() && GetLoginInfo()->comparePassword(password))
        {
            return true;
        }
        return false;
    }
};

// Overrides How the objects of this class are stored as string
ostream &operator<<(ostream &out, Patron c)
{
    if (c.GetLibraryNumber() != 0)//ensure the patron id is not 0
    {
        out << c.GetLibraryNumber() << "|" << c.GetLoginInfo()->GetUsername() << "|" << c.GetLoginInfo()->GetPassword() << endl;
        // outputs information in the format libraryID|Username|Password
    }
    //return user stream
    return out;
}

// Overrides How the objects of this class is read from a file
istream &operator>>(istream &is, Patron &p)
{
    // tempororary varaibles to hold class atributes
    int libraryNumber = 0;
    string name, password;
    char delim;

    // Read input values separated by '|'
    is >> libraryNumber >> delim; // read patron id
    getline(is, name, '|');       // read patron name
    getline(is, password);        // read patron password should already be hashed
    // use muttators to set vaules
    p.SetLibraryNumber(libraryNumber);
    p.GetLoginInfo()->SetUsername(name);
    p.GetLoginInfo()->SetPassword(password);
    // return stream;
    return is;
}

#endif