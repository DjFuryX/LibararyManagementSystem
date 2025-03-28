#ifndef BookQueueNode_h
#define BookQueueNode_h
#include "Book.h"
/**Node used by book queue to store book an pointer*/
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
    BookQueueNode *GetNextNode() // returns node's Next node
    {
        return next;
    }

    Book GetData() // return books information
    {
        return book;
    }
};
#endif //  BookNodeQ.h