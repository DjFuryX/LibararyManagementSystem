
#ifndef PATRONSCENE_H
#define PATRONSCENE_H

#include "Scene.h"
#include "TileList.h"
class PatronScene : public Scene
{
private:
    bool SearchBoxPressed;
    char SearchInput[maxInputSize] = "Search..";

    Rectangle topbar;
    Rectangle sideBar;
    Rectangle searchBox;

    Rectangle UndoBtnBox;
    Rectangle CheckoutBtnBox;
    Rectangle SortBtnBox;


    Rectangle homeBtnBox;
    bool homeBtn;
    Rectangle browseBtnBox;
    bool browseBtn;
    Rectangle LogoutBtnBox;


    Rectangle patronNameBox;
    Rectangle patronIDBox;

    Texture2D background;
    TileList tilelist;
   


public:
    PatronScene()
    {
        background = LoadTexture("src/resources/images/LibraryAisle.jpg");

        topbar = {0, 0, (float)GetScreenWidth(), 100};
        sideBar = {0, 0, 150, (float)GetScreenHeight()};
        homeBtnBox={sideBar.x+5,topbar.y+100,sideBar.width-10,topbar.height};
        browseBtnBox={sideBar.x+5,homeBtnBox.height+120,sideBar.width-10,topbar.height};
        searchBox = {topbar.x + 1450, topbar.y + 10, topbar.width - 1480, topbar.height - 20};

        SearchBoxPressed = false;
        homeBtn = true;

        for (int i = 0; i < 30; i++)
        {
            tilelist.insertByAuthor(Book(i + 5000, "Moby Dick", "Norman martin"));
        }
    }

    void Draw()
    {
        ClearBackground(WHITE);
        DrawTexture(background, 0, 0, WHITE);

        tilelist.DrawList();

        DrawRectangleRec(sideBar, ORANGE);
        DrawRectangleLinesEx(sideBar, 3, BLACK); // Draw container border
       
        DrawRectangleRec(homeBtnBox,YELLOW);
        homeBtn = (GuiLabelButton(homeBtnBox, "HOME"));

        DrawRectangleRec(browseBtnBox,YELLOW);
        browseBtn = (GuiLabelButton(browseBtnBox, "BROWSE"));


        DrawRectangleRec(topbar, RED);
        DrawRectangleLinesEx(topbar, 3, BLACK); // Draw container border
        GuiSetStyle(DEFAULT, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);
        DrawRectangleRec(searchBox, WHITE);
        if (GuiTextBox(searchBox, SearchInput, maxInputSize, SearchBoxPressed))
        {
            buttonClear(SearchBoxPressed, SearchInput, (char *)"Search..");
        };
        GuiSetStyle(DEFAULT, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
    }

    TileList *GetTileList()
    {
        return &tilelist;
    }
};

#endif