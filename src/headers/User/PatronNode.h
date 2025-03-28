// Node.h
#ifndef PATRONNODE_H
#define PATRONNODE_H
#include "Patron.h"
using namespace std;
// Node object for patron list
class PatronNode
{
    // Class Attributes
private:
    Patron data;          // Data portion 
    PatronNode *NextNode; // Link portion

public:
    // default constructor
    PatronNode() : data() // initialize 
    {
        NextNode = NULL;
    }

    // primary constructor 
    PatronNode(Patron info, PatronNode *nextNode) : data(info) // initialize 
    {
        NextNode = nextNode;
    }

    // primary constructor 
    PatronNode(Patron info) : data(info) // initialize 
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

    Patron *GetDataPtr()
    {
        return &data;
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