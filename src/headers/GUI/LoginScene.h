
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

    bool usernameInput;
    char userInput[128] = "Please enter name";
    bool userPasswordInput;
    char userPasword[128] = "Please enter Password";
    bool registerPressed;

public:
    LoginScene()
    {
        Scene::backgroundColor = LIGHTGRAY;
        loginBox = {400, 300, 600, 700};
        LoginBoxColor = DARKGRAY;
        usernameInput = false;
        userPasswordInput = false;
        registerPressed = false;
    }

    void Draw()
    {
        float position = centerPositionHorizontal(1000);
        ClearBackground(backgroundColor);

        loginBox.x=centerPositionHorizontal(loginBox.width);
        DrawRectangleRounded(loginBox, 0.2,0, Fade(LoginBoxColor, 0.2f));

        GuiLabelFont((Rectangle){position, 100, 1000, 50}, "Welcome to LIBRE", headingFont, 50, 0x686868ff);
        GuiLabelFont((Rectangle){position, 200, 1000, 50}, "A Comprehensive Library Management System", subheadingFont, 40, 0x000000ff);
        GuiLabelFont((Rectangle){position, 300, 1000, 50}, "Please Login to Your Account", textFont, 30, 0x000000ff);

        GuiLabelFont((Rectangle){position - 200, 380, 1000, 50}, "Username", textFont, 25, 0x000000ff);
        GuiSetStyle(DEFAULT, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);
        if (GuiTextBox((Rectangle){centerPositionHorizontal(500), 420, 500, 50}, userInput, 128, usernameInput))
        {
            buttonClear(usernameInput, userInput, (char *)"Please enter name");
        };
        GuiSetStyle(DEFAULT, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
        GuiLabelFont((Rectangle){position - 200, 500, 1000, 50}, "Password", textFont, 25, 0x000000ff);
        GuiSetStyle(DEFAULT, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);
        if (GuiTextBox((Rectangle){centerPositionHorizontal(500), 540, 500, 50}, userPasword, 128, userPasswordInput))
        {
            buttonClear(userPasswordInput, userPasword, (char *)"Please enter Password");
        };

        GuiSetStyle(DEFAULT, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
        GuiButton((Rectangle){centerPositionHorizontal(400), 700, 400, 50}, "Login");

        GuiSetStyle(DEFAULT, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
        GuiButton((Rectangle){centerPositionHorizontal(400), 800, 400, 50}, "Cancel");

        registerPressed = (GuiLabelButton((Rectangle){position + 250, 850, 200, 50}, "New Then register"));

        GuiLabelButton((Rectangle){position + 240, 900, 200, 50}, "Reset password");
    }

    bool RegisterButton()
    {
        if (registerPressed==true){
            registerPressed=false;
            return true;
        }

        return false;
    }


};
#endif