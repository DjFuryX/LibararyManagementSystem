
#include "LoginScene.h"
#include "AdminLogin.h"
#include "RegisterScene.h"
#include "ResetScene.h"
#include "WelcomeScene.h"
#include "PatronScene.h"
#include "TileList.h"
#include "PopUp.h"
#include <algorithm>
#include <string>
class SceneManager
{
private:
    // diffrent scenes
    LoginScene *patronLogin;
    AdminLoginScene *adminLogin;
    RegisterScene *Register;
    ResetScene *reset;
    WelcomeScene *welcome;
    PatronScene *patronScene;
    PopUp *message;

    Scene *current;

    FileManager filemanager;   // Filemanager to save patron list,statistiscs and book list
    LibraryManagement library; // Library Manager with all list and user classes

    Patron newRegister;
    // remove later
    Patron *newLogin;
    Admin *admin;

public:
    SceneManager()
    {
        patronLogin = new LoginScene;
        Register = new RegisterScene;
        welcome = new WelcomeScene;
        patronScene = new PatronScene;
        message = new PopUp;
        adminLogin = new AdminLoginScene;
        reset = new ResetScene;
        admin = new Admin;

        // first scene that is shown
        current = patronLogin;

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
    { // on  user operations screen
        if (current == patronScene)
        {
            patronScene->Update();

            if (patronScene->LogoutBtnPressed())
            {
                patronLogin = new LoginScene(); // to clear stuff user already entered
                current = patronLogin;
                message->ShowPopUp(2, "Logout Successfull", WHITE);
            }
        }
        // On login screen
        if (current == patronLogin)
        { // new register button pressed
            if (patronLogin->RegisterBtnPressed())
            {
                current = Register;
            }

            if (patronLogin->adminBtnpresed())
            {
                adminLogin = new AdminLoginScene; // to clear stuff user already entered
                current = adminLogin;
            }

            if (patronLogin->ResetBtnPressed())
            {
                reset = new ResetScene; // to clear stuff user already entered
                current = reset;
            }

            if (patronLogin->passwordBoxpressed() && IsKeyDown(KEY_V) && IsKeyDown(KEY_LEFT_CONTROL))
            {
                string clipboardText = GetClipboardText();
                if (clipboardText == newRegister.GetLoginInfo()->GetPassword())
                {
                    clipboardText.resize(maxInputSize);
                    patronLogin->SetPasswordText(clipboardText);
                }
            }

            if (patronLogin->LoginBtnPressed())
            {                                                      // patronLogin button pressed
                string username = patronLogin->GetNameInput();     // store username entered
                string password = patronLogin->GetPasswordInput(); // store password entered
                // check if user is a new register
                //  if username and password matches current user they are registering for the first time
                if (newRegister.User::Login(username, password)) // only base can acccept temporary password
                {
                    message->ShowPopUp(2, "Please Set Password", WHITE);

                    // go to scene to set a permananet password;
                    reset = new ResetScene;
                    reset->SetUsernameText(username);
                    current = reset;
                }
                // if not a new user search patron list for user
                else if ((newLogin = library.GetPatronList()->GetPatron(username)) != NULL)
                { // person was found in patron list
                    message->ShowPopUp(2, "User Found", GREEN);

                    if (newLogin->Login(username, password))
                    {
                        message->ShowPopUp(2, "Login  Successfull", GREEN);

                        library.SetUser(newLogin);

                        welcome->SetName(username);
                        welcome->SetID(newLogin->GetLibraryNumber());

                        current = welcome;
                    }
                    else
                    {
                        message->ShowPopUp(2, "Incorrect Password", RED);
                    }
                }
                else
                {
                    message->ShowPopUp(2, "User Not found", RED);
                }
            }
        }

        if (current == adminLogin)
        {
            string username = adminLogin->GetNameInput();     // store username entered
            string password = adminLogin->GetPasswordInput(); // store password entered

            if (adminLogin->patronBtnpressed())
            {
                patronLogin = new LoginScene; // to clear stuff user already entered
                current = patronLogin;
            }

            if (adminLogin->LoginBtnPressed())
            {
                if (admin->Login(username, password))
                {

                    library.SetUser(admin);
                    message->ShowPopUp(2, "Login succesfull", GREEN);
                    welcome->SetName(username);
                    welcome->SetID(0);
                    current = welcome;
                }
                else
                {
                    message->ShowPopUp(2, "Login unsuccesfull", RED);
                }
            }
        }

        if (current == Register)
        { // On register scene

            if (Register->LoginBtnPressed())
            { // user pressed button to go back to login screen
                current = patronLogin;
            }

            if (Register->RegisterBtnPressed())
            { // user pressed register button
                if (Register->GetUserNameInput() == "Please enter name")
                { // ensure user entered a name

                    message->ShowPopUp(2, "Please Enter Name", WHITE);
                }
                else
                {
                    newRegister.GetLoginInfo()->SetUsername(Register->GetUserNameInput());
                    // assign a temporary  to the user
                    newRegister.GetLoginInfo()->SetPassword(newRegister.GetLoginInfo()->GenerateTemporayPassword());
                    // show temporary password onscreen
                    Register->SetTempPasswordText(newRegister.GetLoginInfo()->GetPassword());
                    message->ShowPopUp(2, "Password Generated", GREEN);
                }
            }

            if (Register->CopyTempPassword() && (Register->GetTempPasswordText() != "-- -- --"))
            { // copy the temporary password to the clipboard only if was generated

                SetClipboardText(Register->GetTempPasswordText().c_str());

                message->ShowPopUp(2, "Temporary Password copied", WHITE);
            }
        }

        if (current == reset)
        {
            string username = reset->GetNameInput();          // store username entered
            string password = reset->GetPasswordInput();      // store password entered
            string confrimPassword = reset->getConfirmText(); // store password entered

            // if patron library number is equal to zero its a new register
            if (reset->LoginBtnPressed())
            {
                if (reset->GetNameInput() == "Please enter name")
                { // ensure user entered a name

                    message->ShowPopUp(2, "Please Enter Name", WHITE);
                }
                else if (reset->GetPasswordInput() == "Please enter Password")
                {
                    // ensure user entered a password
                    message->ShowPopUp(2, "Please Enter a Password", WHITE);
                }
                else if (password != confrimPassword)
                {
                    // ensure passwords match
                    message->ShowPopUp(2, "Ensure Passwords Match", WHITE);
                }
                else
                {
                    if (library.GetPatronList()->SearchByName(username))
                    {

                        library.GetPatronList()->GetPatron(username)->GetLoginInfo()->SetPassword(password);
                        library.GetPatronList()->GetPatron(username)->GetLoginInfo()->HashPassword();

                        message->ShowPopUp(2, "Reset Successfull", GREEN);
                        patronLogin = new LoginScene; // to clear stuff user already entered
                        current = patronLogin;
                    }
                    else if (newRegister.GetLoginInfo()->GetUsername() == username)
                    {
                        newRegister.GetLoginInfo()->SetPassword(password);
                        newRegister.GetLoginInfo()->HashPassword();

                        while (library.GetPatronList()->SearchByID(newRegister.GetLibraryNumber()))
                        {
                            // generate a random library id until a unique one is found
                            newRegister.SetLibraryNumber(newRegister.GenerateLibraryID());
                        }

                        library.GetPatronList()->InsertByLibaryNumber(newRegister);

                        message->ShowPopUp(2, "Register Succesfully", GREEN);

                        patronLogin = new LoginScene; // to clear stuff user already entered
                        current = patronLogin;
                    }
                    else
                    {
                        message->ShowPopUp(2, "User Not found", RED);
                    }
                }
            }

            if (reset->patronBtnpressed())
            {
                patronLogin = new LoginScene; // to clear stuff user already entered
                current = patronLogin;
            }
        }

        if (current == welcome)
        { // on welcome screen

            if (welcome->ScreenPressed())
            {
                if (library.GetUser() == admin)
                {
                    // got to admin scene
                }
                else
                {
                    patronScene->SetName(library.GetUser()->GetLoginInfo()->GetUsername()); // show name of current user
                    patronScene->SetID(library.GetUser()->GetLibraryNumber());              // show id of current user
                    patronScene->PopulateBookGrid(&library);

                    current = patronScene;
                }
            }
        }
    }
    ~SceneManager()
    {
        // save libray info
        cout << "Files saved" << endl;
        // filemanager.SaveData(library);
    }
};