#ifndef BOOKSTACK_H
#define BOOKSTACK_H

#include "BookStkNode.h"
using namespace std;

class BookStack
{
private:
    BookStkNode *top; // point to top

public:
    // Consstructor
    BookStack() : top(nullptr)
    {
    }

    // Check if empty
    bool isEmpty()
    {
        return top == nullptr;
    }

    //
    void push(Book &book)
    {
        BookStkNode *newNode = new BookStkNode(book, top);
        top = newNode;
    }

    // Pop a book
    Book pop()
    {
        if (isEmpty())
        {
            cout << "Stack is empty. Cannot pop." << endl;
            return Book();
        }

        
        BookStkNode *temp = top;  // stores the current top 
        Book poppedBook = temp->GetData();
        top = top->GetNextNode();    // update the top pointer
        delete temp;

        return poppedBook;  // return the book that was popped
    }
    
       /*  Book *searchByISBN(const int &isbn)
        {
            BookStkNode *current = top;
            while (current != nullptr)
            {
                if (current->GetData().getISBN() == isbn)
                {
                    return &(current->GetData()); // Return a pointer to the book
                }
                current = current->GetNextNode();
            }
            return nullptr; //  book is not found
        } */

        
};

#endif
