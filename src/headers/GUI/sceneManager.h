
#include "LoginScene.h"
#include "RegisterScene.h"

class SceneManager
{
private:
    LoginScene *Login;
    RegisterScene *Register;
    Scene *current;
    FileManager filemanager;   // Filemanager to save patron list,statistiscs and book list
    LibraryManagement library; // Library Manager with all list and user classes
    

public:
    SceneManager()
    {
        Login = new LoginScene;
        Register = new RegisterScene;
        current = Login;
    }

    void Draw()
    {

        current->Draw();
    }

    void Update()
    {

        if (current == Login)
        { // On login screen
            if (Login->RegisterButton())
            {
                current = Register;
                // cout << "Register Pressed" << endl;
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

                Patron *newPatron = new Patron(Register->GetUserName());
                string temp;
                
                // TO DO Add check to ensure Username is unique and not

                temp=newPatron->GenerateTempPassword();
                newPatron->SetPassword(temp);

                Register->SetTempPasswordText(temp);

                library.SetUser(newPatron);
                

            }
        }
    }
};