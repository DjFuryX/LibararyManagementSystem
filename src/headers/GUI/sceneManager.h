
#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "LoginScene.h"
#include "AdminLogin.h"
#include "RegisterScene.h"
#include "ResetScene.h"
#include "WelcomeScene.h"
#include "PatronScene.h"
#include "AdminScene.h"
#include "PopUp.h"
#include <algorithm>
#include <string>
/**Scene Manager Handles the transition to diffrent scenes and the general flow of the program
 * Main Login Screen
 * Admin Login Screen
 * Register Screen
 * Set password/ reset Screen
 * Welcome Screen
 * Admin Screen // add books, view statistics,view all books and patrons,sort and search
 * Patron Screen // view all books,checkout book, return book,undo,search,sort
 *  **Each Screen inherits from the Scene class thus we use polymorphism to switch the current screen been shown**
 */
class SceneManager
{
private:
    /**All the scenes in  program*/
    LoginScene *patronLogin;
    AdminLoginScene *adminLogin;
    RegisterScene *registerScene;
    ResetScene *reset;
    WelcomeScene *welcome;
    PatronScene *patronScene;
    AdminScene *adminScene;
    PopUp *message;

    Scene *current; // current scene being drawn to screen

    FileManager filemanager;   // Filemanager to save patron list,statistiscs and book list
    LibraryManagement library; // Library Manager with all list and user classes

    Patron newRegister; // for a new register
    Patron *newLogin;   // user already in patron list
    Admin *admin;       // admin user

public:
    SceneManager()
    { // initialise scenes
        patronLogin = new LoginScene;
        registerScene = new RegisterScene;
        welcome = new WelcomeScene;
        patronScene = new PatronScene;
        adminScene = new AdminScene;
        message = new PopUp;
        adminLogin = new AdminLoginScene;
        reset = new ResetScene;
        admin = new Admin;

        // first scene that is shown
        current = patronLogin;
        // read library information from file
        filemanager.ReadData(&library);
    }

    void Draw() // main draw call
    {
        current->Draw(); // draw current screen
        message->Draw(); // show popup message if any
    }

    /**Update function checks if a button is pressed on a certain screen
     * A action is performed based on the current screen and button
     */
    void Update()
    {
        /** Patron Main window with functons such as book checkout and checkin */
        if (current == patronScene)
        {                          // on  user operations screen
            patronScene->Update(); // screen specific updates

            if (patronScene->LogoutBtnPressed()) // if logout button is pressed
            {
                patronLogin = new LoginScene();                     // to clear stuff user already entered
                current = patronLogin;                              // go to patron login scren
                message->ShowPopUp(2, "Logout Successfull", WHITE); // show a message
            }
        }
        /** Admin Main window with functons such as Add book */
        if (current == adminScene)
        { // on Admin operation screen
            adminScene->Update();

            if (adminScene->LogoutBtnPressed()) // if logout button is pressed
            {
                patronLogin = new LoginScene(); // to clear stuff user already entered
                current = patronLogin;          // go to patron login scren
                message->ShowPopUp(2, "Logout Successfull", WHITE);
            }
        }
        /**On Main login screen */
        if (current == patronLogin)
        {
            if (patronLogin->RegisterBtnPressed()) // if register button pressed
            {
                registerScene = new RegisterScene; // create a new register screen
                current = registerScene;           // go to register scene
            }

            if (patronLogin->adminBtnpresed()) // if button to switch to Admin login is pressed
            {
                adminLogin = new AdminLoginScene; // create a new Admin screen
                current = adminLogin;             // go to admin login
            }

            if (patronLogin->ResetBtnPressed()) // if button to reset password is pressed
            {
                reset = new ResetScene; // create a new reset Password screen
                current = reset;        // go to reset screen
            }

            if (patronLogin->passwordBoxpressed() && IsKeyDown(KEY_V) && IsKeyDown(KEY_LEFT_CONTROL)) // if ctrl+v pastes text
            {
                string clipboardText = GetClipboardText(); // get text in clipboard
                /**  get password copied to clipboard if its the temporary password only*/
                if (clipboardText == newRegister.GetLoginInfo()->GetPassword())
                {
                    patronLogin->SetPasswordText(clipboardText); // fill text box with string copied
                }
            }

            if (patronLogin->LoginBtnPressed()) // patronLogin button pressed
            {
                string username = patronLogin->GetNameInput();     // store username entered
                string password = patronLogin->GetPasswordInput(); // store password entered

                /** check if User is a new register
                 *  if username and password matches current user they are registering for the first time
                 */
                if (newRegister.User::Login(username, password)) // only base class can acccept temporary password
                {
                    message->ShowPopUp(2, "Please Set Password", WHITE);
                    // go to scene to set a
                    reset = new ResetScene;
                    reset->SetUsernameText(username); // prefill username text box

                    current = reset; // go to screen to set a permanent password
                }
                /** if useer is not a new register search patron list for user
                 * search patronlist with username
                 * new login is assigned the patron if found
                 */
                else if ((newLogin = library.GetPatronList()->GetPatron(username)) != NULL)
                { // person was found in patron list
                    message->ShowPopUp(2, "User Found", GREEN);
                    // attempt user login
                    if (newLogin->Login(username, password))
                    {
                        message->ShowPopUp(2, "Login  Successfull", GREEN);

                        library.SetUser(newLogin); // set current user to librayry

                        welcome->SetName(username);                   // set text on welcome screen
                        welcome->SetID(newLogin->GetLibraryNumber()); // set id on welcome screen

                        current = welcome; // go to welcome screen
                    }
                    else // show error if password is incorrect
                    {
                        message->ShowPopUp(2, "Incorrect Password", RED);
                    }
                }
                else // if user was not found
                {
                    message->ShowPopUp(2, "User Not found", RED);
                }
            }
            // if cancel button was pressed clear all text on screen
            if (patronLogin->cancelBtnPressed())
            {
            }
        }
        /**On Admin login screen */
        if (current == adminLogin)
        {
            string username = adminLogin->GetNameInput();     // store username entered
            string password = adminLogin->GetPasswordInput(); // store password entered
            // if user pressed button to go to patron login
            if (adminLogin->patronBtnpressed())
            {
                patronLogin = new LoginScene; // to clear stuff user already entered
                current = patronLogin;
            }
            // if user attempts admin login
            if (adminLogin->LoginBtnPressed())
            { /** attempt to login with user input (Admin Admin)  */

                if (admin->Login(username, password))
                {
                    library.SetUser(admin); // set current user to admin

                    welcome = new WelcomeScene();                     // create new welcome screen
                    welcome->SetName(username);                       // set username text on welcome screen
                    welcome->SetID(0);                                // set id on welcome screen - admin has no id
                    message->ShowPopUp(2, "Login succesfull", GREEN); // show message

                    current = welcome; // go to welcome screen
                }
                else // show message if password was incorrect
                {
                    message->ShowPopUp(2, "Login unsuccesfull", RED);
                }
            }
            if (adminLogin->cancelBtnPressed()) // clears text boxes on screen
            {
            }
        }
        /**User is on register scene*/
        if (current == registerScene)
        {
            // user pressed button to go back to login screen
            if (registerScene->LoginBtnPressed())
            {
                patronLogin = new LoginScene; // create new patron login screen
                current = patronLogin;        // go to patron login screen
            }
            // user pressed register button
            if (registerScene->RegisterBtnPressed())
            {
                // ensure user entered a name
                if (registerScene->GetUserNameInput() == "Please enter name")
                {
                    message->ShowPopUp(2, "Please Enter Name", WHITE);
                }
                else
                { /**Registration
                   *new register is a patron object
                   *set username to user input
                   *generate temporary password
                   */
                    newRegister.GetLoginInfo()->SetUsername(registerScene->GetUserNameInput());//set username
                    newRegister.GetLoginInfo()->SetPassword(newRegister.GetLoginInfo()->GenerateTemporayPassword());//set temporay passwrod
                    // show temporary password onscreen
                    registerScene->SetTempPasswordText(newRegister.GetLoginInfo()->GetPassword());
                    message->ShowPopUp(2, "Password Generated", GREEN);//show message onscreen
                }
            }

            /** If user clicks on temporay password and its not a empty string */
            if (registerScene->CopyTempPassword() && (registerScene->GetTempPasswordText() != "-- -- --"))
            {
                // copy the temporary password to the clipboard only if was generated
                SetClipboardText(registerScene->GetTempPasswordText().c_str());

                message->ShowPopUp(2, "Temporary Password copied", WHITE);
            }

            if (registerScene->cancelBtnPressed())
            {
                // clears input box
            }
        }

        /**Set Permanent Password/Reset Screen */
        if (current == reset) // setting or resettting password
        {
            string username = reset->GetNameInput();          // store username entered
            string password = reset->GetPasswordInput();      // store password entered
            string confrimPassword = reset->getConfirmText(); // store password entered

            // if patron library number is equal to zero its a new register
            if (reset->LoginBtnPressed())
            {
                // ensure user entered a name
                if (reset->GetNameInput() == "Please enter name")
                {
                    message->ShowPopUp(2, "Please Enter Name", WHITE);
                }
                // ensure user entered a password
                else if (reset->GetPasswordInput() == "Please enter Password")
                {

                    message->ShowPopUp(2, "Please Enter a Password", WHITE);
                }
                // ensure passwords match
                else if (password != confrimPassword)
                {
                    message->ShowPopUp(2, "Ensure Passwords Match", WHITE);
                }
                else
                {
                    if (library.GetPatronList()->SearchByName(username)) // search patron list for cutomer
                    {
                        /**Password Reset if user was found
                         * Assign password value of user input
                         * Hash password
                         */
                        library.GetPatronList()->GetPatron(username)->GetLoginInfo()->SetPassword(password);
                        library.GetPatronList()->GetPatron(username)->GetLoginInfo()->HashPassword();

                        message->ShowPopUp(2, "Reset Successfull", GREEN); // show popup message

                        patronLogin = new LoginScene; // create new patron scren
                        current = patronLogin;        // got to patron login
                    }
                    else if (newRegister.GetLoginInfo()->GetUsername() == username) // if the user is new
                    {
                        /**Registration
                         * Assign password value of user input
                         * Hash password
                         */
                        newRegister.GetLoginInfo()->SetPassword(password); // set password to user value
                        newRegister.GetLoginInfo()->HashPassword();        // hash password

                        // generate a random library id until a unique one is found
                        do
                        {
                            newRegister.SetLibraryNumber(newRegister.GenerateLibraryID());
                        } while (library.GetPatronList()->SearchByID(newRegister.GetLibraryNumber()));

                        library.GetPatronList()->InsertByLibaryNumber(newRegister); // insert new user into the patron list

                        library.Getstats()->setTotalPatrons(1); // update total patron count

                        message->ShowPopUp(2, "Register Succesfully", GREEN); // show success message

                        patronLogin = new LoginScene; // to clear stuff user already entered
                        current = patronLogin;
                    }
                    else
                    {
                        message->ShowPopUp(2, "User Not found", RED); // show error message
                    }
                }
            }

            if (reset->patronBtnpressed()) // go back to main login screen
            {
                patronLogin = new LoginScene; // to clear stuff user already entered
                current = patronLogin;
            }

            if (reset->cancelBtnPressed()) // clears text boxes
            {
            }
        }

        if (current == welcome) // user has logged in successfully
        {                       // on welcome screen

            if (welcome->ScreenPressed())
            {
                if (library.GetUser() == admin) // if user is admin go to the admin scene
                {
                    adminScene = new AdminScene;

                    adminScene->PopulateBookGrid(&library); // populate books on screen in GUI

                    current = adminScene; // got to admin scene
                }
                else // user is a patron
                {
                    patronScene = new PatronScene;
                    patronScene->SetName(library.GetUser()->GetLoginInfo()->GetUsername()); // show name of current user
                    patronScene->SetID(library.GetUser()->GetLibraryNumber());              // show id of current user
                    patronScene->PopulateBookGrid(&library);                                // populate books on screen in GUI
                    current = patronScene;                                                  // got to patron scene
                }
            }
        }
    }
    ~SceneManager()
    { // save library info
        filemanager.SaveData(library);
    }
};

#endif