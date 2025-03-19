// Node.h
#ifndef BOOKSTKNODE_H
#define BOOKSTKNODE_H
#include "Book.h"
using namespace std;
// Node object
class BookStkNode
{
    // Class Attributes
private:
    Book data;    // Data portion - Composition
    BookStkNode *Top; // Link portion (dynamically declared)

public:
    // default constructor
    BookStkNode() : data() // initialize (composition) student using its default constructor
    {
        Top = NULL;
    }

    // primary constructor 1
    BookStkNode(Book info, BookStkNode *nextNode) : data(info) // initialize (composition) student using its copy constructor
    {
        Top = nextNode;
    }

    // primary constructor 2
    BookStkNode(Book info) : data(info) // initialize (composition) student using its copy constructor
    {
        Top = NULL; // set the next node to null
    }


    // copy constructor
    BookStkNode(BookStkNode *node)
    {
        data = node->data;
        Top = node->Top;
    }

    // Accessors
    Book GetData()
    {
        return data;
    }

    BookStkNode *GetNextNode()
    {
        return Top;
    }

    // Mutators
    void SetData(Book info)
    {
        data = info;
    }

    void SetNextNode(BookStkNode *nextNode)
    {
        Top = nextNode;
    }
};


#endif