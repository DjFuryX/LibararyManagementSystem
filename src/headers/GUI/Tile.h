
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
    int textColor;
    float width;
    float height;
    float gap;
    Texture2D bookCover;
    Texture2D checker;
    bool selected;

    Rectangle topbar = {0, 0, 1920, 100};
    Vector2 mousePoint;

public:
    Tile() : book()
    {
        // create a default tile
        bookTile = {0, 0, width, height};
        tileColor = RED;
        width = 300;
        height = 400;
        gap = 50;
        textColor = 0x000000ff;
        selected = false;
    }

    Tile(Book bk) : book(bk)
    {
        // create a default tile
        bookTile = {0, 0, width, height};
        tileColor = RED;
        width = 300;
        height = 400;
        gap = 50;
        textColor = 0x000000ff;
        selected = false;
    }

    Tile(Book bk, Font fn, Texture2D bkTexture, Texture2D bkCheck) : book(bk)
    {
        // create a default tile
        bookTile = {0, 0, width, height};
        tileColor = RED;
        width = 300;
        height = 400;
        gap = 50;
        textColor = 0x000000ff;
        textFont = fn;
        bookCover = bkTexture;
        checker = bkCheck;
        selected = false;
    }

    void SetTextFont(Font txtFont)
    {

        textFont = txtFont;
    }

    void SetBookTexture(Texture2D texture)
    {

        bookCover = texture;
    }

    void SetSelectState(bool isSelected)
    {
        selected = isSelected;
    }

    Tile(float x, float y, float width, float height)
    {
        bookTile = {x, y, width, height};
        tileColor = RED;
        width = 300;
        height = 400;
        gap = 50;
        selected = false;
    }

    Tile(const Tile &t)
    {
        book = t.book;
        bookTile = t.bookTile;
        textFont = t.textFont;
        tileColor = t.tileColor;
        bookCover = t.bookCover;
        checker = t.checker;
        textColor = t.textColor;
        selected = t.selected;
        width = t.width;
        height = t.height;
        gap = t.gap;
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

    bool IsSelected()
    {

        return selected;
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

        // cout<<"bookTile.y: "<<bookTile.y;
        //  cout<<" scroll: "<<scroll<<endl;

        // Draw the texture inside the rectangle
        if (selected)
        {

            DrawTexturePro(bookCover, (Rectangle){0, 0, (float)bookCover.width, (float)bookCover.height}, bookTile, Vector2Zero(), 0.0f, Fade(YELLOW, 0.95));

            DrawTexturePro(checker, (Rectangle){0, 0, (float)checker.width, (float)checker.height},
                           (Rectangle){bookTile.x + 220, bookTile.y + 320, 100, 100}, Vector2Zero(), 0.0f, WHITE);
        }
        else
        {
            DrawTexturePro(bookCover, (Rectangle){0, 0, (float)bookCover.width, (float)bookCover.height}, bookTile, Vector2Zero(), 0.0f, WHITE);
        }
        // cout<<"Is Box Selected: "<<selected<<endl;

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
        // GuiLabelFont((Rectangle){bookTile.x, bookTile.y + 120, bookTile.width, bookTile.height}, to_string(bookTile.y).c_str(), textFont, 25,ColorToInt(RED));
    }

    bool isPressed(float scrollOffset)
    {
        mousePoint = GetMousePosition();
        bookTile.y += scrollOffset;

        if (CheckCollisionPointRec(mousePoint, bookTile))
        {

            if ((IsMouseButtonPressed(MOUSE_LEFT_BUTTON)))
            {

                if (!CheckCollisionPointRec(mousePoint, topbar))
                {
                    selected = !selected;
                    return true;
                }
            }
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