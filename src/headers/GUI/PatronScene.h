
#ifndef PATRONSCENE_H
#define PATRONSCENE_H

#include "PopUp.h"
#include "TileList.h"
#include "src/headers/LibraryManagement.h"

class PatronScene : public Scene
{
private:
    LibraryManagement *library;
    PopUp message;

    bool SearchBoxPressed;
    char SearchInput[maxInputSize] = "Search..";
    char SearchInputDefault[maxInputSize] = "Search..";

    Rectangle topbar;
    Rectangle sideBar;

    Rectangle searchBox;
    Rectangle searchTextBox;
    Rectangle searchBtnBox;
    Rectangle searchCancelBox;
    Texture2D searchIcon;
    Texture2D searchCancel;
    bool search;

    Rectangle undoBtnBox;
    Texture2D undoBtntexture;
    bool undo;

    Rectangle addToCartBtnBox;
    Texture2D addToCartBtnTexture;
    bool addTocart;

    Rectangle sortBtnBox;
    Texture2D sortBtnTexture;
    Texture2D sortBtnTexture1;
    Texture2D sortBtnTexture2;
    bool sort;
    bool sortPressed;

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

    BookBST *selectedBooks;

    void SetTextures()
    {

        // load default textures
        background = LoadTexture("src/resources/images/LibraryAisle.jpg");
        undoBtntexture = LoadTexture("src/resources/images/undo2.png");
        sortBtnTexture1 = LoadTexture("src/resources/images/sort1.png");
        sortBtnTexture2 = LoadTexture("src/resources/images/sort2.png");
        addToCartBtnTexture = LoadTexture("src/resources/images/checkout1.png");
        logoutBtntexture = LoadTexture("src/resources/images/logout1.png");
        librarybtntexture = LoadTexture("src/resources/images/library1.png");
        mybooksBtntexture = LoadTexture("src/resources/images/mybook2.png");
        cartBtntexture = LoadTexture("src/resources/images/cart2.png");
        searchIcon = LoadTexture("src/resources/images/search1.png");
        searchCancel = LoadTexture("src/resources/images/cancel.png");

        sortBtnTexture = sortBtnTexture1;

        // generate higher quilty textures
        GenTextureMipmaps(&undoBtntexture);
        GenTextureMipmaps(&sortBtnTexture);
        GenTextureMipmaps(&addToCartBtnTexture);
        GenTextureMipmaps(&logoutBtntexture);
        GenTextureMipmaps(&mybooksBtntexture);
        GenTextureMipmaps(&cartBtntexture);
        GenTextureMipmaps(&librarybtntexture);
        GenTextureMipmaps(&searchIcon);
        GenTextureMipmaps(&searchCancel);

        // set texture filter to prevent blurry textures
        SetTextureFilter(undoBtntexture, TEXTURE_FILTER_TRILINEAR);
        SetTextureFilter(sortBtnTexture, TEXTURE_FILTER_TRILINEAR);
        SetTextureFilter(addToCartBtnTexture, TEXTURE_FILTER_TRILINEAR);
        SetTextureFilter(logoutBtntexture, TEXTURE_FILTER_TRILINEAR);
        SetTextureFilter(librarybtntexture, TEXTURE_FILTER_TRILINEAR);
        SetTextureFilter(mybooksBtntexture, TEXTURE_FILTER_TRILINEAR);
        SetTextureFilter(cartBtntexture, TEXTURE_FILTER_TRILINEAR);
        SetTextureFilter(searchIcon, TEXTURE_FILTER_TRILINEAR);
        SetTextureFilter(searchCancel, TEXTURE_FILTER_TRILINEAR);
    }

    void SetRectangles()
    {

        topbar = {0, 0, (float)GetScreenWidth(), 100};
        sideBar = {0, 100, 150, (float)GetScreenHeight()};
        libraryBtnBox = {sideBar.x + 5, topbar.y + 105, sideBar.width - 10, topbar.height};
        myBooksBtnBox = {sideBar.x + 5, libraryBtnBox.height + 120, sideBar.width - 10, topbar.height};
        cartBtnBox = {sideBar.x + 5, myBooksBtnBox.height + 240, sideBar.width - 10, topbar.height};

        userNameBox = {sideBar.x + 5, libraryBtnBox.height + 650, sideBar.width - 10, topbar.height};
        userIDBox = {sideBar.x + 5, libraryBtnBox.height + 750, sideBar.width - 10, topbar.height};
        logoutBtnBox = {sideBar.x + 5, libraryBtnBox.height + 850, sideBar.width - 10, topbar.height};

        searchTextBox = {topbar.x + 1400, topbar.y + 10, topbar.width - 1480, topbar.height - 20};
        searchBtnBox = {searchTextBox.x - 80, searchTextBox.y, 75, topbar.height - 20};
        searchCancelBox = {searchTextBox.x + 450, topbar.y + 25, 50, 50};
        searchBox = {1320, 10, 590, 80};
    
        nameBox = {topbar.x + 10, topbar.y + 10, 200, topbar.height - 20};

        addToCartBtnBox = {topbar.x + 400, topbar.y + 5, 250, topbar.height - 10};
        undoBtnBox = {addToCartBtnBox.x + addToCartBtnBox.width + 40, topbar.y + 5, addToCartBtnBox.width, topbar.height - 10};
        sortBtnBox = {undoBtnBox.x + undoBtnBox.width + 100, topbar.y + 5, undoBtnBox.width, topbar.height - 10};
    }

    // Function to travese Binary search tree in Post Order and add to GUI List
    void inorder(BookNode *root)
    {
        if (root == NULL)
        {
            return;
        }

        inorder(root->GetLeftNode());
        inorder(root->GetRightNode());

        if (selectedBooks->SearchByTitle(root->GetData().getTitle()) != NULL)
        {
            tilelist.InsertAtBack(root->GetData(), true);
        }
        else
        {
            tilelist.InsertAtBack(root->GetData());
        }
    }

    void addBackBooks(BookNode *root, Book book)
    {
        if (root == NULL)
        {
            return;
        }
        addBackBooks(root->GetLeftNode(), book);
        addBackBooks(root->GetRightNode(), book);

        if (root->GetData().getISBN() != book.getISBN())
        {

            selectedBooks->InsertBook(root->GetData());
        }
    }

public:
    PatronScene()
    {
        library = NULL;
        SetTextures();
        SetRectangles();

        SearchBoxPressed = false;
        search = false;
        libraryBtn = true;
        cartBtn = false;
        logOutBtn = false;
        undo = false;
        sort = false;
        sortPressed = false;
        selectedBooks = new BookBST;
        // add books to gui
    }

    void Draw()
    {

        ClearBackground(WHITE);
        DrawTexture(background, 0, 0, WHITE);

        tilelist.DrawList();
        GuiSetStyle(DEFAULT, TEXT_COLOR_FOCUSED, ColorToInt(BLACK));
        GuiSetStyle(DEFAULT, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
        GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(BLACK));
        DrawControls();
        GuiSetStyle(DEFAULT, TEXT_COLOR_FOCUSED, DEFAULT);
    }

    void Update()
    {


        if(isButtonPressed(addToCartBtnBox)){// add to cart is pressed

    

        }

        if (isButtonPressed(sortBtnBox) && !search) // sort books
        {
            sort ? (sortBtnTexture = sortBtnTexture1) : (sortBtnTexture = sortBtnTexture2);

            library->GetBookBST()->SortByTitle();
            selectedBooks = tilelist.Clear();
            inorder(library->GetBookBST()->GetRoot());

            selectedBooks = new BookBST;
        }

        if (isButtonPressed(searchBtnBox))
        { // search books

            if (IsSearchEmpty())
            {

                message.ShowPopUp(2, "Search  Box Empty ", RED);
            }
            else if (!search)
            {
                Book *temp = library->GetBookBST()->SearchByTitle(SearchInput);

                if (temp != NULL)
                {
                    search = true;

                    selectedBooks = tilelist.Clear();

                    if (selectedBooks->SearchByTitle(SearchInput) != NULL)
                    {
                        tilelist.InsertAtBack(temp, true);
                    }
                    else
                    {
                        tilelist.InsertAtBack(temp);
                    }
                    message.ShowPopUp(2, "Book Found", GREEN);
                }
                else
                {
                    message.ShowPopUp(2, "Book Not Found", RED);
                }
            }
        }

        if (isButtonPressed(searchCancelBox))//cancel search
        {

            strcpy(SearchInput, SearchInputDefault);
            search = false;
            BookBST *temp = new BookBST;
            Book tempBook;

            temp = selectedBooks;

            if (!tilelist.GetHead()->GetData().IsSelected())
            {

                tempBook = tilelist.GetHead()->GetData().GetBook();
            }

            selectedBooks = tilelist.Clear();

            addBackBooks(temp->GetRoot(), tempBook);

            inorder(library->GetBookBST()->GetRoot());

            selectedBooks = new BookBST;
        }
    }


    void DrawControls()
    {

        DrawRectangleRec(sideBar, Fade(ORANGE, 0.6f));
        DrawRectangleLinesEx(sideBar, 3, BLACK); // Draw container border

        // DrawRectangleRec(libraryBtnBox, YELLOW);
        GuiSetStyle(DEFAULT, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
        isHovered(libraryBtnBox);
        libraryBtn = (GuiLabelButton((Rectangle){libraryBtnBox.x + 30, libraryBtnBox.y + 25, libraryBtnBox.width - 10, libraryBtnBox.height - 40}, "Library"));
        DrawTexturePro(librarybtntexture, (Rectangle){0, 0, (float)librarybtntexture.width, (float)librarybtntexture.height},
                       (Rectangle){libraryBtnBox.x, libraryBtnBox.y + 25, libraryBtnBox.width - 90, libraryBtnBox.height - 50}, Vector2Zero(), 0.0f, WHITE);

        // DrawRectangleRec(myBooksBtnBox, YELLOW);
        isHovered(myBooksBtnBox);
        myBooksBtn = (GuiLabelButton((Rectangle){myBooksBtnBox.x + 25, myBooksBtnBox.y + 25, myBooksBtnBox.width - 10, myBooksBtnBox.height - 40}, "My Books"));
        DrawTexturePro(mybooksBtntexture, (Rectangle){0, 0, (float)mybooksBtntexture.width, (float)mybooksBtntexture.height},
                       (Rectangle){myBooksBtnBox.x - 5, myBooksBtnBox.y + 25, myBooksBtnBox.width - 90, myBooksBtnBox.height - 50}, Vector2Zero(), 0.0f, WHITE);

        // DrawRectangleRec(cartBtnBox, Fade(PINK, 05));
        isHovered(cartBtnBox);
        cartBtn = (GuiLabelButton((Rectangle){cartBtnBox.x + 20, cartBtnBox.y + 25, cartBtnBox.width - 10, cartBtnBox.height - 50}, "Cart"));
        DrawTexturePro(cartBtntexture, (Rectangle){0, 0, (float)cartBtntexture.width, (float)cartBtntexture.height},
                       (Rectangle){cartBtnBox.x + 10, cartBtnBox.y + 25, cartBtnBox.width - 100, cartBtnBox.height - 60}, Vector2Zero(), 0.0f, WHITE);

        // DrawRectangleRec(logoutBtnBox, YELLOW);
        isHovered(logoutBtnBox);
        logOutBtn = (GuiLabelButton((Rectangle){logoutBtnBox.x + 30, logoutBtnBox.y + 25, logoutBtnBox.width - 10, logoutBtnBox.height - 50}, "Logout"));
        DrawTexturePro(logoutBtntexture, (Rectangle){0, 0, (float)logoutBtntexture.width, (float)logoutBtntexture.height},
                       (Rectangle){logoutBtnBox.x, logoutBtnBox.y + 25, logoutBtnBox.width - 90, logoutBtnBox.height - 50}, Vector2Zero(), 0.0f, WHITE);

        GuiLabelFont(userNameBox, userNameText, textFont, 25, ColorToInt(WHITE));
        GuiLabelFont(userIDBox, userIdText, textFont, 25, ColorToInt(RED));

        DrawRectangleRec(topbar, Fade(RED, 0.9f));
        DrawRectangleLinesEx(topbar, 3, BLACK); // Draw container border

        GuiSetStyle(DEFAULT, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);
        DrawRectangleRec(searchTextBox, WHITE);

        GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(BLACK));
        // DrawRectangleRec(addToCartBtnBox, WHITE);
        isHovered(addToCartBtnBox);
        // DrawRectangleRec((Rectangle){addToCartBtnBox.x + 80, addToCartBtnBox.y, addToCartBtnBox.width -10, addToCartBtnBox.height }, WHITE);
        addTocart = (GuiLabelButton((Rectangle){addToCartBtnBox.x + 60, addToCartBtnBox.y, addToCartBtnBox.width, addToCartBtnBox.height}, "Add To Cart"));

        DrawTexturePro(addToCartBtnTexture, (Rectangle){0, 0, (float)addToCartBtnTexture.width, (float)addToCartBtnTexture.height},
                       (Rectangle){addToCartBtnBox.x, addToCartBtnBox.y + 5, 50, topbar.height - 50}, Vector2Zero(), 0.0f, WHITE);

        // DrawRectangleRec(undoBtnBox, WHITE);
        isHovered(undoBtnBox);
        undo = (GuiLabelButton((Rectangle){undoBtnBox.x + 60, undoBtnBox.y, undoBtnBox.width, undoBtnBox.height}, "Undo Add To Cart"));
        DrawTexturePro(undoBtntexture, (Rectangle){0, 0, (float)undoBtntexture.width, (float)undoBtntexture.height},
                       (Rectangle){undoBtnBox.x, undoBtnBox.y + 15, 50, topbar.height - 60}, Vector2Zero(), 0.0f, WHITE);
        // DrawRectangleRec(sortBtnBox, WHITE);
        isHovered(sortBtnBox);
        GuiSetStyle(DEFAULT, TEXT_ALIGNMENT, TEXT_ALIGN_MIDDLE);

        GuiToggle((Rectangle){sortBtnBox.x, sortBtnBox.y, sortBtnBox.width, sortBtnBox.height}, "Sort By Title", &sort);
        
        DrawTexturePro(sortBtnTexture, (Rectangle){0, 0, (float)sortBtnTexture.width, (float)sortBtnTexture.height},
                       (Rectangle){sortBtnBox.x, sortBtnBox.y + 15, 50, topbar.height - 50}, Vector2Zero(), 0.0f, WHITE);

        GuiSetStyle(DEFAULT, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);
        GuiLabelFont(nameBox, "LIBRE LIBRARY", headingFont, 30, ColorToInt(WHITE));
        GuiSetStyle(DEFAULT, TEXT_SIZE, 25);
        GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(RED));

        isHovered(searchBox);
        DrawTexturePro(searchIcon, (Rectangle){0, 0, (float)searchIcon.width, (float)searchIcon.height},
                       (Rectangle){searchBtnBox.x + 15, searchBtnBox.y + 12, searchBtnBox.width - 25, searchBtnBox.height - 30}, Vector2Zero(), 0.0f, WHITE);

        DrawTexturePro(searchCancel, (Rectangle){0, 0, (float)searchCancel.width, (float)searchCancel.height},
                       searchCancelBox, Vector2Zero(), 0.0f, WHITE);

        if (GuiTextBox(searchTextBox, SearchInput, maxInputSize, SearchBoxPressed))
        {
            buttonClear(SearchBoxPressed, SearchInput, SearchInputDefault);
        };

        message.Draw();
    }

    bool IsSearchEmpty()
    {

        return strcmp(SearchInput, SearchInputDefault) == 0;
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

    void PopulateBookGrid(LibraryManagement *libraryManagement)
    {
        library = libraryManagement;
        inorder(library->GetBookBST()->GetRoot());
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
        UnloadTexture(searchCancel);
    }
};

#endif