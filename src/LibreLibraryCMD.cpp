#define BCK "\x1b[1F"  // define line clear for console print
#define CYN "\x1B[36m" // define colour yellow for console print
#define YEL "\x1B[33m" // define colour yellow for console print
#define RED "\x1B[31m" // define colour red for console print
#define GRN "\x1B[32m" // define colour green for console print
#define RST "\x1B[0m"  // define colour white for console print
#include <limits>

// testing Remove afterwards

#include "headers/LibraryManagement.h"
#include "src/headers/FileManagement/FileManager.h"

void mainMenu(User *);
void Login(User *);
void Menu();
int GetUserInputInt();
string GetUserInputStr();

int main()
{
  User *user = new User;

  FileManager *filemanager = new FileManager;

  LibraryManagement *library = new LibraryManagement;

  filemanager->ReadData(library);

  library->GetPatronList()->DisplayList();

  mainMenu(user);

  // filemanager.SaveData(*library);

  cout << "GoodbyeClosing application......." << endl; // closing message
  return 0;                                            // 0 indicates that the program terminated successfully
}

void mainMenu(User *userPtr)
{
  Menu();                         // Show menu options
  int option = GetUserInputInt(); // get user option

  while (option != 0)
  { // Start while loop for main menu

    switch (option)
    { // case structure is used to determine option selected
    case 1:
      userPtr = new Patron;
      Login(userPtr);
      break;
    case 2:
      userPtr = new Admin;
      Login(userPtr);
      break;
    default: // if an invalid number is entered
      cout << "Invalid option chosen" << endl;
      break;
    } // end switch case
    Menu();            // get user option
    GetUserInputInt(); // get user option
    system("pause");
  }
}

void Menu()
{
  // Get current date and time
  time_t timestamp;
  time(&timestamp);
  system("cls");
  cout << "Date: " << ctime(&timestamp) << endl; // print current date and time
  // prints a menu so the user can select their desired choice
  cout << GRN "\n\t\t                             Libre                               " RST << endl;
  cout << "\n\t\t +----------------------------+ Please Login +---------------------------+" << endl;
  cout << "  \t\t | " CYN "1." RST "  Patron                                                            |" << endl;
  cout << "\n\t\t | " CYN "2." RST "  Admin                                                             |" << endl;
  cout << "\n\t\t | " CYN "0." RST "  Exit                                                              |" << endl;
  cout << "\t\t +-----------------------------------------------------------------------+" << endl;
  cout << "\nPlease select with the " CYN "digits" RST " on the left:  " << endl; // prompts for user choice
}

void Login(User *user)
{

  cout << "Please Enter Your Credentials: ";
  // user->Login(GetUserInputStr(), GetUserInputStr());
}

int GetUserInputInt()
{
  int option;

  cout << "Please type in a number: ";
  cin >> option;

  if (cin.eof())
  {
    cout << endl;
    return 1;
  }
  else if (cin.fail())
  {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Integer input required. Try again.\n";
  }

  system("cls");
  return option;
}

string GetUserInputStr()
{
  string option;

  cout << "Please type in a String: ";
  cin >> option;

  if (cin.eof())
  {
    cout << endl;
    return string(" ");
  }
  else if (cin.fail())
  {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Integer input required. Try again.\n";
  }

  system("cls");
  return option;
}
