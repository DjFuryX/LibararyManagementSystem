// Node.h
#ifndef TILENODE_H
#define TILENODE_H
#include "Tile.h"
using namespace std;
// Node object
class TileNode
{
    // Class Attributes
private:
    Tile data; // Data portion - Composition
    TileNode *NextNode; // Link portion (dynamically declared)

public:
    // default constructor
    TileNode() : data() // initialize (composition) student using its default constructor
    {
        NextNode = NULL;
    }

    TileNode(float x, float y, float width, float height):data( x, y, width,height){
        NextNode = NULL;
    }

    TileNode(float x, float y, float width, float height,TileNode *nextNode):data( x, y, width,height){
        NextNode = nextNode;
    }

    // primary constructor 1
    TileNode(Tile tile, TileNode *nextNode) : data(tile) // initialize (composition) student using its copy constructor
    {
        NextNode = nextNode;
    }

    // primary constructor 2
    TileNode(Tile tile) : data(tile) // initialize (composition) student using its copy constructor
    {
        NextNode = NULL; // set the next node to null
    }

    // copy constructor
    TileNode(TileNode *node)
    {
        data = node->data;
        NextNode = node->NextNode;
    }

    // Accessors
    Tile GetData()
    {  
        return data;
    }

    Tile *GetDataPtr()
    {
        return &data;
    }

    TileNode *GetNextNode()
    {
        return NextNode;
    }

    // Mutators
    void SetData(Tile tile)
    {
        data = tile;
    }

    void SetNextNode(TileNode *nextNode)
    {
        NextNode = nextNode;
    }
};

#endif