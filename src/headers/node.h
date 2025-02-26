#ifndef NODE_H
#define NODE_H

#include "Book.h"

class Node
{
private:
    Book data;
    Node *nextNode;
};
#endif