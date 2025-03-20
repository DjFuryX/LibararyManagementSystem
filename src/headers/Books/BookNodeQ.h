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

    void setBook(Book x){book = x;}
    void setqnext(BookQueueNode* x){next = x;}
    void setqprev(BookQueueNode* x){prev = x;}

    Book getBook(){return book;}
    BookQueueNode* getqnext(){return next;}
    BookQueueNode* getqprev(){return prev;}

};
#endif //  BookNodeQ.h