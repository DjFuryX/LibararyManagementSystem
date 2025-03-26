// Node.h
#ifndef PATRONTILENODE_H
#define PATRONTILENODE_H
#include "PatronTile.h"
using namespace std;
// Node object
class PatronTileNode
{
    // Class Attributes
private:
    PatronTile data;          // Data portion - Composition
    PatronTileNode *NextNode; // Link portion (dynamically declared)

public:
    // default constructor
    PatronTileNode() : data() // initialize (composition) student using its default constructor
    {
        NextNode = NULL;
    }

    PatronTileNode(Patron ptrn) : data(ptrn)
    {
        NextNode = NULL;
    }
    PatronTileNode(Patron ptrn, Font font, Texture2D bookTexture) : data(ptrn, font, bookTexture)
    {
        NextNode = NULL;
    }

    PatronTileNode(float x, float y, float width, float height) : data(x, y, width, height)
    {
        NextNode = NULL;
    }

    PatronTileNode(float x, float y, float width, float height, PatronTileNode *nextNode) : data(x, y, width, height)
    {
        NextNode = nextNode;
    }

    // primary constructor 1
    PatronTileNode(PatronTile tile, PatronTileNode *nextNode) : data(tile) // initialize (composition) student using its copy constructor
    {
        NextNode = nextNode;
    }

    // primary constructor 2
    PatronTileNode(PatronTile tile) : data(tile) // initialize (composition) student using its copy constructor
    {
        NextNode = NULL; // set the next node to null
    }

    // copy constructor
    PatronTileNode(PatronTileNode *node)
    {
        data = node->data;
        NextNode = node->NextNode;
    }

    // Accessors
    PatronTile GetData()
    {
        return data;
    }

    PatronTile *GetDataPtr()
    {
        return &data;
    }

    PatronTileNode *GetNextNode()
    {
        return NextNode;
    }

    // Mutators
    void SetData(PatronTile tile)
    {
        data = tile;
    }

    void SetNextNode(PatronTileNode *nextNode)
    {
        NextNode = nextNode;
    }
};

#endif