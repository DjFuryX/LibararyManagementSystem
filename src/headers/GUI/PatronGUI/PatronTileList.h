#ifndef PATRONTILELIST_H
#define PATRONTILELIST_H

#include "PatronTileNode.h"
#include <string> //for string comparisions

// TileNode object
class PatronTileList
{
    // Class attribues
private:
    PatronTileNode *Head; // Head should point to the first element in list

    // Define the scroll panel bounds and content
    float panelScroll;
    float topBound;
    float bottomBound;
    float absoluteDistance;
    Rectangle panel;

    Vector2 mousePoint;
    float mouseWheelSpeed;
    int wheelMove;
    int rowCount;
    int coloumnCount;
    float offset;

    float targetScroll;
    float animationTime;
    float animationDuration;

    Texture2D patronIcon;
    Font textFont;

    void ClearList(PatronTileNode *node)
    {
        if (!IsEmpty())
        {

            if (node == NULL) // while curr is pointing to a valid node; go through list
            {
                return;
            }

            ClearList(node->GetNextNode());

            if (node == Head)
            {
                Head = NULL;
                return;
            }

            delete node; // deallocate memory for curr
        }
        else
        {
            cerr << "The list is empty; there is nothing to delete!" << endl;
        }
    }

    void LoadTexures()
    {
        // load default font files
        textFont = LoadFontEx("src/resources/fonts/Tahoma-Regular-font.ttf", 72, 0, 256);
        // load book textures
        patronIcon = LoadTexture("src/resources/images/mybook1.png");
        // generate Mipmaps for higher quality fonts
        GenTextureMipmaps(&textFont.texture);
        GenTextureMipmaps(&patronIcon);
        // set texture filter to prevent blurry fonts
        SetTextureFilter(textFont.texture, TEXTURE_FILTER_TRILINEAR);
        SetTextureFilter(patronIcon, TEXTURE_FILTER_TRILINEAR);
    }

    void GetMouseScroll()
    {
        mousePoint = GetMousePosition();

        if (CheckCollisionPointRec(mousePoint, panel))
        {
            wheelMove = (int)GetMouseWheelMove();
            wheelMove = Clamp(wheelMove, -1, 1);

            targetScroll = wheelMove * mouseWheelSpeed; // Vertical scroll

            absoluteDistance += targetScroll;
            animationTime = 0.0f; // Reset animation time
        }

        animationTime += GetFrameTime(); // Increment animation time

        if (absoluteDistance > topBound)
        {
            targetScroll = 0;
            absoluteDistance = topBound;
        }

        if (absoluteDistance < bottomBound)
        {
            targetScroll = 0;
            absoluteDistance = bottomBound;
        }

        panelScroll = EaseExpoOut(animationTime, panelScroll, targetScroll - panelScroll, animationDuration);

        // cout << targetScroll << " : " << panelScroll << " : " << absoluteDistance<<" : "<<bottomBound<< endl;
    }

public:
    // default constructor
    PatronTileList() // Creates an empty list
    {

        Head = NULL;
        LoadTexures();
        panelScroll = 0;
        panel = {150, 100, (float)GetScreenWidth() - 150, (float)GetScreenHeight() - 100};
        mouseWheelSpeed = 100;
        absoluteDistance = 0;
        wheelMove = 0;
        offset = 50;
        rowCount = 5;
        coloumnCount = 0;
        bottomBound = 0;
        topBound = 0;
        targetScroll = 0;
        animationTime = 0;
        animationDuration = 1;
    }

    // Accessors
    PatronTileNode *GetHead()
    {
        return Head;
    }

    // Mutator
    void SetHead(PatronTileNode *head)
    {
        Head = head;
    }

    void InsertAtFront(Patron patronToInsert)
    {
        PatronTileNode *temp = new PatronTileNode(patronToInsert, textFont, patronIcon); // initialize temp1 using the primary constructor 3 | Reserve Memory Space;     // declare temp as a pointer to the memory address of a node

        if (temp != NULL) // if memory was allocated successfully
        {
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
        CaculateTilePosition();
    }

    void InsertAtBack(Patron patronToInsert)
    {
        PatronTileNode *temp = new PatronTileNode(patronToInsert, textFont, patronIcon); 

        if (temp != NULL) // if memory was allocated successfully
        {
            if (Head == NULL) // if the list is empty
            {
                Head = temp; // set head to point to the new node to be added to list
            }
            else // if the list was not empty
            {
                PatronTileNode *temp2 = Head;              // initialize temp node to point to first element in list
                while (temp2->GetNextNode() != NULL) // while we are not at the last node in the list
                {
                    temp2 = temp2->GetNextNode(); // move the current node (temp2) to IT'S next node
                }
                temp2->SetNextNode(temp); // set the link portion (NextNode) of the last node to point to the new node we are trying to add to the list
            }
        }
        else // if memory was not allocated successfully
        {
            cerr << "Error! List is full (Out of Memory), can NOT add a new node" << endl;
        }

        CaculateTilePosition();
    }


    int CountNodes()
    {
        int count = 0;         // initialize counter
        PatronTileNode *curr = Head; // initialize curr to point to first element in list
        while (curr != NULL)   // while curr is pointing to a valid node
        {
            count++;                    // increment counter
            curr = curr->GetNextNode(); // point curr to IT'S next node
        }
        return count; // return number of elements in list
    }

    bool SearchByID(int patronId)
    {
        bool isFound = false;

        PatronTileNode *curr = Head; // point curr to the first element in the list.
        while (curr != NULL)   // while curr is pointing to a valid node
        {
            if (curr->GetData().GetPatron().GetLibraryNumber() == patronId) // if the curr node has the data we are searching for
            {
                isFound = true; // set the bool to true (element found)
                break;          // jump out of loop
            }
            curr = curr->GetNextNode(); // point curr to IT'S next node
        }

        return isFound;
    }

    Patron GetPatron(string patronName)
    {
        PatronTileNode *curr = Head; // point curr to the first element in the list.
        Patron patron;
        while (curr != NULL) // while curr is pointing to a valid node
        {
            if (  curr->GetData().GetPatron().GetLoginInfo()->GetUsername() == patronName) // if the curr node has the data we are searching for
            {
                patron = curr->GetData().GetPatron();
                return patron;
            }
            curr = curr->GetNextNode(); // point curr to IT'S next node
        }
        return patron;
    }


    

    void DrawList()
    {
        GetMouseScroll();
   
        PatronTileNode *curr = Head; // point curr to the first element in the list.
        while (curr != NULL)   // while curr is pointing to a valid node
        {
            curr->GetDataPtr()->Draw(panelScroll);

            curr = curr->GetNextNode(); // point curr to IT'S next node
        }
    }


    void CaculateTilePosition()
    {

        PatronTileNode *curr = Head; // point curr to the first element in the list.
        int coloum = 0;
        bottomBound = 0;
        coloumnCount = 0;

        while (curr != NULL) // while curr is pointing to a valid node
        {
            for (int row = 0; row < rowCount && curr != NULL; row++)
            {
                curr->GetDataPtr()->SetPosition(panel.x, panel.y, row, coloum, offset);
                curr = curr->GetNextNode(); // point curr to IT'S next node
            }
            coloum++;
        }

        coloumnCount = coloum - 2;
        bottomBound = -(coloumnCount * 450);
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
        PatronTileNode *temp = new PatronTileNode; // attempt to reserve space for a new node by calling default constructor
        if (temp != NULL)              // if memory was allocated successfully
        {
            delete temp; // deallocate the memory for temp

            return false;
        }
        return true;
    }

    PatronTile DeleteANode(int patronId)
    {

        PatronTile dataToReturn;

        if (!IsEmpty())
        {
            PatronTileNode *curr = Head, *prev = NULL; // point curr to the first element in the list.

            while (curr != NULL) // while curr is pointing to a valid node; go through list
            {
                if (curr->GetData().GetPatron().GetLibraryNumber() == patronId) // if the curr node has the data we are searching for
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

    void Clear()
    {
        
        ClearList(GetHead());

        absoluteDistance = 0;
        animationTime = 0;
        targetScroll = 0;
        panelScroll = 0;

    }

    // Easing function for smooth scrolling
    float EaseExpoOut(float t, float b, float c, float d)
    {
        return (t == d) ? (b + c) : (c * (-powf(2.0f, -10.0f * t / d) + 1.0f) + b);
    }

    ~PatronTileList()
    {
        UnloadTexture(patronIcon);
    }
};

#endif