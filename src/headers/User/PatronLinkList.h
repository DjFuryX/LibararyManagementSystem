#ifndef PatronLinkList_H
#define PatronLinkList_H
#include "PatronNode.h"
/** Patron link list that contains all patron in the library
 * Search - Id or Username
 * Insert - Using library number or at front
 * Delete
 * Count
 */

class PatronLinkList
{
    // Class attribues
private:
    PatronNode *Head; // Head should point to the first element in list

public:
    // default constructor
    PatronLinkList() // Creates an empty list
    {
        Head = NULL;
    }

    // primary
    PatronLinkList(PatronNode *h) // Creates a list with one element in there
    {
        Head = h;
    }

    // Accessors
    PatronNode *GetHead()
    {
        return Head;
    }

    // Mutator
    void SetHead(PatronNode *head)
    {
        Head = head;
    }

    void InsertAtFront(Patron dataToInsert)
    {
        PatronNode *temp;      // declare temp as a pointer to the memory address of a node
        temp = new PatronNode; // calls default constructor and attempts to reserve memory for temp

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

    void InsertByLibaryNumber(Patron dataToInsert)
    {

        PatronNode *temp;                      // declare temp as a pointer to the memory address of a node
        temp = new PatronNode;                 // calls default constructor and attempts to reserve memory for temp
        PatronNode *curr = Head, *prev = NULL; // point curr to the first element in the list.
        bool nodeAdded = false;

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
                while (curr != NULL) // while curr is pointing to a valid node; go through list
                {

                    if (curr->GetData().GetLibraryNumber() >= temp->GetData().GetLibraryNumber()) // if the curr node has age younger than the next in the list
                    {
                        if (curr == Head) // if curr is pointing to head (if we are inserting at the first node in list)
                        {
                            temp->SetNextNode(Head); // points temps next node to head
                            Head = temp;             // makes temp the new first node in the list
                        }
                        else
                        {

                            temp->SetNextNode(curr);//set temp node to point to curr node
                            prev->SetNextNode(temp);//prev node points to the current node
                            //prev ---/temp/----curr
                            
                        }
                        nodeAdded = true;// if a node was added to the list
                        break; // jump out of loop
                    }
                    prev = curr;
                    curr = curr->GetNextNode(); // point curr to IT's next ndoe
                }
                if (!nodeAdded)// if a node was not added
                {
                    prev->SetNextNode(temp); //add node to end of list

                    //prev ---/temp/----curr(NULL)
                }
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
        PatronNode *curr = Head;   // initialize curr to point to first element in list
        while (curr != NULL) // while curr is pointing to a valid node
        {
            count++;                    // increment counter
            curr = curr->GetNextNode(); // point curr to IT'S next node
        }
        return count; // return number of elements in list
    }

    bool SearchByID(int librayNumber)
    {
        bool isFound = false;

        PatronNode *curr = Head;   // point curr to the first element in the list.
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

    bool SearchByName(string patronName){
        bool isFound = false;
        PatronNode *curr = Head;   // point curr to the first element in the list.
        while (curr != NULL) // while curr is pointing to a valid node
        {
            if (curr->GetData().GetLoginInfo()->GetUsername() == patronName) // if the curr node has the data we are searching for
            {
                isFound = true; // set the bool to true (element found)
                break;          // jump out of loop
            }
            curr = curr->GetNextNode(); // point curr to IT'S next node
        }
    
        return isFound;
    }

    Patron* GetPatron(string username){
        PatronNode *curr = Head;   // point curr to the first element in the list.
        while (curr != NULL) // while curr is pointing to a valid node
        {
            if (curr->GetDataPtr()->GetLoginInfo()->GetUsername() == username) // if the curr node has the data we are searching for
            {
                return curr->GetDataPtr();
                break;          // jump out of loop
            }
            curr = curr->GetNextNode(); // point curr to IT'S next node
        }
    
        return NULL;

    }

    Patron* GetPatronNoCase(string username){
        PatronNode *curr = Head;   // point curr to the first element in the list.
        while (curr != NULL) // while curr is pointing to a valid node
        {
            if ( strcasecmp( curr->GetDataPtr()->GetLoginInfo()->GetUsername().c_str(), username.c_str())==0) // if the curr node has the data we are searching for
            {
                return curr->GetDataPtr();
                break;          // jump out of loop
            }
            curr = curr->GetNextNode(); // point curr to IT'S next node
        }
    
        return NULL;

    }

    Patron* GetPatron(int patronid) 
    {
        PatronNode *curr = Head;   // point curr to the first element in the list.
        Patron * temp = NULL;
        while (curr != NULL) // while curr is pointing to a valid node
        {
            if (curr->GetDataPtr()->GetLibraryNumber() == patronid) // if the curr node has the data we are searching for
            {
                temp =  curr->GetDataPtr();
                break;          // jump out of loop
            }
            curr = curr->GetNextNode(); // point cur
        }

        return temp;
    }

    void DisplayList()
    {
        PatronNode *curr = Head;   // point curr to the first element in the list.
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
        PatronNode *temp = new PatronNode; // attempt to reserve space for a new node by calling default constructor
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
            PatronNode *curr = Head, *prev = NULL; // point curr to the first element in the list.

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