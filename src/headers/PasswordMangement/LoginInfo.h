
#ifndef PASSWORD_H
#define PASSWORD_H
#include "sha256/SHA256.h"
#include <iostream>
using namespace std;

class LoginInfo
{
private:
    string username;
    string password;
    static string key;             // key to generate Sha256 Hash of password
    static int tempPasswordlenght; // lenght of password

public:
    // constructors
    LoginInfo()
    {
        username = "Notset";
        password = "Notset";
        
        srand(time(NULL)); // Initialization, should only be called once to get random seed
    };

    LoginInfo(string name)
    {
        username = name;
        password = "Notset";
    }

    LoginInfo(string name, string pass)
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

        password = compute_hash(password + key);
    }

    bool comparePassword(string pass)
    {

        pass = compute_hash(pass + key);

        if (pass == password)
        {
            return true;
        }
        return false;
    }
};

string LoginInfo::key = "One and Only";
int LoginInfo::tempPasswordlenght = 6; // lenght of password
#endif