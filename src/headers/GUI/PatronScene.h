
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

    char stackCount[maxInputSize] = "";

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
    Texture2D undoBtnIcon;
    bool undo;

    Rectangle addToCartBtnBox;
    Texture2D addToCartBtnIcon;
    Texture2D returnBtnIcon;
    bool addTocart;

    Rectangle sortBtnBox;
    Texture2D sortBtnIcon;
    Texture2D sortBtnIcon1;
    Texture2D sortBtnIcon2;
    bool sort;

    Rectangle nameBox;

    Rectangle libraryBtnBox;
    bool libraryBtn;
    Texture2D librarybtnIcon;

    Rectangle myBooksBtnBox;
    bool myBooksBtn;
    Texture2D mybooksBtnIcon;

    Rectangle confirmBtnBox;
    bool confirmBtn;
    Texture2D confirmBtntIcon;

    Rectangle logoutBtnBox;
    Texture2D logoutBtnIcon;
    bool logOutBtn;

    Rectangle userNameBox;
    Rectangle userIDBox;
    char userNameText[maxInputSize];
    char userIdText[maxInputSize];

    bool stackOptions;

    Texture2D background;

    TileList libraryList;
    TileList CheckoutList;

    BookBST *selectedBooks;

    void SetTextures()
    {

        // load default textures
        background = LoadTexture("src/resources/images/LibraryAisle.jpg");
        undoBtnIcon = LoadTexture("src/resources/images/undo1.png");
        sortBtnIcon1 = LoadTexture("src/resources/images/sort1.png");
        sortBtnIcon2 = LoadTexture("src/resources/images/sort2.png");
        addToCartBtnIcon = LoadTexture("src/resources/images/checkout.png");
        returnBtnIcon = LoadTexture("src/resources/images/return.png");
        logoutBtnIcon = LoadTexture("src/resources/images/logout2.png");
        librarybtnIcon = LoadTexture("src/resources/images/library2.png");
        mybooksBtnIcon = LoadTexture("src/resources/images/mybook1.png");
        confirmBtntIcon = LoadTexture("src/resources/images/cart1.png");
        searchIcon = LoadTexture("src/resources/images/search1.png");
        searchCancel = LoadTexture("src/resources/images/cancel.png");

        sortBtnIcon = sortBtnIcon1;

        // generate higher quilty textures
        GenTextureMipmaps(&undoBtnIcon);
        GenTextureMipmaps(&sortBtnIcon);
        GenTextureMipmaps(&addToCartBtnIcon);
        GenTextureMipmaps(&logoutBtnIcon);
        GenTextureMipmaps(&mybooksBtnIcon);
        GenTextureMipmaps(&confirmBtntIcon);
        GenTextureMipmaps(&librarybtnIcon);
        GenTextureMipmaps(&searchIcon);
        GenTextureMipmaps(&searchCancel);
        GenTextureMipmaps(&returnBtnIcon);

        // set texture filter to prevent blurry textures
        SetTextureFilter(undoBtnIcon, TEXTURE_FILTER_TRILINEAR);
        SetTextureFilter(sortBtnIcon, TEXTURE_FILTER_TRILINEAR);
        SetTextureFilter(addToCartBtnIcon, TEXTURE_FILTER_TRILINEAR);
        SetTextureFilter(logoutBtnIcon, TEXTURE_FILTER_TRILINEAR);
        SetTextureFilter(librarybtnIcon, TEXTURE_FILTER_TRILINEAR);
        SetTextureFilter(mybooksBtnIcon, TEXTURE_FILTER_TRILINEAR);
        SetTextureFilter(confirmBtntIcon, TEXTURE_FILTER_TRILINEAR);
        SetTextureFilter(searchIcon, TEXTURE_FILTER_TRILINEAR);
        SetTextureFilter(searchCancel, TEXTURE_FILTER_TRILINEAR);
        SetTextureFilter(returnBtnIcon, TEXTURE_FILTER_BILINEAR);
    }

    void SetRectangles()
    {

        topbar = {0, 0, (float)GetScreenWidth(), 100};
        sideBar = {0, 100, 150, (float)GetScreenHeight()};
        libraryBtnBox = {sideBar.x + 5, topbar.y + 105, sideBar.width - 10, topbar.height};
        myBooksBtnBox = {sideBar.x + 5, libraryBtnBox.height + 120, sideBar.width - 10, topbar.height};
        confirmBtnBox = {sideBar.x + 5, myBooksBtnBox.height + 240, sideBar.width - 10, topbar.height};

        nameBox = {topbar.x + 10, topbar.y + 10, 200, 20};
        userNameBox = {topbar.x + 10, topbar.y + 40, 100, 20};
        userIDBox = {topbar.x + 10, topbar.y + 60, 100, 20};

        logoutBtnBox = {sideBar.x + 5, libraryBtnBox.height + 850, sideBar.width - 10, topbar.height};

        searchTextBox = {topbar.x + 1400, topbar.y + 10, topbar.width - 1480, topbar.height - 20};
        searchBtnBox = {searchTextBox.x - 80, searchTextBox.y, 75, topbar.height - 20};
        searchCancelBox = {searchTextBox.x + 450, topbar.y + 25, 50, 50};
        searchBox = {1320, 10, 590, 80};

        addToCartBtnBox = {topbar.x + 400, topbar.y + 5, 250, topbar.height - 10};
        undoBtnBox = {addToCartBtnBox.x + addToCartBtnBox.width + 40, topbar.y + 5, addToCartBtnBox.width, topbar.height - 10};
        sortBtnBox = {undoBtnBox.x + undoBtnBox.width + 100, topbar.y + 5, undoBtnBox.width, topbar.height - 10};
    }

    void AddToLibraryList(BookNode *root) // TO Do Rename to post Order
    {
        if (root == NULL)
        {
            return;
        }

        AddToLibraryList(root->GetLeftNode());
        AddToLibraryList(root->GetRightNode());

        if (selectedBooks->SearchByTitle(root->GetData().getTitle()) != NULL)
        {
            libraryList.InsertAtBack(root->GetData(), true);
        }
        else
        {
            libraryList.InsertAtBack(root->GetData());
        }
    }

    void PopulateCheckoutList() // TO Do Rename to post Order
    {
        BookQueue *tempQueue = new BookQueue;

        BookQueue *userQueue = library->GetUser()->GetUserQueue();

        CheckoutList.Clear();

        while (userQueue->GetFront() != NULL)
        {

            tempQueue->Enqueue(userQueue->Dequeue());

            CheckoutList.InsertAtBack(tempQueue->GetRearBook());
        }
        while (tempQueue->GetFront() != NULL)
        {
            userQueue->Enqueue(tempQueue->Dequeue());
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

    void updateBookRentee(BookNode *root, int isbn, int UserId)
    {
        if (root == NULL)
        {
            return;
        }

        updateBookRentee(root->GetLeftNode(), isbn, UserId);

        updateBookRentee(root->GetRightNode(), isbn, UserId);

        if (root->GetData().getISBN() == isbn)
        {
            root->GetDataPtr()->SetRenteeID(UserId);
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
        confirmBtn = false;
        logOutBtn = false;
        undo = false;
        sort = false;
        stackOptions = true;
        selectedBooks = new BookBST;
        // add books to gui
    }

    void Draw()
    {

        ClearBackground(WHITE);
        DrawTexture(background, 0, 0, WHITE);

        stackOptions ? (libraryList.DrawList()) : (CheckoutList.DrawList());

        GuiSetStyle(DEFAULT, TEXT_COLOR_FOCUSED, ColorToInt(BLACK));
        GuiSetStyle(DEFAULT, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
        GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(BLACK));
        DrawControls();
        GuiSetStyle(DEFAULT, TEXT_COLOR_FOCUSED, ColorToInt(SKYBLUE));
    }

    void Update()
    {

        if (isButtonPressed(addToCartBtnBox) && stackOptions)
        { // add to cart is pressed

            TileNode *curr = libraryList.GetHead(); // point curr to the first element in the list.

            while (curr != NULL) // while curr is pointing to a valid node
            {
                if (curr->GetDataPtr()->IsSelected() && (curr->GetDataPtr()->GetBook().getRenteeID() == 0))
                {
                    curr->GetDataPtr()->GetBookPtr()->SetRenteeID(library->GetUser()->GetLibraryNumber());
                    curr->GetDataPtr()->SetSelectState(false);
                    library->GetBookStack()->push(curr->GetDataPtr()->GetBook());

                    updateBookRentee(library->GetBookBST()->GetRoot(), curr->GetData().GetBook().getISBN(), library->GetUser()->GetLibraryNumber());
                }
                curr = curr->GetNextNode(); // point curr to IT'S next node
            }
            // update stack count
            SetStackCount();
        }

        if (isButtonPressed(confirmBtnBox) && stackOptions)
        {

            Book temp;
            while (library->GetBookStack()->GetTop() != NULL)
            {
                temp = library->GetBookStack()->pop();

                library->GetUser()->CheckinBook(temp);
            }
            // update stack count
            SetStackCount();
        }

        if (isButtonPressed(addToCartBtnBox) && !stackOptions)
        {

            Book temp = library->GetUser()->GetUserQueue()->Dequeue();

            TileNode *curr = CheckoutList.GetHead(); // point curr to the first element in the list.

            while (curr != NULL) // while curr is pointing to a valid node
            {
                if (curr->GetDataPtr()->GetBook().getISBN() == temp.getISBN())
                {
                    curr->GetDataPtr()->GetBookPtr()->SetRenteeID(0);
                }
                curr = curr->GetNextNode(); // point curr to IT'S next node
            }

            CheckoutList.DeleteANode(temp.getISBN());
            CheckoutList.CaculateTilePosition();
        }

        if (isButtonPressed(myBooksBtnBox) && stackOptions)
        {
            PopulateCheckoutList();
            stackOptions = false;
        }

        if (isButtonPressed(libraryBtnBox))
        {
            libraryList.Clear();
            AddToLibraryList(library->GetBookBST()->GetRoot());

            stackOptions = true;
        }

        if (isButtonPressed(undoBtnBox) && stackOptions)
        {

            Book temp = library->GetBookStack()->pop();
            updateBookRentee(library->GetBookBST()->GetRoot(), temp.getISBN(), 0);

            TileNode *curr = libraryList.GetHead(); // point curr to the first element in the list.

            while (curr != NULL) // while curr is pointing to a valid node
            {
                if (curr->GetDataPtr()->GetBook().getISBN() == temp.getISBN())
                {
                    curr->GetDataPtr()->GetBookPtr()->SetRenteeID(0);
                }
                curr = curr->GetNextNode(); // point curr to IT'S next node
            }
            // update stack count
            SetStackCount();
        }

        if (isButtonPressed(sortBtnBox) && !search) // sort books
        {
            sort ? (sortBtnIcon = sortBtnIcon1) : (sortBtnIcon = sortBtnIcon2);

            library->GetBookBST()->SortByTitle();
            selectedBooks = libraryList.Clear();
            AddToLibraryList(library->GetBookBST()->GetRoot());

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

                    selectedBooks = libraryList.Clear();

                    if (selectedBooks->SearchByTitle(SearchInput) != NULL)
                    {
                        libraryList.InsertAtBack(temp, true);
                    }
                    else
                    {
                        libraryList.InsertAtBack(temp);
                    }
                    message.ShowPopUp(2, "Book Found", GREEN);
                }
                else
                {
                    message.ShowPopUp(2, "Book Not Found", RED);
                }
            }
        }

        if (isButtonPressed(searchCancelBox)) // cancel search
        {

            strcpy(SearchInput, SearchInputDefault);
            search = false;
            BookBST *temp = new BookBST;
            Book tempBook;

            temp = selectedBooks;

            if (!libraryList.GetHead()->GetData().IsSelected())
            {

                tempBook = libraryList.GetHead()->GetData().GetBook();
            }

            selectedBooks = libraryList.Clear();

            addBackBooks(temp->GetRoot(), tempBook);

            AddToLibraryList(library->GetBookBST()->GetRoot());

            selectedBooks = new BookBST;
        }

        if (isButtonPressed(logoutBtnBox))
        { // if logout btn pressed

            // clear book stack
            Book temp;
            while (library->GetBookStack()->GetTop() != NULL)
            {
                temp = library->GetBookStack()->pop();
                updateBookRentee(library->GetBookBST()->GetRoot(), temp.getISBN(), 0);
            }
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

        // DrawRectangleRec(myBooksBtnBox, YELLOW);
        isHovered(myBooksBtnBox);
        myBooksBtn = (GuiLabelButton((Rectangle){myBooksBtnBox.x + 25, myBooksBtnBox.y + 25, myBooksBtnBox.width - 10, myBooksBtnBox.height - 40}, "My Books"));
        DrawTexturePro(mybooksBtnIcon, (Rectangle){0, 0, (float)mybooksBtnIcon.width, (float)mybooksBtnIcon.height},
                       (Rectangle){myBooksBtnBox.x - 5, myBooksBtnBox.y + 25, myBooksBtnBox.width - 90, myBooksBtnBox.height - 50}, Vector2Zero(), 0.0f, WHITE);

        // DrawRectangleRec(logoutBtnBox, YELLOW);
        isHovered(logoutBtnBox);
        logOutBtn = (GuiLabelButton((Rectangle){logoutBtnBox.x + 30, logoutBtnBox.y + 25, logoutBtnBox.width - 10, logoutBtnBox.height - 50}, "Logout"));
        DrawTexturePro(logoutBtnIcon, (Rectangle){0, 0, (float)logoutBtnIcon.width, (float)logoutBtnIcon.height},
                       (Rectangle){logoutBtnBox.x, logoutBtnBox.y + 25, logoutBtnBox.width - 90, logoutBtnBox.height - 50}, Vector2Zero(), 0.0f, WHITE);
        DrawRectangleRec(topbar, Fade(RED, 0.9f));
        DrawRectangleLinesEx(topbar, 3, BLACK); // Draw container border

        DrawRectangleRec(searchTextBox, WHITE);
        GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(BLACK));

        if (stackOptions)
        { // DrawRectangleRec(confirmBtnBox, Fade(PINK, 05));
            isHovered(confirmBtnBox);
            confirmBtn = (GuiLabelButton((Rectangle){confirmBtnBox.x + 20, confirmBtnBox.y + 25, confirmBtnBox.width - 10, confirmBtnBox.height - 50}, "Confirm"));
            DrawTexturePro(confirmBtntIcon, (Rectangle){0, 0, (float)confirmBtntIcon.width, (float)confirmBtntIcon.height},
                           (Rectangle){confirmBtnBox.x, confirmBtnBox.y + 25, 40, 40}, Vector2Zero(), 0.0f, WHITE);

            GuiSetStyle(DEFAULT, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);
            // DrawRectangleRec(addToCartBtnBox, WHITE);
            isHovered(addToCartBtnBox);
            // DrawRectangleRec((Rectangle){addToCartBtnBox.x + 80, addToCartBtnBox.y, addToCartBtnBox.width -10, addToCartBtnBox.height }, WHITE);
            addTocart = (GuiLabelButton((Rectangle){addToCartBtnBox.x + 60, addToCartBtnBox.y, addToCartBtnBox.width, addToCartBtnBox.height}, "Checkout"));

            DrawTexturePro(addToCartBtnIcon, (Rectangle){0, 0, (float)addToCartBtnIcon.width, (float)addToCartBtnIcon.height},
                           (Rectangle){addToCartBtnBox.x, addToCartBtnBox.y + 15, 50, topbar.height - 50}, Vector2Zero(), 0.0f, WHITE);

            // DrawRectangleRec(undoBtnBox, WHITE);
            isHovered(undoBtnBox);
            undo = (GuiLabelButton((Rectangle){undoBtnBox.x + 60, undoBtnBox.y, undoBtnBox.width, undoBtnBox.height}, "Undo Checkout"));
            DrawTexturePro(undoBtnIcon, (Rectangle){0, 0, (float)undoBtnIcon.width, (float)undoBtnIcon.height},
                           (Rectangle){undoBtnBox.x, undoBtnBox.y + 20, 50, topbar.height - 60}, Vector2Zero(), 0.0f, WHITE);
            GuiLabel((Rectangle){undoBtnBox.x + 210, undoBtnBox.y + 10, 50, topbar.height - 60}, stackCount);
        }
        else
        {

            GuiSetStyle(DEFAULT, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);
            // DrawRectangleRec(addToCartBtnBox, WHITE);
            isHovered(addToCartBtnBox);
            // DrawRectangleRec((Rectangle){addToCartBtnBox.x + 80, addToCartBtnBox.y, addToCartBtnBox.width -10, addToCartBtnBox.height }, WHITE);
            addTocart = (GuiLabelButton((Rectangle){addToCartBtnBox.x + 60, addToCartBtnBox.y, addToCartBtnBox.width, addToCartBtnBox.height}, "Check In Book"));
            DrawTexturePro(returnBtnIcon, (Rectangle){0, 0, (float)returnBtnIcon.width, (float)returnBtnIcon.height},
                           (Rectangle){addToCartBtnBox.x, addToCartBtnBox.y + 15, 50, topbar.height - 50}, Vector2Zero(), 0.0f, WHITE);
        }

        // DrawRectangleRec(sortBtnBox, WHITE);
        isHovered(sortBtnBox);
        GuiSetStyle(DEFAULT, TEXT_ALIGNMENT, TEXT_ALIGN_MIDDLE);
        GuiToggle((Rectangle){sortBtnBox.x, sortBtnBox.y, sortBtnBox.width, sortBtnBox.height}, "Sort By Title", &sort);

        DrawTexturePro(sortBtnIcon, (Rectangle){0, 0, (float)sortBtnIcon.width, (float)sortBtnIcon.height},
                       (Rectangle){sortBtnBox.x, sortBtnBox.y + 15, 50, topbar.height - 50}, Vector2Zero(), 0.0f, WHITE);

        GuiSetStyle(DEFAULT, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);
        GuiLabelFont(nameBox, "LIBRE LIBRARY", headingFont, 30, ColorToInt(WHITE));

        GuiLabelFont(userNameBox, userNameText, textFont, 25, ColorToInt(BLACK));
        GuiLabelFont(userIDBox, userIdText, textFont, 25, ColorToInt(BLACK));

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

    void SetStackCount()
    {
        int count = library->GetBookStack()->GetTotalBooks();

        (count == 0) ? (strcpy(stackCount, "")) : (strcpy(stackCount, to_string(count).c_str()));
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
        return &libraryList;
    }

    void PopulateBookGrid(LibraryManagement *libraryManagement)
    {
        library = libraryManagement;
        AddToLibraryList(library->GetBookBST()->GetRoot());
        
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
        UnloadTexture(undoBtnIcon);
        UnloadTexture(sortBtnIcon);
        UnloadTexture(addToCartBtnIcon);
        UnloadTexture(logoutBtnIcon);
        UnloadTexture(librarybtnIcon);
        UnloadTexture(mybooksBtnIcon);
        UnloadTexture(confirmBtntIcon);
        UnloadTexture(searchCancel);
    }
};

#endif