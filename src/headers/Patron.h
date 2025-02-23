#include <string>
#include <iostream>
#include <list>
#include "Book.h"

using namespace std;

class Patron{
    public:

    string name;
    int libraryNumber;       //Used as the Patron Library Card Number
    std::list<Book> checkedOutBooks;

    // Constructor 
    Patron(){
        libraryNumber = 0;
        name ="NotSet";

    }

    //Primary
    Patron (int libNumb, string pName){
        libraryNumber = libNumb;
        name =pName;
    }


    // Getters
    int getLibraryNumber(){ 
        return libraryNumber; 
    }
    string getName(){ 
        return name; 
    }

    // Setter methods
    void setLibraryNumber(int libNumb) { 
        libraryNumber = libNumb; 
    }

    void setName(string pName){ 
        name =pName; 
    }

    //CheckOut Book
    void getCheckoutBook(Book book) {
        checkedOutBooks.push(book);
        cout << name << " Checked out " << book.getTitle << endl;
    }


    //Return Book Method
    void returnBook(Book){
        cout << name << " Retruned Vook " << book.getTitle << endl;

    }
   
   
    //display patron details
    void displayPatronDetails(){
        cout <<"Patron Name: "<<name<<"\n";
        cout <<"Patron Library Number: "<<libraryNumber<<"\n";
        cout <<"Books Checked Out: ";
    }



};