#ifndef BookQueueNode_h
#define BookQueueNode_h
#include "Book.h"
// class to store books user has checkout in a Queue
class BookQueueNode
{
private:
    Book book;           // Book information
    BookQueueNode *next; // Node Pointer
public:
    // Primary Constructor
    BookQueueNode(Book newbook)
    {
        book = newbook;
        next = NULL;
    }
    // Setters
    void SetNextNode(BookQueueNode *node)
    {
        next = node;
    }
    void SetData(Book newBook)
    {
        book = newBook;
    }
    // Getters
    BookQueueNode *GetNextNode()
    {

        return next;
    }

    Book GetData()
    {

        return book;
    }
};
#endif //  BookNodeQ.h