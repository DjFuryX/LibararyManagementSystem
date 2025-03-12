#ifndef REGISTERSCENE_H
#define REGISTERSCENE_H
#include "Scene.h"

class RegisterScene : public Scene
{
private:
    Color headingColor;
    Color subHeadingColor;
    Color textColor;
    Color LoginBoxColor;
    Rectangle loginBox;

    bool usernameTextBox;
    char nameInput[128] = "Please enter name";
    bool passwordTextBox;
    char PasswordInput[128] = "Please enter Password";

    bool backToLogin;

    bool newUser;
    char TemporaryPasword[128] = "-- -- --";

public:
    RegisterScene()
    {
        Scene::backgroundColor = LIGHTGRAY;
        loginBox = {400, 300, 600, 700};
        LoginBoxColor = DARKGRAY;
        usernameTextBox = false;
        passwordTextBox = false;
        backToLogin = false;
        newUser = false;
    }

    void Draw()
    {
        float position = centerPositionHorizontal(1000);
        ClearBackground(backgroundColor);

        loginBox.x = centerPositionHorizontal(loginBox.width);
        DrawRectangleRounded(loginBox, 0.2, 0, Fade(LoginBoxColor, 0.2f));

        GuiLabelFont((Rectangle){position, 100, 1000, 50}, "Welcome to LIBRE", headingFont, 50, 0x686868ff);
        GuiLabelFont((Rectangle){position, 200, 1000, 50}, "A Comprehensive Library Management System", subheadingFont, 40, 0x000000ff);
        GuiLabelFont((Rectangle){position, 300, 1000, 50}, "Registration", textFont, 30, 0x000000ff);

        GuiLabelFont((Rectangle){position - 200, 380, 1000, 50}, "Username", textFont, 25, 0x000000ff);
        GuiSetStyle(DEFAULT, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);
        if (GuiTextBox((Rectangle){centerPositionHorizontal(500), 420, 500, 50}, nameInput, 128, usernameTextBox))
        {
            buttonClear(usernameTextBox, nameInput, (char *)"Please enter name");
        };
       
        GuiSetStyle(DEFAULT, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
        GuiLabelFont((Rectangle){centerPositionHorizontal(500), 500, 500, 50}, "Temporary Password", textFont, 30, 0x000000ff);
        
        GuiSetStyle(DEFAULT, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
        GuiLabelFont((Rectangle){centerPositionHorizontal(500), 550, 500, 50}, TemporaryPasword, textFont, 50, 0x000000ff);
        
        GuiSetStyle(DEFAULT, TEXT_SIZE, 25);
        newUser = GuiButton((Rectangle){centerPositionHorizontal(400), 700, 400, 50}, "Register");

        GuiSetStyle(DEFAULT, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
        GuiButton((Rectangle){centerPositionHorizontal(400), 800, 400, 50}, "Cancel");

        backToLogin = GuiLabelButton((Rectangle){position + 250, 850, 200, 50}, "Back to Login");
    }

    bool LoginButton()
    {
        if (backToLogin == true)
        {
            backToLogin = false;
            return true;
        }
        return backToLogin;
    }

    bool RegisterButton()
    {
        if (newUser == true)
        {
            newUser = false;
            return true;
        }
        return newUser;
    }

    string GetUserNameInput()
    {
        return nameInput;
    }

    void SetTempPasswordText(string text)
    {   
        //cout<<"Text Changed--"<<TemporaryPasword<<" : "<<text<<endl;
        strcpy(TemporaryPasword, text.c_str());
        
    }
};

#endif