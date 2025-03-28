#ifndef BOOKSTACK_H
#define BOOKSTACK_H
#include "BookStkNode.h"
/**  class to create a Stack that stores a book temporarily before checkout*/
class BookStack
{
private:
    BookStkNode *top; // point to top
    int totalBooks;   // total books in stack

public:
    // Default Constructor
    BookStack() : top(NULL)
    {
        totalBooks = 0;
    }

    // Check if empty
    bool isEmpty()
    {
        return (top == NULL);
    }
    // Getters
    BookStkNode *GetTop()
    { // returns top of stack

        return top;
    }

    int GetTotalBooks()
    { // get book count
        return totalBooks;
    }
    //
    void push(Book book) // adds a book to the stack
    {
        BookStkNode *newNode = new BookStkNode(book, top);
        top = newNode;
        totalBooks++;
    }

    // Pop a book
    Book pop() // removes a book from the stack and returns it
    {
        if (isEmpty())
        {
            return Book();
        }

        BookStkNode *temp = top; // stores the current top
        Book poppedBook = temp->GetData();
        top = top->GetNextNode(); // update the top pointer
        delete temp;              // free up memmory
        totalBooks--;             // decrease book conut
        return poppedBook;        // return the book that was popped
    }
};

#endif
