
#ifndef TILE_H
#define TILE_H

#include "Scene.h"

class Tile
{
private:
    Book book;
    Rectangle bookTile;
    Color tileColor;
    Font textFont;
    int textColor = 0x000000ff;
    float width;
    float height;
    float gap;
    Texture2D bookCover;

public:
    Tile() : book()
    {
        // create a default tile
        bookTile = {0, 0, width, height};
        tileColor = RED;
        width = 300;
        height = 400;
        gap = 50;
    }

    void SetTextFont(Font txtFont)
    {

        textFont = txtFont;
    }

    void SetBookTexture(Texture2D texture)
    {

        bookCover = texture;
    }

    Tile(float x, float y, float width, float height)
    {
        bookTile = {x, y, width, height};
        tileColor = RED;
        width = 300;
        height = 400;
        gap = 50;
    }

    Tile(Tile const &t)//inlcude all parameters to avoid errors
    {
        book = t.book;
        bookTile = t.bookTile;
        textFont = t.textFont;
        tileColor = t.tileColor;
        bookCover=t.bookCover;
    }

    void SetBook(Book bk)
    {

        book = bk;
    }

    Book GetBook()
    {
        return book;
    }

    Book *GetBookPtr()
    {
        return &book;
    }

    float GetHeight()
    {

        return height;
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

        // cout<<"bookTile.y: "<<bookTile.y;
        //  cout<<" scroll: "<<scroll<<endl;

        Vector2 position = {0, 0};

        // Draw the texture inside the rectangle
        DrawTexturePro(bookCover, (Rectangle){0, 0, (float)bookCover.width, (float)bookCover.height}, bookTile, position, 0.0f, WHITE);
        // DrawTextureRec(bookCover, bookTile, position, WHITE);

        // set text alignment and color
        GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, textColor);
        GuiSetStyle(DEFAULT, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
        // draw tile
        // DrawRectangleRec(bookTile, tileColor);
        // DrawRectangleRounded(bookTile, roundness, segments, tileColor);
        GuiLabelFont((Rectangle){bookTile.x, bookTile.y - 100, bookTile.width, bookTile.height}, book.getTitle().c_str(), textFont, 25, textColor);
        GuiLabelFont((Rectangle){bookTile.x, bookTile.y, bookTile.width, bookTile.height}, book.getAuthor().c_str(), textFont, 25, textColor);
        GuiLabelFont((Rectangle){bookTile.x, bookTile.y + 100, bookTile.width, bookTile.height}, to_string(book.getISBN()).c_str(), textFont, 25, textColor);
    }

    bool isPressed(float scrollOffset)
    {

        Vector2 mousePoint = GetMousePosition();
        bookTile.y += scrollOffset;
        if (CheckCollisionPointRec(mousePoint, bookTile) && (IsMouseButtonDown(MOUSE_LEFT_BUTTON)))
        {
            return true;
        }
        return false;
    }

    bool isHovered(float scrollOffset)
    {
        Vector2 mousePoint = GetMousePosition();
        bookTile.y += scrollOffset;
        if (CheckCollisionPointRec(mousePoint, bookTile))
        {
            DrawRectangleLinesEx(bookTile, 5, DARKGRAY); // Draw container border
            return true;
        }
        return false;
    }
};

#endif