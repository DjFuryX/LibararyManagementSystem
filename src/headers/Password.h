
#ifndef PASSWORD_H
#define PASSWORD_H

#include <iostream>
using namespace std;

/// @brief Handles password creation and encryption
class Password
{
private:
    string username;
    string tempPassword;
    string password;

public:
    Password()
    {
        username = "Notset";
        tempPassword = "Notset";
        password = "Notset";
    };

    Password(string username)
    {
        username = "Notset";
        password = "Notset";
        tempPassword = GenerateTempPassword();
    }

    string GenerateTempPassword()
    {
        int passwordLenght = 5;
        int passwordArray[passwordLenght];
        string tempPassword;

        GenerateRandomNumber(passwordArray, passwordLenght);

        for (int element : passwordArray)
        {
            cout << element << "  ";
            cout << "The letter that corresponds to that value is '"
                 << char(element) << "'\n";
            tempPassword += char(element);
        };

        return tempPassword;
    }

    void GenerateRandomNumber(int num_list[], int passwordLenght)
    {
        int rand_max = 27; // maximum number that can be generated ()
        int rand_min = 1;  // minimum number that can be generated
        srand(time(NULL)); // Initialization, should only be called once to get random seed
        for (int counter = 0; counter < passwordLenght; counter++)
        {                                                                  // index[min] to index[max]
            num_list[counter] = rand() % (rand_max - rand_min) + rand_min; // generate random numbers
        }
    }

    //Testing //Remove Later
    void printAllsCharacter()
    {
        for (int element=0;element<400;element++)
        {
            cout << element << "  ";
            cout << "The letter that corresponds to that value is '"
                 << char(element) << "'\n";
        };
    }
};

#endif