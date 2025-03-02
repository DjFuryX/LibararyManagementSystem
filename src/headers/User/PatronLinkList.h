#ifndef LinkedList_H
#define LinkedList_H

#include "PatronNode.h"

// Node object
class PatronLinkList
{
    // Class attribues
private:
    Node *Head; // Head should point to the first element in list

public:
    // default constructor
    PatronLinkList() // Creates an empty list || 99% used
    {
        Head = NULL;
    }

    // primary
    PatronLinkList(Node *h) // Creates a list with one element in there
    {
        Head = h;
    }

    // Accessors
    Node *GetHead()
    {
        return Head;
    }

    // Mutator
    void SetHead(Node *head)
    {
        Head = head;
    }


    void InsertAtFront(Patron dataToInsert)
    {
        Node *temp;      // declare temp as a pointer to the memory address of a node
        temp = new Node; // calls default constructor and attempts to reserve memory for temp

        if (temp != NULL) // if memory was allocated successfully
        {
            temp->SetData(dataToInsert); // set the data of the new node
            temp->SetNextNode(NULL);     // set the link portion to point to NULL

            if (Head == NULL) // if the list is empty
            {
                Head = temp;
            }
            else // if the list was not empty
            {
                temp->SetNextNode(Head); // points temps next node to head
                Head = temp;             // makes temp the new first node in the list
            }
        }
        else // if memory was not allocated successfully
        {
            cerr << "Error! List is full (Out of Memory), can NOT add a new node" << endl;
        }
    }

    

    int CountNodes()
    {
        int count = 0;       // initialize counter
        Node *curr = Head;   // initialize curr to point to first element in list
        while (curr != NULL) // while curr is pointing to a valid node
        {
            count++;                    // increment counter
            curr = curr->GetNextNode(); // point curr to IT'S next node
        }
        return count; // return number of elements in list
    }

    bool SearchForANode(int librayNumber)
    {
        bool isFound = false;

        Node *curr = Head;   // point curr to the first element in the list.
        while (curr != NULL) // while curr is pointing to a valid node
        {
            if (curr->GetData().GetLibraryNumber() == librayNumber) // if the curr node has the data we are searching for
            {
                isFound = true; // set the bool to true (element found)
                break;          // jump out of loop
            }
            curr = curr->GetNextNode(); // point curr to IT'S next node
        }

        return isFound;
    }

    void DisplayList()
    {
        Node *curr = Head;   // point curr to the first element in the list.
        while (curr != NULL) // while curr is pointing to a valid node
        {
            cout << "[";
            curr->GetData().Display(); // display the data for that node
            cout << "]->";
            curr = curr->GetNextNode(); // point curr to IT'S next node
        }
        cout << "NULL";
    }

    bool IsEmpty()
    {
        if (Head == NULL) // if the list is empty
        {
            return true; // return TRUE - list is empty
        }
        return false; // List is not empty
    }

    bool IsFull()
    {
        Node *temp = new Node; // attempt to reserve space for a new node by calling default constructor
        if (temp != NULL)      // if memory was allocated successfully
        {
            delete temp; // deallocate the memory for temp

            return false;
        }
        return true;
    }

    Patron DeleteANode(int libraryNumber)
    {

        Patron dataToReturn;

        if (!IsEmpty())
        {
            Node *curr = Head, *prev = NULL; // point curr to the first element in the list.

            while (curr != NULL) // while curr is pointing to a valid node; go through list
            {
                if (curr->GetData().GetLibraryNumber() == libraryNumber) // if the curr node has the data we are searching for
                {
                    if (curr == Head) // if curr is pointing to head (if we are deleting the first node in list)
                    {
                        Head = Head->GetNextNode(); // point head to IT's next node
                    }
                    else
                    {
                        prev->SetNextNode(curr->GetNextNode()); // set the next node of "prev" to "curr" next node
                    }
                    dataToReturn = curr->GetData(); // capture data from node to be deleted.
                    delete curr;                    // deallocate memory for curr
                    break;                          // jump out of loop
                }
                prev = curr;
                curr = curr->GetNextNode(); // point curr to IT's next ndoe
            }
        }
        else
        {
            cerr << "The list is empty; there is nothing to delete!" << endl;
        }

        return dataToReturn;
    }
};

#endif