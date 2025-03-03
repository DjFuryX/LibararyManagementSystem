// Node.h
#ifndef Node_H
#define Node_H
#include "Patron.h"
using namespace std;
// Node object
class PatronNode
{
    // Class Attributes
private:
    Patron data;    // Data portion - Composition
    PatronNode *NextNode; // Link portion (dynamically declared)

public:
    // default constructor
    PatronNode() : data() // initialize (composition) student using its default constructor
    {
        NextNode = NULL;
    }

    // primary constructor 1
    PatronNode(Patron info, PatronNode *nextNode) : data(info) // initialize (composition) student using its copy constructor
    {
        NextNode = nextNode;
    }

    // primary constructor 2
    PatronNode(Patron info) : data(info) // initialize (composition) student using its copy constructor
    {
        NextNode = NULL; // set the next node to null
    }

    // primary constructor 3
    PatronNode(string name) : data(name) // initialize (composition) student using its primary constructor
    {
        NextNode = NULL; // set the next node to null
    }

    // copy constructor
    PatronNode(PatronNode *node)
    {
        data = node->data;
        NextNode = node->NextNode;
    }

    // Accessors
    Patron GetData()
    {
        return data;
    }

    PatronNode *GetNextNode()
    {
        return NextNode;
    }

    // Mutators
    void SetData(Patron info)
    {
        data = info;
    }

    void SetNextNode(PatronNode *nextNode)
    {
        NextNode = nextNode;
    }
};


#endif