#ifndef BookNodeQ.h
#define BookNodeQ .h

#include "Book.h"

class BookQueueNode
{
public:
    Book book;
    BookQueueNode *next;
    BookQueueNode *prev;

    BookQueueNode(Book book){
        next= NULL;

    }
};
#endif   // BookNodeQ.h