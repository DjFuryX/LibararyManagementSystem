
#ifndef ADMINSCENE_H
#define ADMINSCENE_H

#include "PopUp.h"
#include "TileList.h"
#include "src/headers/LibraryManagement.h"

class AdminScene : public Scene
{
private:
    LibraryManagement *library;
    PopUp message;

    bool SearchBoxPressed;
    char SearchInput[maxInputSize] = "Search By Title..";
    char SearchInputDefault[maxInputSize] = "Search By Title..";
  

    Rectangle topbar;
    Rectangle sideBar;

    Rectangle searchBox;
    Rectangle searchTextBox;
    Rectangle searchBtnBox;
    Rectangle searchCancelBox;
    Texture2D searchIcon;
    Texture2D searchCancel;
    bool search;

    Rectangle sortBtnBox;
    Texture2D sortBtnIcon;
    Texture2D sortBtnIcon1;
    Texture2D sortBtnIcon2;
    bool sort;
    char sortType[maxInputSize] = "Sort By Title";

    Rectangle libraryNameBox;

    Rectangle libraryBtnBox;
    bool libraryBtn;
    Texture2D librarybtnIcon;

    Rectangle showPatronListBox;
    bool patronListBtn;
    Texture2D patronBtnIcon;

    Rectangle addBookBtnBox;
    bool addBookBtn;
    Texture2D addBookBtntIcon;

    Rectangle logoutBtnBox;
    Texture2D logoutBtnIcon;
    bool logOutBtn;

    Rectangle totalBooksBox;
    Rectangle totalPatronsBox;
    Rectangle totalCheckoutsBox;

    Rectangle totalBooksTextBox;
    Rectangle totalPatronsTextBox;
    Rectangle totalCheckoutsTextBox;
    char totalBooks[maxInputSize];
    char totalPatrons[maxInputSize];
    char totalCheckouts[maxInputSize];

    bool listChange;

    Texture2D background;

    TileList libraryList;
    TileList CheckoutList;


    void SetTextures()
    {

        // load default textures
        background = LoadTexture("src/resources/images/LibraryAisle.jpg");

        sortBtnIcon1 = LoadTexture("src/resources/images/sort1.png");
        sortBtnIcon2 = LoadTexture("src/resources/images/sort2.png");
        logoutBtnIcon = LoadTexture("src/resources/images/logout2.png");
        librarybtnIcon = LoadTexture("src/resources/images/library2.png");
        patronBtnIcon = LoadTexture("src/resources/images/user.png");
        addBookBtntIcon = LoadTexture("src/resources/images/addBook.png");
        searchIcon = LoadTexture("src/resources/images/search1.png");
        searchCancel = LoadTexture("src/resources/images/cancel.png");
        sortBtnIcon = sortBtnIcon1;

        // generate higher quilty textures

        GenTextureMipmaps(&sortBtnIcon1);
        GenTextureMipmaps(&sortBtnIcon2);
        GenTextureMipmaps(&logoutBtnIcon);
        GenTextureMipmaps(&patronBtnIcon);
        GenTextureMipmaps(&addBookBtntIcon);
        GenTextureMipmaps(&librarybtnIcon);
        GenTextureMipmaps(&searchIcon);
        GenTextureMipmaps(&searchCancel);

        // set texture filter to prevent blurry textures
        SetTextureFilter(sortBtnIcon1, TEXTURE_FILTER_TRILINEAR);
        SetTextureFilter(sortBtnIcon2, TEXTURE_FILTER_TRILINEAR);
        SetTextureFilter(logoutBtnIcon, TEXTURE_FILTER_TRILINEAR);
        SetTextureFilter(librarybtnIcon, TEXTURE_FILTER_TRILINEAR);
        SetTextureFilter(patronBtnIcon, TEXTURE_FILTER_TRILINEAR);
        SetTextureFilter(addBookBtntIcon, TEXTURE_FILTER_TRILINEAR);
        SetTextureFilter(searchIcon, TEXTURE_FILTER_TRILINEAR);
        SetTextureFilter(searchCancel, TEXTURE_FILTER_TRILINEAR);
    }

    void SetRectangles()
    {

        topbar = {0, 0, (float)GetScreenWidth(), 100};
        sideBar = {0, 100, 150, (float)GetScreenHeight()};
        libraryBtnBox = {sideBar.x + 5, topbar.y + 105, sideBar.width - 10, topbar.height};
        showPatronListBox = {sideBar.x + 5, libraryBtnBox.height + 120, sideBar.width - 10, topbar.height};
        addBookBtnBox = {sideBar.x + 5, showPatronListBox.height + 240, sideBar.width - 10, topbar.height};

        libraryNameBox = {topbar.x + 10, topbar.y + 40, 200, 20};

        totalBooksBox = {topbar.x + 200, topbar.y + 10, 300, 20};
        totalPatronsBox = {topbar.x + 200, topbar.y + 35, 300, 20};
        totalCheckoutsBox = {topbar.x + 200, topbar.y + 60, 300, 20};

        totalBooksTextBox = {topbar.x + 400, topbar.y + 10, 300, 20};
        totalPatronsTextBox = {topbar.x + 400, topbar.y + 35, 300, 20};
        totalCheckoutsTextBox = {topbar.x + 400, topbar.y + 60, 300, 20};

        logoutBtnBox = {sideBar.x + 5, libraryBtnBox.height + 850, sideBar.width - 10, topbar.height};

        searchTextBox = {topbar.x + 1400, topbar.y + 10, topbar.width - 1480, topbar.height - 20};
        searchBtnBox = {searchTextBox.x - 80, searchTextBox.y, 75, topbar.height - 20};
        searchCancelBox = {searchTextBox.x + 450, topbar.y + 25, 50, 50};
        searchBox = {1320, 10, 590, 80};
        sortBtnBox = {1040, 5, 250, 90};
    }

    void AddToLibraryList(BookNode *root) // TO Do Rename to post Order
    {
        if (root == NULL)
        {
            return;
        }

        AddToLibraryList(root->GetLeftNode());
        AddToLibraryList(root->GetRightNode());

       
        libraryList.InsertAtBack(root->GetData());
        
    }



public:
    AdminScene()
    {
        library = NULL;
        SetTextures();
        SetRectangles();

        SearchBoxPressed = false;
        search = false;
        libraryBtn = true;
        addBookBtn = false;
        logOutBtn = false;
        sort = false;
    
    }

    void Draw()
    {

        ClearBackground(WHITE);
        DrawTexture(background, 0, 0, WHITE);

        listChange ? (libraryList.DrawList()) : (CheckoutList.DrawList());

        GuiSetStyle(DEFAULT, TEXT_COLOR_FOCUSED, ColorToInt(BLACK));
        GuiSetStyle(DEFAULT, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
        GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(BLACK));
        DrawControls();
        GuiSetStyle(DEFAULT, TEXT_COLOR_FOCUSED, ColorToInt(SKYBLUE));
    }

    void Update()
    {

        if (isButtonPressed(addBookBtnBox))
        {

          
        }

        if (isButtonPressed(showPatronListBox))
        {
            strcpy(sortType, "Sort By Name");
            
        }

        if (isButtonPressed(libraryBtnBox))
        {
            libraryList.Clear();
            AddToLibraryList(library->GetBookBST()->GetRoot());

            strcpy(sortType, "Sort By Title");
            listChange = true;
        }

        if (isButtonPressed(sortBtnBox) && !search && listChange) // sort books
        {
            sort ? (sortBtnIcon = sortBtnIcon1) : (sortBtnIcon = sortBtnIcon2);

            libraryList.Clear();
            library->GetBookBST()->SortByTitle();
            AddToLibraryList(library->GetBookBST()->GetRoot());
        }

        if (isButtonPressed(sortBtnBox) && !listChange) // sort books
        {
        
        }

        if (isButtonPressed(searchBtnBox) && listChange)
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

                    libraryList.Clear();

                    
                    libraryList.InsertAtBack(temp);
                    
                    message.ShowPopUp(2, "Book Found", GREEN);
                }
                else
                {
                    message.ShowPopUp(2, "Book Not Found", RED);
                }
            }
        }

        if (isButtonPressed(searchBtnBox) && !listChange)
        {
            if (IsSearchEmpty())
            {

                message.ShowPopUp(2, "Search  Box Empty ", RED);
            }
            else if (!search)
            {
                
            }
        }

        if (isButtonPressed(searchCancelBox)) // cancel search
        {

            strcpy(SearchInput, SearchInputDefault);
            search = false;
            Book tempBook;

            libraryList.Clear();

            AddToLibraryList(library->GetBookBST()->GetRoot());
        }

        if (isButtonPressed(searchCancelBox) && !listChange) // cancel search
        {

            strcpy(SearchInput, SearchInputDefault);
     
        }

        if (isButtonPressed(logoutBtnBox))
        { // if logout btn pressed

          
        }
    }

    void DrawControls()
    {

        DrawRectangleRec(sideBar, Fade(ORANGE, 0.6f));
        DrawRectangleLinesEx(sideBar, 3, BLACK); // Draw container border

        // DrawRectangleRec(libraryBtnBox, YELLOW);
        GuiSetStyle(DEFAULT, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
        GuiSetFont(textFont);
        GuiSetStyle(DEFAULT, TEXT_SIZE, 25);

        isHovered(libraryBtnBox);
        libraryBtn = (GuiLabelButton((Rectangle){libraryBtnBox.x + 30, libraryBtnBox.y + 25, libraryBtnBox.width - 10, libraryBtnBox.height - 40}, "Library"));
        DrawTexturePro(librarybtnIcon, (Rectangle){0, 0, (float)librarybtnIcon.width, (float)librarybtnIcon.height},
                       (Rectangle){libraryBtnBox.x, libraryBtnBox.y + 25, libraryBtnBox.width - 90, libraryBtnBox.height - 50}, Vector2Zero(), 0.0f, WHITE);

        // DrawRectangleRec(showPatronListBox, YELLOW);
        isHovered(showPatronListBox);
        patronListBtn = (GuiLabelButton((Rectangle){showPatronListBox.x + 25, showPatronListBox.y + 25, showPatronListBox.width - 10, showPatronListBox.height - 40}, "Patrons"));
        DrawTexturePro(patronBtnIcon, (Rectangle){0, 0, (float)patronBtnIcon.width, (float)patronBtnIcon.height},
                       (Rectangle){5, 245, 40, 40}, Vector2Zero(), 0.0f, WHITE);

        // DrawRectangleRec(logoutBtnBox, YELLOW);
        isHovered(logoutBtnBox);
        logOutBtn = (GuiLabelButton((Rectangle){logoutBtnBox.x + 30, logoutBtnBox.y + 25, logoutBtnBox.width - 10, logoutBtnBox.height - 50}, "Logout"));
        DrawTexturePro(logoutBtnIcon, (Rectangle){0, 0, (float)logoutBtnIcon.width, (float)logoutBtnIcon.height},
                       (Rectangle){logoutBtnBox.x, logoutBtnBox.y + 25, logoutBtnBox.width - 90, logoutBtnBox.height - 50}, Vector2Zero(), 0.0f, WHITE);
        DrawRectangleRec(topbar, Fade(RED, 0.9f));
        DrawRectangleLinesEx(topbar, 3, BLACK); // Draw container border

        DrawRectangleRec(searchTextBox, WHITE);
        GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(BLACK));

        // DrawRectangleRec(addBookBtnBox, Fade(PINK, 05));
        isHovered(addBookBtnBox);
        addBookBtn = (GuiLabelButton((Rectangle){30, 365,130, 50}, "Add Book"));
        DrawTexturePro(addBookBtntIcon, (Rectangle){0, 0, (float)addBookBtntIcon.width, (float)addBookBtntIcon.height},
                       (Rectangle){addBookBtnBox.x, addBookBtnBox.y + 25, 40, 40}, Vector2Zero(), 0.0f, WHITE);

        // DrawRectangleRec(sortBtnBox, WHITE);
        isHovered(sortBtnBox);
        GuiSetStyle(DEFAULT, TEXT_ALIGNMENT, TEXT_ALIGN_MIDDLE);
        GuiToggle((Rectangle){sortBtnBox.x, sortBtnBox.y, sortBtnBox.width, sortBtnBox.height}, sortType, &sort);

        DrawTexturePro(sortBtnIcon, (Rectangle){0, 0, (float)sortBtnIcon.width, (float)sortBtnIcon.height},
                       (Rectangle){sortBtnBox.x, sortBtnBox.y + 15, 50, topbar.height - 50}, Vector2Zero(), 0.0f, WHITE);

        GuiSetStyle(DEFAULT, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);
        GuiLabelFont(libraryNameBox, "LIBRE LIBRARY", headingFont, 30, ColorToInt(WHITE));

        GuiLabelFont(totalBooksBox,"Total Books: ", textFont, 25, ColorToInt(BLACK));
        GuiLabelFont(totalBooksTextBox, totalBooks, textFont, 25, ColorToInt(WHITE));
        GuiLabelFont(totalPatronsBox, "Total Patrons: ", textFont, 25, ColorToInt(BLACK));
        GuiLabelFont(totalPatronsTextBox, totalPatrons, textFont, 25, ColorToInt(WHITE));
        GuiLabelFont(totalCheckoutsBox, "Total Checkouts: ", textFont, 25, ColorToInt(BLACK));
        GuiLabelFont(totalCheckoutsTextBox, totalCheckouts, textFont, 25, ColorToInt(WHITE));

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

    TileList *GetTileList()
    {
        return &libraryList;
    }

    void PopulateBookGrid(LibraryManagement *libraryManagement)
    {
        library = libraryManagement;
        AddToLibraryList(library->GetBookBST()->GetRoot());

        strcpy(totalBooks,to_string( library->Getstats()->getTotalBooks()).c_str());
        strcpy(totalCheckouts,to_string( library->Getstats()->getTotalCurrentCheckouts()).c_str());
        strcpy(totalPatrons,to_string( library->Getstats()->getTotalPatrons()).c_str());
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

    ~AdminScene()
    {
        UnloadTexture(background);
        UnloadTexture(sortBtnIcon);
        UnloadTexture(logoutBtnIcon);
        UnloadTexture(librarybtnIcon);
        UnloadTexture(patronBtnIcon);
        UnloadTexture(addBookBtntIcon);
        UnloadTexture(searchCancel);
    }
};

#endif