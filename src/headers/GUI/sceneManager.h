
#include "LoginScene.h"
#include "RegisterScene.h"

class SceneManager
{
private:
    LoginScene *Login;
    RegisterScene *Register;
    Scene *current;
    FileManager filemanager;// Filemanager to save patron list,statistiscs and book list
    LibraryManagement library; //Library Manager with all list and user classes

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
        if (Login->RegisterButton())
        {
            current = Register;
           // cout << "Register Pressed" << endl;
        }

      

        if(current==Register){// On register scene

            if (Register->LoginButton())
            {
                current = Login;
               //cout << "back to Login Pressed" << endl;
            }

            if(Register->RegisterButton()){
            
             Patron newPatron(Register->GetUserName());
             newPatron.SetTemporaryPassword();
             
             Register->SetTempPasswordText(newPatron.GetPassword());

            }

        }

    }
};