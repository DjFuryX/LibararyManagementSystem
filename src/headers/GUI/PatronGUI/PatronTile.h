
#ifndef PATRONTILE_H
#define  PATRONTILE_H

#include "src/headers/GUI/Scene.h"

class PatronTile
{
private:
    Patron patron;
    Rectangle bookTile;
    Color tileColor;
    Font textFont;
    int textColor;
    float width;
    float height;
    float gap;
    Texture2D bookCover;
    Rectangle topbar = {0, 0, 1920, 100};
    Rectangle IconBox;
    Vector2 mousePoint;

public:
    PatronTile() : patron()
    {
        // create a default tile
        bookTile = {0, 0, width, height};
        tileColor = LIGHTGRAY;
        width = 300;
        height = 400;
        gap = 50;
        textColor = 0x000000ff;;
    }

    PatronTile(Patron ptrn) : patron(ptrn)
    {
        // create a default tile
        bookTile = {0, 0, width, height};
        tileColor = LIGHTGRAY;
        width = 300;
        height = 400;
        gap = 50;
        textColor = 0x000000ff;
    }

    PatronTile(Patron ptrn, Font fn, Texture2D bkTexture) : patron(ptrn)
    {
        // create a default tile
        bookTile = {0, 0, width, height};
        tileColor = LIGHTGRAY;
        width = 300;
        height = 400;
        gap = 50;
        textColor = 0x000000ff;
        textFont = fn;
        bookCover = bkTexture;
    }

    void SetTextFont(Font txtFont)
    {

        textFont = txtFont;
    }

    void SetBookTexture(Texture2D texture)
    {

        bookCover = texture;
    }

 

    PatronTile(float x, float y, float width, float height)
    {
        bookTile = {x, y, width, height};
        tileColor = LIGHTGRAY;
        width = 300;
        height = 400;
        gap = 50;
    }

    PatronTile(const PatronTile &t)
    {
        patron = t.patron;
        bookTile = t.bookTile;
        textFont = t.textFont;
        tileColor = t.tileColor;
        bookCover = t.bookCover;
        textColor = t.textColor;
        width = t.width;
        height = t.height;
        gap = t.gap;
    }

    void SetBook(Patron ptrn)
    {

        patron = ptrn;
    }

    Patron GetPatron()
    {
        return patron;
    }

    Patron *GetPatronPtr()

    {
        return &patron;
    }

    float GetHeight()
    {

        return height;
    }

    Rectangle GetTileRec()
    {

        return bookTile;
    }

    float GetGap()
    {
        return gap;
    }

    void SetPosition(float x, float y, int xIndex, int yIndex, float offset)
    {
        // create a grid of books to display
        bookTile = {x + offset + (xIndex * (width + gap)), y + offset + (yIndex * (height + gap)), width, height};
    }

    void Draw(float scroll)
    {
        bookTile.y += scroll;

        IsHovered();

        DrawRectangleRounded(bookTile,0.1,5,tileColor);

        IconBox = {bookTile.x+100,bookTile.y+20,100,100};
        DrawTexturePro(bookCover, (Rectangle){0, 0, (float)bookCover.width, (float)bookCover.height}, IconBox, Vector2Zero(), 0.0f, WHITE);
        
        GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, textColor);
        GuiSetStyle(DEFAULT, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
        GuiLabelFont((Rectangle){bookTile.x, bookTile.y - 50, bookTile.width, bookTile.height}, patron.GetLoginInfo()->GetUsername().c_str(), textFont, 25, textColor);
        GuiLabelFont((Rectangle){bookTile.x, bookTile.y, bookTile.width, bookTile.height},to_string(patron.GetLibraryNumber()).c_str(), textFont, 25, textColor);
    }


    void IsHovered()
    {
        mousePoint = GetMousePosition();
        if (CheckCollisionPointRec(mousePoint, bookTile))
        {
            tileColor = LIGHTGRAY;
        }
        else{
            tileColor = WHITE;
        }
     
    }
};

#endif