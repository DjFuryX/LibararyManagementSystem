
#ifndef ADMINLOGIN_H
#define ADMINLOGIN_H
#include "LoginScene.h"

class AdminLoginScene : public LoginScene
{
private:
    bool patronBtn;

public:
    AdminLoginScene():LoginScene()
    {
    }

    void Draw()
    {
        float position = centerPositionHorizontal(1000);
        ClearBackground(backgroundColor);
        DrawTexture(backgroundTexture, 0, 0, WHITE);

        loginBox.x = centerPositionHorizontal(loginBox.width);
        DrawRectangleRounded(loginBox, 0.2, 0, Fade(LoginBoxColor, 0.9f));

        GuiLabelFont((Rectangle){position, 100, 1000, 50}, "Welcome to LIBRE", headingFont, 50, ColorToInt(WHITE));
        GuiLabelFont((Rectangle){position, 200, 1000, 50}, "A Comprehensive Library Management System", subheadingFont, 40, ColorToInt(RAYWHITE));
        GuiLabelFont((Rectangle){position, 300, 1000, 50}, "Administrator Login", textFont, 30, 0x000000ff);

        GuiLabelFont((Rectangle){position - 200, 380, 1000, 50}, "Username", textFont, 25, 0x000000ff);
        DrawRectangleRec(nameBox, WHITE);
        GuiSetStyle(DEFAULT, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);
        if (GuiTextBox((Rectangle){centerPositionHorizontal(500), 420, 500, 50}, nameInput, maxInputSize, usernameTextBox))
        {
            buttonClear(usernameTextBox, nameInput, (char *)"Please enter name");
        };
        GuiSetStyle(DEFAULT, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
        GuiLabelFont((Rectangle){position - 200, 500, 1000, 50}, "Password", textFont, 25, 0x000000ff);

        DrawRectangleRec(passwordBox, WHITE);
        GuiSetStyle(DEFAULT, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);
        if (GuiTextBox(passwordBox, PasswordInput, maxInputSize, passwordTextBox))
        {
            buttonClear(passwordTextBox, PasswordInput, (char *)"Please enter Password");
        };

        GuiSetStyle(DEFAULT, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
        loginBtn = GuiButton((Rectangle){centerPositionHorizontal(400), 700, 400, 50}, "Login");

        GuiSetStyle(DEFAULT, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
       cancelBtn = GuiButton((Rectangle){centerPositionHorizontal(400), 800, 400, 50}, "Cancel");

        patronBtn = GuiLabelButton((Rectangle){position + 600, 900, 200, 50}, "Patron Login");
        GuiLabelButton((Rectangle){position + 600, 900, 200, 50}, "__________");
    }

    bool patronBtnpressed()
    {
        if (patronBtn == true)
        {
            patronBtn = false;
            return true;
        }
        return false;
    }

  

};
#endif