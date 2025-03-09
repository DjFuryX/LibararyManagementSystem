
#define BCK "\x1b[1F"  // define line clear for console print
#define CYN "\x1B[36m" // define colour yellow for console print
#define YEL "\x1B[33m" // define colour yellow for console print
#define RED "\x1B[31m" // define colour red for console print
#define GRN "\x1B[32m" // define colour green for console print
#define RST "\x1B[0m"  // define colour white for console print
#include <limits>
#include <iostream>

using namespace std;
class Menu
{
private:
    int option;

public:
    void Display()
    {
        int choice;
        // Get current date and time
        time_t timestamp;
        time(&timestamp);
        system("cls");  // clears the screen
        cout << "Date: "<< ctime(&timestamp) << endl; // print current date and time
         /*prints a menu so the user can select their desired choice*/
        cout << GRN "\n\t\t                             Libre                               " RST << endl;
        cout << "\n\t\t +----------------------------+ Please Login +---------------------------+" << endl;
        cout << "  \t\t | " CYN "1." RST "  Patron                                                            |" << endl;
        cout << "\n\t\t | " CYN "2." RST "  Admin                                                             |" << endl;
        cout << "\n\t\t | " CYN "0." RST "  Exit                                                              |" << endl;
        cout << "\t\t +-----------------------------------------------------------------------+" << endl;
        cout << "\nPlease select with the " CYN "digits" RST " on the left:  " << endl; // prompts for user choice
        GetInput(option);
        system("cls");
        // clears the screen
    }

    int GetOption(int option)
    {
    }

    int GetInput(int letter)
    {

        while (1)
        {
            std::cout << "Please type in a number: ";
            std::cin >> letter;

            if (std::cin.eof())
            {
                std::cout << std::endl;
                return 1;
            }
            else if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Integer input required. Try again.\n";
            }
            else if (letter < 1 || letter > 26)
            {
                std::cout << "The English alphabet only has 26 letters. Try again.\n";
            }
            else
            {
                break;
            }
        }

        return option;
    }
};