// Node.h
#ifndef BookNode_H
#define BookNode_H
#include "Book.h"
/**  Node object for Binary Search tree*/
class BookNode
{
    // Class Attributes
private:
    Book Data;           // Data portion - Composition
    BookNode *leftNode;  // left node link portion
    BookNode *rightNode; // right node link portion

public:
    // default constructor
    BookNode() : Data() // initialize (composition)
    {
        leftNode = NULL;  // empty pointer to left node
        rightNode = NULL; // empyt pointer to right node
    }

    // primary constructor No Nodes set only data created
    BookNode(Book data) : Data(data) // initialize (composition)
    {
        leftNode = NULL;  // empty pointer to left node
        rightNode = NULL; // empyt pointer to right nodel
    }

    // primary constructor Left and Righ Node
    BookNode(Book data, BookNode *lNode, BookNode *rNode) : Data(data) // initialize (composition) using a copy constructor
    {
        leftNode = lNode;
        rightNode = rNode;
    }

    // copy constructor
    BookNode(BookNode *node)
    {
        Data = node->Data;
        leftNode = node->leftNode;
        rightNode = node->rightNode;
    }

    // Accessors
    Book GetData() // returns book data
    {
        return Data;
    }

    Book *GetDataPtr()
    { // returns pointer to book data to call its functons

        return &Data;
    }

    BookNode *&GetLeftNode()
    { // get current node left node
        return leftNode;
    }; // Return by reference to modify the actual node pointer

    BookNode *&GetRightNode()
    { // get current node right node
        return rightNode;
    }; // Return by reference to modify the actual node pointer

    // Mutators
    void SetData(Book data) // sets book data
    {
        Data = data;
    }

    void SetleftNode(BookNode *nextNode) // set node's Left Node
    {
        leftNode = nextNode; // set pointer
    }

    void SetRightNode(BookNode *nextnode)
    {                         // set node's Right Node
        rightNode = nextnode; // set pointer
    }
    // Destructor
    ~BookNode()
    {
    }
};

#endif