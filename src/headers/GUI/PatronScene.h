
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
    Texture2D background;
    TileList tilelist;

public:
    PatronScene()
    {
        background = LoadTexture("src/resources/images/LibraryAisle.jpg");

        topbar = {0, 0, (float)GetScreenWidth(), 100};
        sideBar = {0, 0, 150, (float)GetScreenHeight()};
        searchBox = {topbar.x+1450,topbar.y+10,topbar.width-1480,topbar.height-20};

        SearchBoxPressed=false;

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


        DrawRectangleRec(topbar, RED);
        DrawRectangleLinesEx(topbar, 3, BLACK); // Draw container border
        GuiSetStyle(DEFAULT, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);
        DrawRectangleRec(searchBox, WHITE);
        if (GuiTextBox(searchBox, SearchInput, maxInputSize, SearchBoxPressed))
        {
            buttonClear(SearchBoxPressed, SearchInput, (char *)"Search..");

        };
        GuiSetStyle(DEFAULT, TEXT_ALIGNMENT,TEXT_ALIGN_CENTER);
    }

    TileList *GetTileList()
    {
        return &tilelist;
    }
};

#endif