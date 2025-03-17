
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

    Rectangle undoBtnBox;
    Texture2D undoBtntexture;

    Rectangle checkoutBtnBox;
    Texture2D checkoutBtnTexture;
    Rectangle sortBtnBox;
    Texture2D sortBtnTexture;

    Rectangle nameBox;

    Rectangle homeBtnBox;
    bool homeBtn;
    Rectangle browseBtnBox;
    bool browseBtn;
    Rectangle LogoutBtnBox;
    bool logOutBtn;

    Rectangle userNameBox;
    Rectangle userIDBox;
    char userNameText[maxInputSize];
    char userIdText[maxInputSize];

    Texture2D background;
    TileList tilelist;

public:
    PatronScene()
    {
        background = LoadTexture("src/resources/images/LibraryAisle.jpg");
        undoBtntexture = LoadTexture("src/resources/images/undo2.png");
        sortBtnTexture = LoadTexture("src/resources/images/sort2.png");
        checkoutBtnTexture = LoadTexture("src/resources/images/checkout1.png");

        GenTextureMipmaps(&undoBtntexture);
        GenTextureMipmaps(&sortBtnTexture);
        GenTextureMipmaps(&checkoutBtnTexture);
        // set texture filter to prevent blurry textures
        SetTextureFilter(undoBtntexture, TEXTURE_FILTER_TRILINEAR);
        SetTextureFilter(sortBtnTexture, TEXTURE_FILTER_TRILINEAR);
        SetTextureFilter(checkoutBtnTexture, TEXTURE_FILTER_TRILINEAR);

        topbar = {0, 0, (float)GetScreenWidth(), 100};
        sideBar = {0, 0, 150, (float)GetScreenHeight()};

        homeBtnBox = {sideBar.x + 5, topbar.y + 100, sideBar.width - 10, topbar.height};
        browseBtnBox = {sideBar.x + 5, homeBtnBox.height + 120, sideBar.width - 10, topbar.height};
        userNameBox = {sideBar.x + 5, homeBtnBox.height + 650, sideBar.width - 10, topbar.height};
        userIDBox = {sideBar.x + 5, homeBtnBox.height + 750, sideBar.width - 10, topbar.height};
        LogoutBtnBox = {sideBar.x + 5, homeBtnBox.height + 850, sideBar.width - 10, topbar.height};

        searchBox = {topbar.x + 1450, topbar.y + 10, topbar.width - 1480, topbar.height - 20};
        nameBox = {topbar.x + 10, topbar.y + 10, 200, topbar.height - 20};
        checkoutBtnBox = {topbar.x + 900, topbar.y + 25, 50, topbar.height - 50};
        undoBtnBox = {checkoutBtnBox.x + 200, topbar.y + 25, 50, topbar.height - 50};
        sortBtnBox = {undoBtnBox.x + 200, topbar.y + 25, 50, topbar.height - 50};

        SearchBoxPressed = false;
        homeBtn = true;
        logOutBtn = false;

        // testing should remove later
        for (int i = 0; i < 30; i++)
        {
            tilelist.insertByAuthor(Book(i + 5000, "Moby Dick", "Norman martin"));
        }
    }

    void Draw()
    {
        GuiSetStyle(DEFAULT, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
        ClearBackground(WHITE);
        DrawTexture(background, 0, 0, WHITE);

        tilelist.DrawList();

        DrawRectangleRec(sideBar, ORANGE);
        DrawRectangleLinesEx(sideBar, 3, BLACK); // Draw container border

        DrawRectangleRec(homeBtnBox, YELLOW);
        GuiSetStyle(DEFAULT, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
        homeBtn = (GuiLabelButton(homeBtnBox, "HOME"));

        DrawRectangleRec(browseBtnBox, YELLOW);
        browseBtn = (GuiLabelButton(browseBtnBox, "BROWSE"));

        DrawRectangleRec(LogoutBtnBox, YELLOW);
        logOutBtn = (GuiLabelButton(LogoutBtnBox, "LOGOUT"));

        GuiLabelFont(userNameBox, userNameText, textFont, 25, ColorToInt(WHITE));
        GuiLabelFont(userIDBox, userIdText, textFont, 25, ColorToInt(RED));

        DrawRectangleRec(topbar, RED);
        DrawRectangleLinesEx(topbar, 3, BLACK); // Draw container border

        GuiSetStyle(DEFAULT, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);
        DrawRectangleRec(searchBox, WHITE);

        // DrawRectangleRec(sortBtnBox, WHITE);
        DrawTexturePro(sortBtnTexture, (Rectangle){0, 0, (float)sortBtnTexture.width, (float)sortBtnTexture.height}, sortBtnBox, Vector2Zero(), 0.0f, WHITE);
        //  DrawRectangleRec(undoBtnBox, WHITE);
        DrawTexturePro(undoBtntexture, (Rectangle){0, 0, (float)undoBtntexture.width, (float)undoBtntexture.height}, undoBtnBox, Vector2Zero(), 0.0f, WHITE);
        // DrawRectangleRec(checkoutBtnBox, WHITE);
        DrawTexturePro(checkoutBtnTexture, (Rectangle){0, 0, (float)checkoutBtnTexture.width, (float)checkoutBtnTexture.height}, checkoutBtnBox, Vector2Zero(), 0.0f, WHITE);

        GuiLabelFont(nameBox, "LIBRE LIBRARY", headingFont, 30, ColorToInt(WHITE));
        GuiSetStyle(DEFAULT, TEXT_SIZE, 25);
        GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(RED));

        if (GuiTextBox(searchBox, SearchInput, maxInputSize, SearchBoxPressed))
        {
            buttonClear(SearchBoxPressed, SearchInput, (char *)"Search..");
        };
    }

    void SetName(string name)
    {
        strcpy(userNameText, name.c_str());
    }

    void SetID(int id)
    {
        if (id == 0)
        {
            strcpy(userIdText, "Not Set"); // testing - change to empty text aftwards
            return;
        }
        strcpy(userIdText, to_string(id).c_str());
    }

    TileList *GetTileList()
    {
        return &tilelist;
    }
};

#endif