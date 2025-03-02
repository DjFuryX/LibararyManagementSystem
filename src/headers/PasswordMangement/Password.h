
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

public:
    Password()
    {
        username = "Notset";
        password = "Notset";
    };

    Password(string username)
    {
        username = username;
        password = "Notset";
    }
// Accessors
    string GetUsername(){
        return username;
    }
    string GetPassword(){
        return password;
    }
     // Mutators

    void SetUsername(string name){
        username=name;
     }

    string GenerateTemporayPassword()
    {
        int passwordLenght = 6; // lenght of password
        string tempPassword;  //empty string to store password
        int randomNumber;

        srand(time(NULL));   // Initialization, should only be called once outside of loop to get random seed

        for (int element=0;element<passwordLenght;element++)//for lenght of password
        {
            if(element<2){
                randomNumber=GenerateRandomNumber(65,91);//generate numbers corresponding to A-Z as char 
            }
            else if(element<4){
                randomNumber=GenerateRandomNumber(48,58);//generate numbers  corresponding to 1-9 as char 
            }
            else{
                randomNumber=GenerateRandomNumber(97,123);//generate numbers corresponding to a-b as char 
            }
            //creates a temporay password with format AA-11-aa
            tempPassword += char(randomNumber);
        }
        cout <<"Generated Password: "<<tempPassword<<endl;
        return tempPassword;
    }

    int GenerateRandomNumber( int rand_min,int rand_max)
    {
        // rand_max maximum number that can be generated
        // rand_min minimum number that can be generated
        int randomNumber = rand() % (rand_max - rand_min) + rand_min; // generate random numbers
        return randomNumber;
    }
};

#endif