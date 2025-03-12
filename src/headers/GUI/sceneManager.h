
#include "LoginScene.h"
#include "RegisterScene.h"
#include "WelcomeScene.h"
#include "PatronScene.h"

class SceneManager
{
private:
    LoginScene *Login;
    RegisterScene *Register;
    WelcomeScene *welcome;
    PatronScene *patronScene;
    Scene *current;
    FileManager filemanager;   // Filemanager to save patron list,statistiscs and book list
    LibraryManagement library; // Library Manager with all list and user classes
    Patron TempUser;
    Patron *newLogin;

public:
    SceneManager()
    {
        Login = new LoginScene;
        Register = new RegisterScene;
        welcome = new WelcomeScene;
        patronScene = new PatronScene;

        current = Login;
        filemanager.ReadData(&library);
        library.GetPatronList()->DisplayList();
        ///
    }

    void Draw()
    {

        current->Draw();
    }

    void Update()
    {

        if (current == Login)
        {                                    // On login screen
            if (Login->RegisterBtnPressed()) // new register button pressed
            {
                current = Register;
                // cout << "Register Pressed" << endl;
            }

            if (Login->LoginBtnPressed())
            { // Login button pressed
                string username = Login->GetNameInput();
                string password = Login->GetPasswordInput();

                // check if user is a new register
                //  if username and password matches current user they are registering for the first time
                if (TempUser.Login(username, password))
                {
                    cout << "Login succesfull contine Registration" << endl;
                }
                // if not a new user search patron list for user
                else if (library.GetPatronList()->SearchByName(username))
                {
                    cout << "User found" << endl;

                    newLogin = library.GetPatronList()->GetPatron(username);

                    if (newLogin != NULL)
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
                current = Login;
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
        }

        if (current == welcome)
        { // on welcome screen

            if (welcome->ScreenPressed())
            {
                current=patronScene;
                cout << "Screen has been pressed" << endl;
            }
        }
    }
};