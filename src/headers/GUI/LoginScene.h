
#ifndef LOGINSCENE_H
#define LOGINSCENE_H
#include "Scene.h"
class LoginScene : public Scene
{
private:
    Color headingColor;
    Color subHeadingColor;
    Color textColor;
    Color LoginBoxColor;
    Rectangle loginBox;

    bool usernameTextBox;
    char nameInput[maxInputSize] = "Please enter name";
    bool passwordTextBox;
    char PasswordInput[maxInputSize] = "Please enter Password";
    bool registerBtn;
    bool loginBtn;

public:
    LoginScene()
    {
        Scene::backgroundColor = LIGHTGRAY;
        loginBox = {400, 300, 600, 700};
        LoginBoxColor = DARKGRAY;
        usernameTextBox = false;
        passwordTextBox = false;
        registerBtn = false;
        loginBtn=false;
    }

    void Draw()
    {
        float position = centerPositionHorizontal(1000);
        ClearBackground(backgroundColor);

        loginBox.x = centerPositionHorizontal(loginBox.width);
        DrawRectangleRounded(loginBox, 0.2, 0, Fade(LoginBoxColor, 0.2f));

        GuiLabelFont((Rectangle){position, 100, 1000, 50}, "Welcome to LIBRE", headingFont, 50, 0x686868ff);
        GuiLabelFont((Rectangle){position, 200, 1000, 50}, "A Comprehensive Library Management System", subheadingFont, 40, 0x000000ff);
        GuiLabelFont((Rectangle){position, 300, 1000, 50}, "Please Login to Your Account", textFont, 30, 0x000000ff);

        GuiLabelFont((Rectangle){position - 200, 380, 1000, 50}, "Username", textFont, 25, 0x000000ff);
        GuiSetStyle(DEFAULT, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);
        if (GuiTextBox((Rectangle){centerPositionHorizontal(500), 420, 500, 50}, nameInput, maxInputSize,usernameTextBox))
        {
            buttonClear(usernameTextBox, nameInput, (char *)"Please enter name");
        };
        GuiSetStyle(DEFAULT, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
        GuiLabelFont((Rectangle){position - 200, 500, 1000, 50}, "Password", textFont, 25, 0x000000ff);
        GuiSetStyle(DEFAULT, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);
        if (GuiTextBox((Rectangle){centerPositionHorizontal(500), 540, 500, 50}, PasswordInput, maxInputSize, passwordTextBox))
        {
            buttonClear(passwordTextBox, PasswordInput, (char *)"Please enter Password");
        };

        GuiSetStyle(DEFAULT, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
        loginBtn = GuiButton((Rectangle){centerPositionHorizontal(400), 700, 400, 50}, "Login");

        GuiSetStyle(DEFAULT, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
        GuiButton((Rectangle){centerPositionHorizontal(400), 800, 400, 50}, "Cancel");

        registerBtn = (GuiLabelButton((Rectangle){position + 250, 850, 200, 50}, "New Then register"));

        GuiLabelButton((Rectangle){position + 240, 900, 200, 50}, "Reset password");
    }


    string GetNameInput(){

        return nameInput;
    }

    string GetPasswordInput(){
        
        return PasswordInput;
    }

    bool RegisterBtnPressed()
    {
        if (registerBtn == true)
        {
            registerBtn = false;
            return true;
        }

        return false;
    }

    bool LoginBtnPressed()
    {
        if (loginBtn == true)
        {
            loginBtn = false;
            return true;
        }
        return false;
    }
};
#endif