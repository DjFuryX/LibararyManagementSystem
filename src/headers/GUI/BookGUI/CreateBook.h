#ifndef CREATEBOOK_H
#define CREATEBOOK_H
#include "src/headers/Books/Book.h"
#include "src/headers/GUI/PopUp.h"


class CreateBook:public PopUp
{
private:
    Book book;
    Rectangle box = {500, 200, 1000, 800};
    Color boxColour = MAROON;
    Font textFont;
    char bookTitle[maxInputSize] = "Please Enter Book Title";
    Rectangle bookTitleBox = {box.x+20, box.y+100, 200, 50};
    bool titleBool;

    char bookAuthor[maxInputSize] = "Please Enter Book Author";
    Rectangle bookAuthorBox = {600, 200, 800, 800};  
    char bookIsbn[maxInputSize] = "Please Enter Book ISBN";
    Rectangle bookIsbnBox = {600, 200, 800, 800}; 



public:
    CreateBook() : book()
    {
        textFont = LoadFontEx("src/resources/fonts/Tahoma-Regular-font.ttf", 72, 0, 256);
        GenTextureMipmaps(&textFont.texture);
        SetTextureFilter(textFont.texture, TEXTURE_FILTER_TRILINEAR);
        titleBool = false;
    }
    void Draw()
    {

        DrawRectangleRounded(box,.2, 20, boxColour);

        GuiLabelFont((Rectangle){box.x -200, 380, 1000, 50}, "Book Title", textFont, 25, 0x000000ff);
        DrawRectangleRec(bookTitleBox, WHITE);

        GuiSetStyle(DEFAULT, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);
        if (GuiTextBox(bookTitleBox, bookTitle, maxInputSize, titleBool))
        {
            buttonClear(titleBool, bookTitle, (char *)"Please Enter Book title");
        };
    }
    ~CreateBook()
    {
    }
};

#endif // CREATEBOOK_H
