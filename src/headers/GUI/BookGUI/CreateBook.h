#ifndef CREATEBOOK_H
#define CREATEBOOK_H
#include "src/headers/Books/Book.h"
#include "src/headers/GUI/PopUp.h"

class CreateBook : public PopUp
{
private:
    Book book;
    Rectangle box = {800, 200, 500, 700};
    Color boxColour = MAROON;

    char bookTitle[maxInputSize] = "Please Enter Book Title";
    Rectangle bookTitleBox = {box.x + 20, box.y + 150, 450, 50};
    bool titleBool;

    char bookAuthor[maxInputSize] = "Please Enter Book Author";
    Rectangle bookAuthorBox = {box.x + 20, box.y + 300, 450, 50};
    bool authorBool;
    char bookIsbn[maxInputSize] = "Please Enter Book ISBN";
    Rectangle bookIsbnBox = {box.x + 20, box.y + 450, 450, 50};
    Rectangle cancelBox = {box.x + 430, box.y + 10, 40, 40};
    bool IsbnBool;
    bool saveBtn;
    bool cancelBtn;
    Texture2D cancelIcon;
    LibraryManagement *library;

public:
    CreateBook() : book()
    {
        titleBool = false;
        authorBool = false;
        IsbnBool = false;
        saveBtn = false;
        cancelBtn = false;
        cancelIcon = LoadTexture("src/resources/images/cancel.png");
        GenTextureMipmaps(&cancelIcon);
        SetTextureFilter(cancelIcon, TEXTURE_FILTER_TRILINEAR);
    }
    void Draw()
    {
        DrawRectangleRounded(box,0.2, 20, Fade(RED,0.9));

        GuiLabelFont((Rectangle){850, box.y + 40, 400}, "Create Book", headingFont, 30, ColorToInt(BLACK));

        GuiLabelFont((Rectangle){box.x + 20, box.y + 100, 400, 50}, "Enter Book Title", textFont, 25, ColorToInt(BLACK));
        DrawRectangleRec(bookTitleBox, WHITE);

        GuiSetStyle(DEFAULT, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);
        if (GuiTextBox(bookTitleBox, bookTitle, maxInputSize, titleBool))
        {
            buttonClear(titleBool, bookTitle, (char *)"Please Enter Book Title");
        };

        GuiLabelFont((Rectangle){box.x + 20, box.y + 250, 400, 50}, "Enter Book Author", textFont, 25, ColorToInt(BLACK));
        DrawRectangleRec(bookAuthorBox, WHITE);
        GuiSetStyle(DEFAULT, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);
        if (GuiTextBox(bookAuthorBox, bookAuthor, maxInputSize, authorBool))
        {
            buttonClear(authorBool, bookAuthor, (char *)"Please Enter Book Author");
        };

        GuiLabelFont((Rectangle){box.x + 20, box.y + 400, 400, 50}, "Enter Book ISBN", textFont, 25, ColorToInt(BLACK));
        DrawRectangleRec(bookIsbnBox, WHITE);

        GuiSetStyle(DEFAULT, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);
        if (GuiTextBox(bookIsbnBox, bookIsbn, maxInputSize, IsbnBool))
        {
            buttonClear(IsbnBool, bookIsbn, (char *)"Please Enter Book ISBN");
        };
        GuiSetStyle(DEFAULT, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
        saveBtn = GuiButton((Rectangle){box.x + 50, box.y + 600, 400, 50}, "Save");

        // draw cancel icon
        DrawTexturePro(cancelIcon, (Rectangle){0, 0, (float)cancelIcon.width, (float)cancelIcon.height},
                       cancelBox, Vector2Zero(), 0.0f, WHITE);
    }

    Book *GetNewBook()
    {
        Book *temp = NULL;
        if (InputValid())
        {

            int isbn = stoi(bookIsbn);
            temp = new Book(bookTitle, bookAuthor, isbn);
        }

        return temp;
    }

    Rectangle Cancel()
    {

        return cancelBox;
    }

    bool Save()
    {
        return saveBtn;
    }


    bool InputValid()
    {

        if (strcmp("Please Enter Book Title", bookTitle) == 0)
        {
            return false;
        }
        if (strcmp("Please Enter Book Author", bookAuthor) == 0)
        {
            return false;
        }
        if (strcmp("Please Enter Book ISBN", bookIsbn) == 0)
        {
            return false;
        }

        if (!IsbnVaild())
        {
            return false;
        }

        return true;
    }

    bool IsbnVaild()
    {

        for (int i = 0; i < maxInputSize; i++)
        {
            if (bookIsbn[i] == '\0')
            {
                return true;
            }
            if (isdigit(bookIsbn[i]) == false)
            {

                return false;
            }
        }

        return true;
    }

    ~CreateBook()
    {
    }
};

#endif // CREATEBOOK_H
