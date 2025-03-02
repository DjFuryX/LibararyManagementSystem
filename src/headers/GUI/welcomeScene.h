
#include"scene.h"
class WelcomeScene : public Scene
{
private:
    Color headingColor;
    Color subHeadingColor;
    Color textColor;
    Color LoginBoxColor;
    Rectangle loginBox;

    bool usernameInput;
    char userInput[128]="Please enter name";
    bool userPasswordInput;
    char userPasword[128]="Please enter name";

public:
    WelcomeScene()
    {
        Scene::backgroundColor=LIGHTGRAY;
        loginBox={400,300,600,700};
        LoginBoxColor=DARKGRAY;
        usernameInput=false;
    }

    

    void Draw()
    {
        float position = centerPositionHorizontal(1000);
        ClearBackground(backgroundColor);

        DrawRectangleRounded(loginBox, 0.2,0, Fade(LoginBoxColor, 0.2f));
        loginBox.x=centerPositionHorizontal(loginBox.width);

        GuiLabelFont((Rectangle){position, 100, 1000, 50}, "Welcome to LIBRE", headingFont, 50,0x686868ff);
        GuiLabelFont((Rectangle){position, 200, 1000, 50}, "A Comprehensive Library Management System", subheadingFont, 40,0x000000ff);
        GuiLabelFont((Rectangle){position, 300, 1000, 50}, "Please Login to Your Account", textFont, 30,0x000000ff);
        
        GuiLabelFont((Rectangle){position-200, 380, 1000, 50}, "Username", textFont, 25,0x000000ff);
        GuiSetStyle(DEFAULT,TEXT_ALIGNMENT,TEXT_ALIGN_LEFT);
        if (GuiTextBox((Rectangle){centerPositionHorizontal(500), 420, 500, 50}, userInput, 128, usernameInput)) {
           buttonClear(usernameInput,userInput);
        };
        GuiSetStyle(DEFAULT,TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
        GuiLabelFont((Rectangle){position-200, 500, 1000, 50}, "Password", textFont, 25,0x000000ff);
        GuiSetStyle(DEFAULT,TEXT_ALIGNMENT,TEXT_ALIGN_LEFT);
        if (GuiTextBox((Rectangle){centerPositionHorizontal(500), 540, 500, 50}, userPasword, 128, userPasswordInput)) {
           buttonClear(userPasswordInput,userPasword);
        };
        


        GuiSetStyle(DEFAULT,TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
        GuiButton((Rectangle){centerPositionHorizontal(400), 700, 400, 50},"Login");

    }



};
