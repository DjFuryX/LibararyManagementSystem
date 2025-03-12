
#ifndef PATRONSCENE_H
#define PATRONSCENE_H
#include "Scene.h"
class PatronScene : public Scene
{
private:
    char message[128] = "Welcome";
    char idString[128] = "0000";
    string idmessage = "Library Number: ";

    // Define the scroll panel bounds and content
    Vector2 panelScroll;
    Rectangle panel;

    Vector2 mousePoint;
    float mouseWheelSpeed;

    int offset=50;



public:
    PatronScene()
    {
        Scene::backgroundColor = LIGHTGRAY;
        panelScroll = {0, 0};
        panel = {150,100,(float)GetScreenWidth()-150,(float)GetScreenHeight()-100};
        mouseWheelSpeed=20.0f;
        
    }

    void Draw()
    {
        ClearBackground(DARKGRAY);
    
        DrawRectangleRounded((Rectangle){panel.x+offset,panel.y+panelScroll.y+offset,300,400}, 0.2, 0, GREEN);

        DrawRectangleRounded((Rectangle){panel.x+330+offset,panel.y+panelScroll.y+offset,300,400}, 0.2, 0, RED);
        DrawRectangleRounded((Rectangle){panel.x+660+offset,panel.y+panelScroll.y+offset,300,400}, 0.2, 0, GREEN);
        DrawRectangleRounded((Rectangle){panel.x+990+offset,panel.y+panelScroll.y+offset,300,400}, 0.2, 0, RED);
        DrawRectangleRounded((Rectangle){panel.x+1320+offset,panel.y+panelScroll.y+offset,300,400}, 0.2, 0, GREEN);
    
        DrawRectangle(0, 0, GetScreenWidth(), 100, RED);
        DrawRectangle(0, 0,150,GetScreenHeight(), ORANGE);
        DrawRectangle(0, 0,150,100, PINK);
        
        //DrawRectangleRec(panel,Fade(GREEN, 0.2f));

        GetMouseScroll();
        /*   GuiLabelFont((Rectangle){position, 100, 1000, 50}, "Welcome to LIBRE", headingFont, 50, 0x686868ff);
          GuiLabelFont((Rectangle){position, 200, 1000, 50}, message, textFont, 50, 0x000000ff);
          GuiLabelFont((Rectangle){position, 300, 1000, 50}, idString, textFont, 50, 0x000000ff);

          GuiLabelFont((Rectangle){position, 750, 1000, 50}, "Press Anywhere to Continue", headingFont, 30, 0x686868ff);
          GuiLabelFont((Rectangle){position, 1000, 1000, 50}, "A Comprehensive Library Management System", subheadingFont, 40, 0x000000ff); */
    }

    void SetName(string name)
    {
        strcpy(message, name.c_str());
    }

    void SetID(int id)
    {
        idmessage = idmessage + to_string(id);
        strcpy(idString, idmessage.c_str());
    }

    void GetMouseScroll()
    {   
        mousePoint = GetMousePosition();
        if (CheckCollisionPointRec(mousePoint, panel))
        { 
            float wheelMove = GetMouseWheelMove();
            panelScroll.y += wheelMove * mouseWheelSpeed; // Vertical scroll
        } 
    }
};

#endif