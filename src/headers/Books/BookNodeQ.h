#ifndef BookQueueNode_h
#define BookQueueNode_h

#include "Book.h"

class BookQueueNode
{
private:
    Book book;
    BookQueueNode *next;
public:
    BookQueueNode(Book newbook)
    {
        book =newbook;
        next = NULL;
    }

    void SetNextNode(BookQueueNode *node){
        next=node;
    }
    void SetData(Book newBook){
        book=newBook;
    }
    BookQueueNode *GetNextNode(){

        return next;
    }

    Book GetData(){

        return book;
    }

};
#endif //  BookNodeQ.h