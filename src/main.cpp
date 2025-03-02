
#include <raylib.h>
#include "./headers/scene.h"
#include "./headers/welcomeScene.h"
#include "./headers/bookBSt.h"

int main()
{

    // create students using primary constructor
    Book book1(4, "Tom Sayer", "Jane Doe");
    Book book2(1, "The Whale", "John Smith");
    Book book3(10, "Robing Hood", "Jessie Jackson");
    Book book4(400, "Rolling", "Jessie Jackson");
    Book book5(22, "Task Master", "Michael Monrowe");

    // declare an empty linked list using its default constructor
    BookBST *BST = new BookBST;

    BST->InsertBook(book1);  
    BST->InsertBook(book2);
    BST->InsertBook(book3);
    BST->InsertBook(book4);
    BST->InsertBook(book5);

    BST->DisplayInorder();
    
    //BST->DisplayLayers();



    /*  constexpr int screenWidth = 1920;
     constexpr int screenHeight = 1080;
     Image icon = LoadImage("src/resources/images/LibraryManagementSystemIcon.png");

     SetConfigFlags(FLAG_WINDOW_RESIZABLE); // Window configuration flags

     InitWindow(screenWidth, screenHeight, "LIBRE");

     WelcomeScene login;

     SetWindowIcon(icon);
     SetTargetFPS(60);

     while (!WindowShouldClose())
     {
         BeginDrawing();

         login.Draw();

         EndDrawing();
     }
     UnloadImage(icon);
     CloseWindow(); */
}