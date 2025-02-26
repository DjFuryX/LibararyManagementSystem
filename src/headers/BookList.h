#include <string>
#include <iostream>
#include "node.h"
#include "book.h"

using namespace std;

//Used to store collection of Books


// TO DO !!
// Implement Node then add in BST for Sorting

class BookList{
    private:

        Node* head;

    public:
    //constructor

    BookList():head(nullptr){}

   
   
    //Add Book
    void addBook (Book book){
        Node* newNode = new Node(book);
        if(!head){
            head = newNode;
        }
        else {
            Node* temp = head;
            while (temp->nextNode){
                temp=nextNode;
            }
        }
    }


    //Display all l

    void displayBookInfo(){
        Node* temp = head; //start at head
        
        while(temp != nullptr){// then traversse 
            temp->data.displayBookInfo();
            temp=temp->nextNode;
        }
    }
}