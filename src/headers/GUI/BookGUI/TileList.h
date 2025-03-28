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

    Texture2D bookTexture;
    Texture2D checkerTexture;
    Font textFont;

    void ClearList(TileNode *node, BookBST *&selectedList)
    {
        if (!IsEmpty())
        {

            if (node == NULL) // while curr is pointing to a valid node; go through list
            {
                return;
            }

            if (node->GetData().IsSelected())
            {

                selectedList->InsertByTitle(selectedList->GetRootNode(), node->GetData().GetBook());
                // selectedList->InsertBook(node->GetData().GetBook());
            }

            ClearList(node->GetNextNode(), selectedList);

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
    TileList() // Creates an empty list 
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
    TileNode *GetHead()
    {
        return Head;
    }

    // Mutator
    void SetHead(TileNode *head)
    {
        Head = head;
    }


    void InsertAtFront(Book bookToInsert)
    {
       TileNode *temp = new TileNode(bookToInsert, textFont, bookTexture, checkerTexture); // initialize temp1 using the primary constructor 3 | Reserve Memory Space;     // declare temp as a pointer to the memory address of a node
      

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

    void InsertAtBack(Book bookToInsert)
    {
        TileNode *temp = new TileNode(bookToInsert, textFont, bookTexture, checkerTexture); // initialize temp1 

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
        }
        else // if memory was not allocated successfully
        {
            cerr << "Error! List is full (Out of Memory), can NOT add a new node" << endl;
        }

        CaculateTilePosition();
    }

    void InsertAtBack(Book bookToInsert, bool selected)
    {
        TileNode *temp = new TileNode(bookToInsert, textFont, bookTexture, checkerTexture); // initialize temp1 using the primary constructor 3 | Reserve Memory Space
        temp->GetDataPtr()->SetSelectState(selected);
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

    BookBST *Clear()
    {
        BookBST *SelectedBooks = new BookBST;

        ClearList(GetHead(), SelectedBooks);

        absoluteDistance = 0;
        animationTime = 0;
        targetScroll = 0;
        panelScroll = 0;

        return SelectedBooks;
    }

    // Easing function for smooth scrolling
    float EaseExpoOut(float t, float b, float c, float d)
    {
        return (t == d) ? (b + c) : (c * (-powf(2.0f, -10.0f * t / d) + 1.0f) + b);
    }

    ~TileList()
    {
        UnloadTexture(bookTexture);
        UnloadTexture(checkerTexture);
    }
};

#endif