
#include "LoginScene.h"
#include "RegisterScene.h"
#include "WelcomeScene.h"
#include "PatronScene.h"
#include "TileList.h"
#include "PopUp.h"

class SceneManager
{
private:
    //diffrent scenes
    LoginScene *loginScene;
    RegisterScene *Register;
    WelcomeScene *welcome;
    PatronScene *patronScene;
    PopUp *message;

    Scene *current;

    FileManager filemanager;   // Filemanager to save patron list,statistiscs and book list
    LibraryManagement library; // Library Manager with all list and user classes
   
    Patron TempUser;
    //remove later 
    Patron *newLogin;

public:
    SceneManager()
    {
        loginScene = new LoginScene;
        Register = new RegisterScene;
        welcome = new WelcomeScene;
        patronScene = new PatronScene;
        message = new PopUp;
        

        //first scene that is shown 
        current = welcome;

        filemanager.ReadData(&library);
    // library.GetPatronList()->DisplayList();
        ///
    }

    void Draw()
    {

        current->Draw();
        message->Draw();

    }

    void Update()
    {
        if (current == patronScene)
        { // on regular user screen
            patronScene->SetName(library.GetUser()->GetLoginInfo()->GetUsername());//show name of current user
            patronScene->SetID(library.GetUser()->GetLibraryNumber());//show id of current user
            patronScene->SetLibraryPtr(&library);

            if(patronScene->LogoutBtnPressed()){

               // loginScene = new LoginScene(); to clear stuff user already entered
                current = loginScene;
            }

        }

        if (current == loginScene)
        {                                    // On login screen
            if (loginScene->RegisterBtnPressed()) // new register button pressed
            {
                current = Register;
                // cout << "Register Pressed" << endl;
            }

            if (loginScene->LoginBtnPressed())
            { // loginScene button pressed
                string username = loginScene->GetNameInput();
                string password = loginScene->GetPasswordInput();

                // check if user is a new register
                //  if username and password matches current user they are registering for the first time
                if (TempUser.Login(username, password))// acccepts temporary password
                {
                    cout << "Login succesfull contine Registration" << endl;
                    // Permanent password screen 
                }
                // if not a new user search patron list for user
                else if (library.GetPatronList()->SearchByName(username))
                {
                    cout << "User found" << endl;

                    newLogin = library.GetPatronList()->GetPatron(username);

                    if (newLogin != NULL)//person was found in patron list
                    {
                        if (newLogin->Login(username, password))
                        {
                            newLogin->Display();
                            cout << "Login  Successfull" << endl;
                            // library.SetUser();
                            welcome->SetName(username);
                            welcome->SetID(newLogin->GetLibraryNumber());
                            current = welcome;
                        }
                        else
                        {
                            cout << "Incorrect Password" << endl;
                        }
                    }
                }
                else
                {
                    cout << "User Not found" << endl;
                }
            }
        }

        if (current == Register)
        { // On register scene

            if (Register->LoginButton())
            {
                current = loginScene;
                // cout << "back to Login Pressed" << endl;
            }

            if (Register->RegisterButton())
            {

                TempUser.GetLoginInfo()->SetUsername(Register->GetUserNameInput());
                string temp;
                // TO DO Add check to ensure Username is unique and not

                temp = TempUser.GetLoginInfo()->GenerateTemporayPassword();

                TempUser.GetLoginInfo()->SetPassword(temp);

                Register->SetTempPasswordText(temp);
            }

            if(Register->CopyTempPassword()){

             SetClipboardText(Register->GetTempPasswordText());
            }
        }
        if (current == welcome)
        { // on welcome screen

            if (welcome->ScreenPressed())
            {
                current = patronScene;
                cout << "Screen has been pressed" << endl;
            }
        }
    }
};