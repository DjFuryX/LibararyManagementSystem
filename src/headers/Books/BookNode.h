// Node.h
#ifndef BookNode_H
#define BookNode_H
#include "Book.h"
// Node object
class BookNode
{
    // Class Attributes
private:
    Book Data;   // Data portion - Composition
    BookNode *leftNode;  // left node link portion (dynamically declared)
    BookNode *rightNode; // right node link portion (dynamically declared)

public:
    // default constructor
    BookNode() : Data() // initialize (composition) student using its default constructor
    {
        leftNode = NULL; // empty pointer to left node
        rightNode = NULL;   //empyt pointer to right node
    }

     // primary constructor No Nodes set only data created
     BookNode(Book data) : Data(data) // initialize (composition) student using its copy constructor
     {
         leftNode = NULL; // empty pointer to left node
         rightNode = NULL;   //empyt pointer to right nodel
     }

    // primary constructor leftnode
    BookNode(Book data, BookNode *lNode,BookNode *rNode) : Data(data) // initialize (composition) student using its copy constructor
    {
        this->leftNode = lNode;
        this->rightNode = rNode;
    }

    // primary constructor 3
    BookNode(string title, string author, int isbn) : Data(title, author, isbn) // initialize (composition) student using its primary constructor
    {
        leftNode = NULL; // empty pointer to left node
        rightNode = NULL;   //empyt pointer to right nodel
    }

    // copy constructor
    BookNode(BookNode *node)
    {
        Data = node->Data;
        leftNode = node->leftNode;
        rightNode = node->rightNode;
    }

    // Accessors
    Book GetData()
    {
        return Data;
    }

     BookNode  *GetLeftNode()
    {
        return leftNode;
    }

    BookNode *GetRightNode(){
        return rightNode;
    }

    BookNode*& GetLeftNodeRef(){
        return leftNode;
    };  // Return by reference to modify the actual node pointer

    BookNode*& GetRightNodeRef(){
        return rightNode;
    };  // Return by reference to modify the actual node pointer



    // Mutators
    void SetData(Book data)
    {
        Data = data;
    }

    void SetleftNode(BookNode *nextNode)
    {
        leftNode = nextNode;
    }

    void SetRightNode(BookNode *nextnode){
        rightNode = nextnode;
    }

    ~BookNode(){
        //delete leftNode;
       // delete rightNode;
    }
};

#endif