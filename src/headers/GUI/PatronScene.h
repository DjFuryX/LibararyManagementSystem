
#ifndef PATRONSCENE_H
#define PATRONSCENE_H

#include "Scene.h"
#include "TileList.h"
#include "src/headers/LibraryManagement.h"
class PatronScene : public Scene
{
private:
    LibraryManagement *library;

    bool SearchBoxPressed;
    char SearchInput[maxInputSize] = "Search..";

    Rectangle topbar;
    Rectangle sideBar;
    Rectangle searchBox;

    Rectangle undoBtnBox;
    Texture2D undoBtntexture;
    bool undo;

    Rectangle addToCartBtnBox;
    Texture2D addToCartBtnTexture;
    bool addTocart;

    Rectangle sortBtnBox;
    Texture2D sortBtnTexture;
    bool sort;

    Rectangle nameBox;

    Rectangle libraryBtnBox;
    bool libraryBtn;
    Texture2D librarybtntexture;

    Rectangle myBooksBtnBox;
    bool myBooksBtn;
    Texture2D mybooksBtntexture;

    Rectangle cartBtnBox;
    bool cartBtn;
    Texture2D cartBtntexture;

    Rectangle logoutBtnBox;
    Texture2D logoutBtntexture;
    bool logOutBtn;

    Rectangle userNameBox;
    Rectangle userIDBox;
    char userNameText[maxInputSize];
    char userIdText[maxInputSize];

    Texture2D background;
    TileList tilelist;

    void SetTextures()
    {

        // load default textures
        background = LoadTexture("src/resources/images/LibraryAisle.jpg");
        undoBtntexture = LoadTexture("src/resources/images/undo2.png");
        sortBtnTexture = LoadTexture("src/resources/images/sort1.png");
        addToCartBtnTexture = LoadTexture("src/resources/images/checkout1.png");
        logoutBtntexture = LoadTexture("src/resources/images/logout1.png");
        librarybtntexture = LoadTexture("src/resources/images/library1.png");
        mybooksBtntexture = LoadTexture("src/resources/images/mybook2.png");
        cartBtntexture = LoadTexture("src/resources/images/cart2.png");
        // generate higher quilty textures
        GenTextureMipmaps(&undoBtntexture);
        GenTextureMipmaps(&sortBtnTexture);
        GenTextureMipmaps(&addToCartBtnTexture);
        GenTextureMipmaps(&logoutBtntexture);
        GenTextureMipmaps(&mybooksBtntexture);
        GenTextureMipmaps(&cartBtntexture);
        GenTextureMipmaps(&librarybtntexture);

        // set texture filter to prevent blurry textures
        SetTextureFilter(undoBtntexture, TEXTURE_FILTER_TRILINEAR);
        SetTextureFilter(sortBtnTexture, TEXTURE_FILTER_TRILINEAR);
        SetTextureFilter(addToCartBtnTexture, TEXTURE_FILTER_TRILINEAR);
        SetTextureFilter(logoutBtntexture, TEXTURE_FILTER_TRILINEAR);
        SetTextureFilter(librarybtntexture, TEXTURE_FILTER_TRILINEAR);
        SetTextureFilter(mybooksBtntexture, TEXTURE_FILTER_TRILINEAR);
        SetTextureFilter(cartBtntexture, TEXTURE_FILTER_TRILINEAR);
    }

    void SetRectangles()
    {

        topbar = {0, 0, (float)GetScreenWidth(), 100};
        sideBar = {0, 100, 150, (float)GetScreenHeight()};
        libraryBtnBox = {sideBar.x + 5, topbar.y + 100, sideBar.width - 10, topbar.height};
        myBooksBtnBox = {sideBar.x + 5, libraryBtnBox.height + 120, sideBar.width - 10, topbar.height};
        cartBtnBox = {sideBar.x + 5, myBooksBtnBox.height + 240, sideBar.width - 10, topbar.height};

        userNameBox = {sideBar.x + 5, libraryBtnBox.height + 650, sideBar.width - 10, topbar.height};
        userIDBox = {sideBar.x + 5, libraryBtnBox.height + 750, sideBar.width - 10, topbar.height};
        logoutBtnBox = {sideBar.x + 5, libraryBtnBox.height + 850, sideBar.width - 10, topbar.height};

        searchBox = {topbar.x + 1450, topbar.y + 10, topbar.width - 1480, topbar.height - 20};
        nameBox = {topbar.x + 10, topbar.y + 10, 200, topbar.height - 20};

        addToCartBtnBox = {topbar.x + 400, topbar.y + 25, 250, topbar.height - 50};
        undoBtnBox = {addToCartBtnBox.x + addToCartBtnBox.width + 40, topbar.y + 25, addToCartBtnBox.width, topbar.height - 50};
        sortBtnBox = {undoBtnBox.x + undoBtnBox.width + 200, topbar.y + 25, undoBtnBox.width, topbar.height - 50};
    }

public:
    PatronScene()
    {
        library = NULL;
        SetTextures();
        SetRectangles();

        SearchBoxPressed = false;
        libraryBtn = true;
        cartBtn = false;
        logOutBtn = false;
        undo = false;
        sort = false;

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
        DrawControls();
    }

    void DrawControls()
    {

        DrawRectangleRec(sideBar, Fade(ORANGE, 0.6f));
        DrawRectangleLinesEx(sideBar, 3, BLACK); // Draw container border

        // DrawRectangleRec(libraryBtnBox, YELLOW);
        GuiSetStyle(DEFAULT, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
        libraryBtn = (GuiLabelButton((Rectangle){libraryBtnBox.x + 30, libraryBtnBox.y + 25, libraryBtnBox.width - 10, libraryBtnBox.height - 40}, "Library"));
        DrawTexturePro(librarybtntexture, (Rectangle){0, 0, (float)librarybtntexture.width, (float)librarybtntexture.height},
                       (Rectangle){libraryBtnBox.x, libraryBtnBox.y + 25, libraryBtnBox.width - 90, libraryBtnBox.height - 50}, Vector2Zero(), 0.0f, WHITE);

        // DrawRectangleRec(myBooksBtnBox, YELLOW);
        myBooksBtn = (GuiLabelButton((Rectangle){myBooksBtnBox.x + 25, myBooksBtnBox.y + 25, myBooksBtnBox.width - 10, myBooksBtnBox.height - 40}, "My Books"));
        DrawTexturePro(mybooksBtntexture, (Rectangle){0, 0, (float)mybooksBtntexture.width, (float)mybooksBtntexture.height},
                       (Rectangle){myBooksBtnBox.x - 5, myBooksBtnBox.y + 25, myBooksBtnBox.width - 90, myBooksBtnBox.height - 50}, Vector2Zero(), 0.0f, WHITE);

        // DrawRectangleRec(cartBtnBox, Fade(PINK, 05));
        cartBtn = (GuiLabelButton((Rectangle){cartBtnBox.x + 20, cartBtnBox.y + 25, cartBtnBox.width - 10, cartBtnBox.height - 50}, "Cart"));
        DrawTexturePro(cartBtntexture, (Rectangle){0, 0, (float)cartBtntexture.width, (float)cartBtntexture.height},
                       (Rectangle){cartBtnBox.x + 10, cartBtnBox.y + 25, cartBtnBox.width - 100, cartBtnBox.height - 60}, Vector2Zero(), 0.0f, WHITE);

        // DrawRectangleRec(logoutBtnBox, YELLOW);
        logOutBtn = (GuiLabelButton((Rectangle){logoutBtnBox.x + 30, logoutBtnBox.y + 25, logoutBtnBox.width - 10, logoutBtnBox.height - 50}, "Logout"));
        DrawTexturePro(logoutBtntexture, (Rectangle){0, 0, (float)logoutBtntexture.width, (float)logoutBtntexture.height},
                       (Rectangle){logoutBtnBox.x, logoutBtnBox.y + 25, logoutBtnBox.width - 90, logoutBtnBox.height - 50}, Vector2Zero(), 0.0f, WHITE);

        GuiLabelFont(userNameBox, userNameText, textFont, 25, ColorToInt(WHITE));
        GuiLabelFont(userIDBox, userIdText, textFont, 25, ColorToInt(RED));

        DrawRectangleRec(topbar, Fade(RED, 0.9f));
        DrawRectangleLinesEx(topbar, 3, BLACK); // Draw container border

        GuiSetStyle(DEFAULT, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);
        DrawRectangleRec(searchBox, WHITE);

        GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(BLACK));
        // DrawRectangleRec(addToCartBtnBox, WHITE);
        // DrawRectangleRec((Rectangle){addToCartBtnBox.x + 80, addToCartBtnBox.y, addToCartBtnBox.width -10, addToCartBtnBox.height }, WHITE);
        addTocart = (GuiLabelButton((Rectangle){addToCartBtnBox.x + 60, addToCartBtnBox.y + 10, addToCartBtnBox.width, addToCartBtnBox.height}, "Add To Cart"));

        DrawTexturePro(addToCartBtnTexture, (Rectangle){0, 0, (float)addToCartBtnTexture.width, (float)addToCartBtnTexture.height},
                       (Rectangle){addToCartBtnBox.x, addToCartBtnBox.y, 50, topbar.height - 50}, Vector2Zero(), 0.0f, WHITE);

        // DrawRectangleRec(undoBtnBox, WHITE);
        undo = (GuiLabelButton((Rectangle){undoBtnBox.x + 60, undoBtnBox.y + 10, undoBtnBox.width, undoBtnBox.height}, "Undo Add To Cart"));
        DrawTexturePro(undoBtntexture, (Rectangle){0, 0, (float)undoBtntexture.width, (float)undoBtntexture.height},
                       (Rectangle){undoBtnBox.x, undoBtnBox.y + 10, 50, topbar.height - 60}, Vector2Zero(), 0.0f, WHITE);

        // DrawRectangleRec(sortBtnBox, WHITE);
        sort = (GuiLabelButton((Rectangle){sortBtnBox.x + 60, sortBtnBox.y + 10, sortBtnBox.width, sortBtnBox.height}, "Sort By ISBN"));
        DrawTexturePro(sortBtnTexture, (Rectangle){0, 0, (float)sortBtnTexture.width, (float)sortBtnTexture.height},
                       (Rectangle){sortBtnBox.x, sortBtnBox.y, 50, topbar.height - 50}, Vector2Zero(), 0.0f, WHITE);

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

    void SetLibraryPtr(LibraryManagement *libraryManagement)
    {

        library = libraryManagement;
    }

    bool LogoutBtnPressed()
    {
        if (logOutBtn == true)
        {
            logOutBtn = false;
            return true;
        }
        return false;
    }

    ~PatronScene()
    {
        UnloadTexture(background);
        UnloadTexture(undoBtntexture);
        UnloadTexture(sortBtnTexture);
        UnloadTexture(addToCartBtnTexture);
        UnloadTexture(logoutBtntexture);
        UnloadTexture(librarybtntexture);
        UnloadTexture(mybooksBtntexture);
        UnloadTexture(cartBtntexture);
    }
};

#endif