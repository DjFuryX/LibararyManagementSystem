#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"



int main() 
{
    const Color darkGreen = {20, 160, 133, 255};
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);    // Window configuration flags
    constexpr int screenWidth = 800;
    constexpr int screenHeight = 600;
    Image icon=LoadImage("src/resources/images/LibraryManagementSystemIcon.png");
    

    InitWindow(screenWidth, screenHeight, "LIBRE");
    SetWindowIcon(icon); 
    UnloadImage(icon);
  
    SetTargetFPS(60);

    Font headerFont=LoadFontEx("src/resources/fonts/Century-Gothic-Bold.ttf",72,0,NULL);
    Font subHeader=LoadFontEx("src/resources/fonts/copperplate-gothic-light.ttf",72,0,NULL);
    SetTextureFilter(headerFont.texture, TEXTURE_FILTER_TRILINEAR);
    SetTextureFilter(subHeader.texture, TEXTURE_FILTER_TRILINEAR);
    GuiSetStyle(DEFAULT,TEXT_COLOR_NORMAL, 0x000000ff);
    GuiSetStyle(DEFAULT,TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);

    
    while (!WindowShouldClose())
    {

        float position = (((float)GetScreenWidth() / 2) - (500/ 2));

        BeginDrawing();
            ClearBackground(darkGreen);
            GuiLabelFont((Rectangle){position,264,500,100},"Welcome to LIBRE",headerFont,50);
            GuiLabelFont((Rectangle){position-150,364,800,72},"Comprehensive Library Management",subHeader,40);
        EndDrawing();
    }
    
    CloseWindow();
}