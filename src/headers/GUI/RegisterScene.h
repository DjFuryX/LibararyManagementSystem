#ifndef REGISTERSCENE_H
#define REGISTERSCENE_H

#include "LoginScene.h"

class RegisterScene : public LoginScene
{

private:

    char tempPasword[maxInputSize] = "-- -- --";
    Rectangle tempPasswordBox;
    bool tempPassPressed;

public:
    RegisterScene():LoginScene()
    {
        tempPassPressed=false;
        tempPasswordBox={centerPositionHorizontal(500), 550, 500, 50};
    }

    void Draw()
    {
        float position = centerPositionHorizontal(1000);
        ClearBackground(backgroundColor);
        DrawTexture(backgroundTexture, 0, 0, WHITE);

        loginBox.x = centerPositionHorizontal(loginBox.width);
        DrawRectangleRounded(loginBox, 0.2, 16, Fade(LoginBoxColor, 0.9f));

        GuiLabelFont((Rectangle){position, 100, 1000, 50}, "Welcome to LIBRE", headingFont, 50, ColorToInt(WHITE));
        GuiLabelFont((Rectangle){position, 200, 1000, 50}, "A Comprehensive Library Management System", subheadingFont, 40,ColorToInt(RAYWHITE));
        GuiLabelFont((Rectangle){position, 300, 1000, 50}, "Registration", textFont, 30, 0x000000ff);

        GuiLabelFont((Rectangle){position - 200, 380, 1000, 50}, "Username", textFont, 25, 0x000000ff);
        DrawRectangleRec(nameBox,WHITE);
        GuiSetStyle(DEFAULT, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);
        if (GuiTextBox(nameBox, nameInput, maxInputSize, usernameTextBox))
        {
            buttonClear(usernameTextBox, nameInput, (char *)"Please enter name");
        };
       
        GuiSetStyle(DEFAULT, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);


        GuiLabelFont((Rectangle){centerPositionHorizontal(500), 500, 500, 50}, "Temporary Password", textFont, 30, 0x000000ff);
      
        GuiSetStyle(DEFAULT, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
        GuiLabelFont((Rectangle){centerPositionHorizontal(500), 550, 500, 50}, tempPasword, textFont, 50, 0x000000ff);
        DrawRectangleRec(tempPasswordBox,WHITE);

        tempPassPressed = GuiTextBox(tempPasswordBox, tempPasword, maxInputSize, false);
        
        GuiSetStyle(DEFAULT, TEXT_SIZE, 25);
        registerBtn = GuiButton((Rectangle){centerPositionHorizontal(400), 700, 400, 50}, "Register");

        GuiSetStyle(DEFAULT, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
        GuiButton((Rectangle){centerPositionHorizontal(400), 800, 400, 50}, "Cancel");

        loginBtn = GuiLabelButton((Rectangle){position + 250, 850, 200, 50}, "Back to Login");
    }


    bool CopyTempPassword()
    {
        if (tempPassPressed == true)
        {
            tempPassPressed = false;
            return true;
        }
        return tempPassPressed;
    }


    string GetTempPasswordText(){

        return tempPasword;
    }


    string GetUserNameInput()
    {
        return nameInput;
    }

    void SetTempPasswordText(string text)
    {   
        //cout<<"Text Changed--"<<tempPasword<<" : "<<text<<endl;
        strcpy(tempPasword, text.c_str());

        
    }
};

#endif