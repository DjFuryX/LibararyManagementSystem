
// testing Remove afterwards
#include "headers/PasswordMangement/Password.h"
#include "headers/User/Admin.h"
#include "headers/LibraryManagement.h"
#include "headers/FileManagement/FileManager.h"
int main()
{

  // testing patron Sinlge link List
  //---------------------------------------------------
  PatronLinkList *list = new PatronLinkList;

  Patron patron1("Norman");
  Patron patron2("Dave");
  Patron patron3("Bob");

  patron1.SetPassword("Login");
  //hashPassword
  patron1.GetPasswordPtr()->HashPassword();
  cout<<"Hashed Password: "<<patron1.GetPasswordPtr()->GetPassword()<<endl;
  //reverse hashedPassword
  patron1.GetPasswordPtr()->UnHashPassword();
  cout<<"UnHashed Password: "<<patron1.GetPasswordPtr()->GetPassword()<<endl;

  patron1.Display();

  list->InsertByLibaryNumber(patron1);
  list->InsertByLibaryNumber(patron2);
  list->InsertByLibaryNumber(patron3);

  list->DisplayList();

  // testing FileManager

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
  // Password newPassword;

  // newPassword.GenerateTemporayPassword();

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
}