
#ifndef LOGINSCENE_H
#define LOGINSCENE_H
#include "Scene.h"
class LoginScene : public Scene
{
protected:
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
    bool adminBtn;
    bool resetBtn;
    bool cancelBtn;

public:
    LoginScene()
    {
        loginBox = {400, 300, 600, 700};
        LoginBoxColor = DARKGRAY;
        usernameTextBox = false;
        passwordTextBox = false;
        registerBtn = false;
        loginBtn = false;
        adminBtn = false;
        resetBtn = false;
        cancelBtn = false;
    }

    void Draw()
    {
        float position = centerPositionHorizontal(1000);
        ClearBackground(backgroundColor);
        DrawTexture(backgroundTexture, 0, 0, WHITE);

        loginBox.x = centerPositionHorizontal(loginBox.width);
        DrawRectangleRounded(loginBox, 0.2, 16, Fade(LoginBoxColor, 0.9f));

        GuiLabelFont((Rectangle){position, 100, 1000, 50}, "Welcome to LIBRE", headingFont, 50, ColorToInt(WHITE));
        GuiLabelFont((Rectangle){position, 200, 1000, 50}, "A Comprehensive Library Management System", subheadingFont, 40, ColorToInt(RAYWHITE));
        GuiLabelFont((Rectangle){position, 300, 1000, 50}, "Please Login to Your Account", textFont, 30, 0x000000ff);

        GuiLabelFont((Rectangle){position - 200, 380, 1000, 50}, "Username", textFont, 25, 0x000000ff);
        DrawRectangleRec(nameBox, WHITE);
        GuiSetStyle(DEFAULT, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);
        
        if (GuiTextBox(nameBox, nameInput, maxInputSize, usernameTextBox))
        {
            buttonClear(usernameTextBox, nameInput, (char *)"Please enter name");
                passwordTextBox =false;
        };

        GuiSetStyle(DEFAULT, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
        GuiLabelFont((Rectangle){position - 200, 500, 1000, 50}, "Password", textFont, 25, 0x000000ff);

        DrawRectangleRec(passwordBox, WHITE);
        GuiSetStyle(DEFAULT, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);

        if (GuiTextBox(passwordBox, PasswordInput, maxInputSize, passwordTextBox))
        {
            buttonClear(passwordTextBox, PasswordInput, (char *)"Please enter Password");
            usernameTextBox = false;

        };

        GuiSetStyle(DEFAULT, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
        loginBtn = GuiButton((Rectangle){centerPositionHorizontal(400), 700, 400, 50}, "Login");

        GuiSetStyle(DEFAULT, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
        cancelBtn = GuiButton((Rectangle){centerPositionHorizontal(400), 800, 400, 50}, "Cancel");

        registerBtn = (GuiLabelButton((Rectangle){position + 250, 850, 200, 50}, "New Then register"));

        resetBtn = GuiLabelButton((Rectangle){position + 240, 900, 200, 50}, "Reset password");

        adminBtn = GuiLabelButton((Rectangle){position + 600, 900, 200, 50}, "Admin Login");
        GuiLabelButton((Rectangle){position + 600, 900, 200, 50}, "__________");
    }

    string GetNameInput()
    {
        return nameInput;
    }

    string GetPasswordInput()
    {
        return PasswordInput;
    }

    void SetUsernameText(string text)
    {
        strcpy(nameInput, text.c_str());
    }
    void SetPasswordText(string text)
    {
        strcpy(PasswordInput, text.c_str());
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
    bool ResetBtnPressed()
    {
        if (resetBtn == true)
        {
            resetBtn = false;
            return true;
        }

        return false;
    }
    // if the password input box is pressed
    bool passwordBoxpressed()
    {
        return passwordTextBox;
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

    bool adminBtnpresed()
    {
        if (adminBtn == true)
        {
            adminBtn = false;
            return true;
        }
        return false;
    }

    virtual bool cancelBtnPressed()
    {
        if (cancelBtn == true)
        {
            strcpy(nameInput, "Please enter name");

            strcpy(PasswordInput, "Please enter Password");

            cancelBtn = false;
            return true;
        }
        return false;
    }
};
#endif