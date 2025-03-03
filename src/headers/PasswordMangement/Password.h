
#ifndef PASSWORD_H
#define PASSWORD_H

#include <iostream>
using namespace std;

/// @brief Handles password creation and encryption
class Password
{
private:
    string username;
    string password;
    static int tempPasswordlenght; // lenght of password
    static int key;            // key to encrypt and decrypt password

public:
    // constructors
    Password()
    {
        username = "Notset";
        password = "Notset";
    };

    Password(string name)
    {
        username = name;
        password = "Notset";
    }

    Password(string name, string pass)
    { // used with admin class only
        username = name;
        password = pass;
    }

    // Accessors
    string GetUsername()
    {
        return username;
    }
    string GetPassword()
    {
        return password;
    }
    // Mutators

    void SetUsername(string name)
    {
        username = name;
    }

    void SetPassword(string pass)
    {
        password = pass;
    }

    string GenerateTemporayPassword()
    {

        string tempPassword; // empty string to store password
        int randomNumber;

        srand(time(NULL)); // Initialization, should only be called once outside of loop to get random seed

        for (int element = 0; element < tempPasswordlenght; element++) // for lenght of password
        {
            if (element < 2)
            {
                randomNumber = GenerateRandomNumber(65, 91); // generate numbers corresponding to A-Z as char
            }
            else if (element < 4)
            {
                randomNumber = GenerateRandomNumber(48, 58); // generate numbers  corresponding to 1-9 as char
            }
            else
            {
                randomNumber = GenerateRandomNumber(97, 123); // generate numbers corresponding to a-b as char
            }
            // creates a temporay password with format AA-11-aa
            tempPassword += char(randomNumber);
        }
        return tempPassword;
    }

    int GenerateRandomNumber(int rand_min, int rand_max)
    {
        // rand_max maximum number that can be generated
        // rand_min minimum number that can be generated
        int randomNumber = rand() % (rand_max - rand_min) + rand_min; // generate random numbers
        return randomNumber;
    }

    void HashPassword()
    {
        string hashPassword;
        int num;
        int remainder;
        int divisions;
        int count = password.length();
        // Traverse the string
        for (int i = 0; i <count; i++)
        {
            num = password[i]; // store character as int

            remainder = num % key; // get the remainder when number is divided by key
            divisions = num / key; // get number of divsions
            cout<<"num: "<<num;
            cout<<" divisions: "<<divisions;
            cout<<" remainder: "<<remainder<<endl;
            // assign new number to string as a character
            // Hashed password should be twice as long
            hashPassword += char(divisions);
            hashPassword += char(remainder);
        }
        // overwritecurrent password with hashPassworded
        password = hashPassword;
    }

    void UnHashPassword()
    {

        string unHashPassword;
        int num;
        int remainder;
        int divisions;
        int count = password.length();
        // Traverse the string
        for (int i = 0; i < count; i+=2)
        {

            divisions = password[i]; // get number of divsions
            remainder = password[i+1]; // get the remainder when number is divided by key
            num = (key*divisions)+remainder; // calculate original number 

            cout<<"num: "<<num;
            cout<<" divisions: "<<divisions;
            cout<<" remainder: "<<remainder<<endl;
            // assign new number to string as a character
            unHashPassword += char(num);
        }
        // cout<<"HashPassword: "<<hashPassword<<endl;
        // overwritecurrent password with hashPassworded
        password = unHashPassword;
    }
};

int Password::tempPasswordlenght = 6;
int Password::key = 65;

#endif