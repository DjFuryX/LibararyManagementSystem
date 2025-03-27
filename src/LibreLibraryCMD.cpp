

#include "headers/LibraryManagement.h"
#include "src/headers/FileManagement/FileManager.h"

int main()
{
  User *user = new User;

  FileManager *filemanager = new FileManager;

  LibraryManagement *library = new LibraryManagement;

  BookQueue queue;

  Book book1("Tom Sawyer", "Mark Twain", 40002302);
  Book book2("Huckleberry Finn", "Mark Twain", 50005401);

  // queue.enqueue(book1);
  // queue.enqueue(book2);

  // queue.displayQueue();

  // library->GetBookBST()->InsertBook(book1);
  //  library->GetBookBST()->InsertBook(book2);

  // filemanager->SaveData(*library);

  filemanager->ReadData(library);

  library->GetBookBST()->DisplayInorder();
  library->GetPatronList()->DisplayList();

  // filemanager.SaveData(*library);

  cout << "GoodbyeClosing application......." << endl; // closing message
  return 0;
}
