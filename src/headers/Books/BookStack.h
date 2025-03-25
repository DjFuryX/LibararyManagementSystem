#ifndef BOOKSTACK_H
#define BOOKSTACK_H

#include "BookStkNode.h"
using namespace std;

class BookStack
{
private:
    BookStkNode *top; // point to top
    int totalBooks;

public:
    // Constructor
    BookStack() : top(NULL)
    {
        totalBooks = 0;

    }

    // Check if empty
    bool isEmpty()
    {
        return (top == NULL);
    }


    BookStkNode *GetTop(){

        return top;
    }

    int GetTotalBooks(){
        return totalBooks;
    }
    //
    void push(Book book)
    {
        BookStkNode *newNode = new BookStkNode(book, top);
        top = newNode;
        totalBooks++;
    }

    // Pop a book
    Book pop()
    {
        if (isEmpty())
        {
            return Book();
        }

        BookStkNode *temp = top;  // stores the current top 
        Book poppedBook = temp->GetData();
        top = top->GetNextNode();    // update the top pointer
        delete temp;
        totalBooks--;
        return poppedBook;  // return the book that was popped
    }
        
};

#endif
