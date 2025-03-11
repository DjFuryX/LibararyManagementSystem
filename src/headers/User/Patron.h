
#ifndef PATRON_H
#define PATRON_H

#include "User.h"

class Patron : public User
{
private:
    int libraryID; // Used as the Patron Library Card Number
    // queue of book checked out
    // TO DO  BookQueue bookqueue

public:
    // Constructor
    Patron() : User() // initialize base class using its default constructor
    {
        libraryID = 0;
    }

    // Primary
    Patron(string name) : User(name) // Create patron and set username  //no password set
    {
        // TO do ensure Id number does not exist already
        libraryID = GenerateLibraryID();
        // libraryID = 0;
    }

    // Getters
    int GetLibraryNumber()
    {
        return libraryID;
    }

    string GetUsername()
    {

        return GetName();
    }

    // Setter methods
    void SetLibraryNumber(int libNumb) // will propblaby not be used id is genereated automatically
    {
        libraryID = libNumb;
    }

    // display patron details
    void Display()
    {
        cout << "Patron Name: " << GetName() << endl;
        cout << "Patron Library Number: " << libraryID << endl;
        cout << "Patron PassWord: " << GetPassword() << endl;
    }

    int GenerateLibraryID()
    {
        // usese random generation function from Password class
        return generatetandomNumber(5000, 7000); // new ID in range specified
    }
};

// Overrides How the objects of this class are stored as string
ostream &operator<<(ostream &out, Patron c)
{
    out << c.GetLibraryNumber() << "|" << c.GetUsername() << "|" << c.GetPassword() << endl;
    return out;
}

std::istream &operator>>(std::istream &is, Patron &p)
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
    p.SetName(name);
    p.SetPassword(password);
    // return stream;
    return is;
}

#endif