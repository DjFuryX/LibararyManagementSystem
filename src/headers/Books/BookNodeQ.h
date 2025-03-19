#ifndef BOOKNODEQ_h
#define BOOKNODEQ_h

#include "Book.h"

class BookQueueNode
{
public:
    Book book;
    BookQueueNode *next;
    BookQueueNode *prev;

    BookQueueNode(Book book)
    {
        next= NULL;
        prev = NULL;
    }

    void setBook(Book x){book = x;}
    void setqnext(BookQueueNode* x){next = x;}
    void setqprev(BookQueueNode* x){prev = x;}

    Book getBook(){return book;}
    BookQueueNode* getqnext(){return next;}
    BookQueueNode* getqprev(){return prev;}

};
#endif // BookNodeQ.h