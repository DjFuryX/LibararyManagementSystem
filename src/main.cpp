
#include <raylib.h>

//testing Remove afterwards
#include "./headers/GUI/scene.h"
#include "./headers/GUI/welcomeScene.h"
#include "./headers/PasswordMangement/Password.h"
#include "./headers/User/Admin.h"
#include "./headers/LibraryManagement.h"
#include "./headers/FileManagement/FileManager.h"
int main()
{

// testing patron Sinlge link List
//---------------------------------------------------
PatronLinkList *list = new PatronLinkList;

Patron patron1("Norman");
Patron patron2("Dave");
Patron patron3("Bob");

patron1.SetPassword("Login");


list->InsertByLibaryNumber(patron1);
list->InsertByLibaryNumber(patron2);
list->InsertByLibaryNumber(patron3);

list->DisplayList();

  //testing FileManager

  FileManager filemanager;

  LibraryManagement library;

  library.SetPatronList(*list);

  filemanager.SaveData(library);


// testing admin login
//---------------------------------------------------
   /*  Admin newAdmin;

    string username;
    string password;
    bool result;

    cout<<endl;
   cout<<"User Name: "<<endl;
   cin>> username;
    cout<<"Password: "<<endl;
    cin>>password;

    result = newAdmin.Login(username,password);

    cout<<(result? "Login Succesful" : "Login Failed")<<endl; */
//---------------------------------------------------
// testing password generation
//Password newPassword;
    
    //newPassword.GenerateTemporayPassword();

//---------------------------------------------------
  // testing Binary Search tree
   // create students using primary constructor
   /* Book book1(4, "Moby Dick", "Jane Doe");
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
*/

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