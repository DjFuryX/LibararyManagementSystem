#include "headers/PasswordMangement/Password.h"
#include "headers/User/Admin.h"
#include "headers/LibraryManagement.h"


int main(){

    User *user=new User;

    string username;
    string password;


    cout<<"Please Login to system"<<endl;
    cout<<"Enter username: ";
    cin>>username;
    cout<<"Enter Password: "<<endl;
    cin>>password;

    bool result=user->Login(username,password);

    return 0;
}