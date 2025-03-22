#ifndef TILELIST_H
#define TILELIST_H

#include "TileNode.h"
#include <string> //for string comparisions

// TileNode object
class TileList
{
    // Class attribues
private:
    TileNode *Head; // Head should point to the first element in list
   
    // Define the scroll panel bounds and content
    float panelScroll;
    float minScroll;
    float maxScroll;
    Rectangle panel;

    Vector2 mousePoint;
    float mouseWheelSpeed;
    int wheelMove;
    int rowCount;
    int coloumnCount;
    float offset;

    float targetScroll;
    float animationTime;
    float animationDuration; // Adjust duration as needed

    Texture2D bookTexture;
    Texture2D checkerTexture;
    Font textFont;
    void ClearList(TileNode *node)
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
        //load book textures
        bookTexture = LoadTexture("src/resources/images/Book.png");
        checkerTexture = LoadTexture("src/resources/images/check.png");
        // generate Mipmaps for higher quality fonts
        GenTextureMipmaps(&textFont.texture);
        GenTextureMipmaps(&checkerTexture);
        // set texture filter to prevent blurry fonts
        SetTextureFilter(textFont.texture, TEXTURE_FILTER_TRILINEAR);
        SetTextureFilter(checkerTexture, TEXTURE_FILTER_TRILINEAR);
    }

    void GetMouseScroll()
    {
        mousePoint = GetMousePosition();

        if (CheckCollisionPointRec(mousePoint, panel))
        {

            wheelMove = (int)GetMouseWheelMove();
            wheelMove = Clamp(wheelMove, -1, 1);
            targetScroll += wheelMove * mouseWheelSpeed; // Vertical scroll
            animationTime = 0.0f;                        // Reset animation time
        }
        animationTime += GetFrameTime(); // Increment animation time
        panelScroll = EaseExpoOut(animationTime, panelScroll, targetScroll - panelScroll, animationDuration);
        targetScroll = Clamp(targetScroll, -maxScroll, minScroll);
    }

public:
    // default constructor
    TileList() // Creates an empty list || 99% used
    {

        Head = NULL;
        LoadTexures();
        panelScroll = 0;
        panel = {150, 100, (float)GetScreenWidth() - 150, (float)GetScreenHeight() - 100};
        mouseWheelSpeed = 50;

        wheelMove = 0;
        offset = 50;
        rowCount = 5;
        coloumnCount = 0;
        maxScroll = 0;
        minScroll = 0;
        targetScroll = 0;
        animationTime = 0;
        animationDuration = 1;
    }

    // Accessors
    TileNode *GetHead()
    {
        return Head;
    }

    // Mutator
    void SetHead(TileNode *head)
    {
        Head = head;
    }

    void InsertAtBack(Book bookToInsert)
    {
        TileNode *temp = new TileNode(bookToInsert,textFont,bookTexture,checkerTexture); // initialize temp1 using the primary constructor 3 | Reserve Memory Space
     
        if (temp != NULL) // if memory was allocated successfully
        {
            if (Head == NULL) // if the list is empty
            {
                Head = temp; // set head to point to the new node to be added to list
            }
            else // if the list was not empty
            {
                TileNode *temp2 = Head;              // initialize temp node to point to first element in list
                while (temp2->GetNextNode() != NULL) // while we are not at the last node in the list
                {
                    temp2 = temp2->GetNextNode(); // move the current node (temp2) to IT'S next node
                }
                temp2->SetNextNode(temp); // set the link portion (NextNode) of the last node to point to the new node we are trying to add to the list
            }
            CaculateTilePosition();
        }
        else // if memory was not allocated successfully
        {
            cerr << "Error! List is full (Out of Memory), can NOT add a new node" << endl;
        }
    }

    int CountNodes()
    {
        int count = 0;         // initialize counter
        TileNode *curr = Head; // initialize curr to point to first element in list
        while (curr != NULL)   // while curr is pointing to a valid node
        {
            count++;                    // increment counter
            curr = curr->GetNextNode(); // point curr to IT'S next node
        }
        return count; // return number of elements in list
    }

    bool SearchByID(int bookId)
    {
        bool isFound = false;

        TileNode *curr = Head; // point curr to the first element in the list.
        while (curr != NULL)   // while curr is pointing to a valid node
        {
            if (curr->GetData().GetBook().getISBN() == bookId) // if the curr node has the data we are searching for
            {
                isFound = true; // set the bool to true (element found)
                break;          // jump out of loop
            }
            curr = curr->GetNextNode(); // point curr to IT'S next node
        }

        return isFound;
    }

    Book GetBook(string title)
    {
        TileNode *curr = Head; // point curr to the first element in the list.
        Book book;
        while (curr != NULL) // while curr is pointing to a valid node
        {
            if (curr->GetData().GetBook().getTitle() == title) // if the curr node has the data we are searching for
            {
                book = curr->GetData().GetBook();
                return book;
            }
            curr = curr->GetNextNode(); // point curr to IT'S next node
        }
        return book;
    }

    void DrawList()
    {
        GetMouseScroll();
        GetBookHovered();
        
        TileNode *curr = Head; // point curr to the first element in the list.
        while (curr != NULL)   // while curr is pointing to a valid node
        {
            curr->GetData().Draw(panelScroll);

            curr = curr->GetNextNode(); // point curr to IT'S next node
        }

        GetBookPressed();
       
    }

    Book *GetBookPressed()
    {
        Book *book = NULL;

        TileNode *curr = Head; // point curr to the first element in the list.
        while (curr != NULL)   // while curr is pointing to a valid node
        {
            if (curr->GetDataPtr()->isPressed(panelScroll))
            {
                book = curr->GetDataPtr()->GetBookPtr();
            }
            curr = curr->GetNextNode(); // point curr to IT'S next node
        }
        return book;
    }

    Book *GetBookHovered()
    {
        Book *book = NULL;

        TileNode *curr = Head; // point curr to the first element in the list.
        while (curr != NULL)   // while curr is pointing to a valid node
        {
            if (curr->GetData().isHovered(panelScroll))
            {
                book = curr->GetDataPtr()->GetBookPtr();
            }
            curr = curr->GetNextNode(); // point curr to IT'S next node
        }
        return book;
    }

    void CaculateTilePosition()
    {

        TileNode *curr = Head; // point curr to the first element in the list.
        int coloum = 0;

        while (curr != NULL) // while curr is pointing to a valid node
        {
            for (int row = 0; row < rowCount && curr != NULL; row++)
            {

                curr->GetDataPtr()->SetPosition(panel.x, panel.y, row, coloum, offset);

                curr = curr->GetNextNode(); // point curr to IT'S next node
            }
            coloum++;
            // cout << "Coloum" << coloum << "Coloum*mousespeed" << coloum * mouseWheelSpeed << endl;
            maxScroll = (coloum * (400 + 50)) - 900;
        }
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
        TileNode *temp = new TileNode; // attempt to reserve space for a new node by calling default constructor
        if (temp != NULL)              // if memory was allocated successfully
        {
            delete temp; // deallocate the memory for temp

            return false;
        }
        return true;
    }

    Tile DeleteANode(int bookId)
    {

        Tile dataToReturn;

        if (!IsEmpty())
        {
            TileNode *curr = Head, *prev = NULL; // point curr to the first element in the list.

            while (curr != NULL) // while curr is pointing to a valid node; go through list
            {
                if (curr->GetData().GetBook().getISBN() == bookId) // if the curr node has the data we are searching for
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
    }

    // Easing function for smooth scrolling
    float EaseExpoOut(float t, float b, float c, float d)
    {
        return (t == d) ? (b + c) : (c * (-powf(2.0f, -10.0f * t / d) + 1.0f) + b);
    }

    ~TileList()
    {
        UnloadTexture(bookTexture);
    }
};

#endif