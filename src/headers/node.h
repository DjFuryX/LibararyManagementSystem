// Node.h
#include <iostream>
#ifndef Node_H
#define Node_H
#include "Book.h"
using namespace std;
// Node object
class Node
{
    // Class Attributes
private:
    Book Data;   // Data portion - Composition
    Node *leftNode;  // left node link portion (dynamically declared)
    Node *rightNode; // right node link portion (dynamically declared)

public:
    // default constructor
    Node() : Data() // initialize (composition) student using its default constructor
    {
        leftNode = NULL; // empty pointer to left node
        rightNode = NULL;   //empyt pointer to right node
    }

     // primary constructor No Nodes set only data created
     Node(Book data) : Data(data) // initialize (composition) student using its copy constructor
     {
         leftNode = NULL; // empty pointer to left node
         rightNode = NULL;   //empyt pointer to right nodel
     }

    // primary constructor leftnode
    Node(Book data, Node *lefttNode,Node *rightNode) : Data(data) // initialize (composition) student using its copy constructor
    {
        this->leftNode = leftNode;
        this->rightNode = leftNode;
    }

    // primary constructor 3
    Node(string title, string author, int isbn) : Data(title, author, isbn) // initialize (composition) student using its primary constructor
    {
        leftNode = NULL; // empty pointer to left node
        rightNode = NULL;   //empyt pointer to right nodel
    }

    // copy constructor
    Node(Node *node)
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

     Node  *GetLeftNode()
    {
        return leftNode;
    }

    Node *GetRightNode(){
        return rightNode;
    }

    Node*& GetLeftNodeRef(){
        return leftNode;
    };  // Return by reference to modify the actual node pointer

    Node*& GetRightNodeRef(){
        return rightNode;
    };  // Return by reference to modify the actual node pointer



    // Mutators
    void SetData(Book data)
    {
        Data = data;
    }

    void SetleftNode(Node *nextNode)
    {
        leftNode = nextNode;
    }

    void SetRightNode(Node *nextnode){
        rightNode = nextnode;
    }

    ~Node(){
        delete leftNode;
        delete rightNode;
    }
};

#endif