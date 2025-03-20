
#include <raylib.h>

// testing Remove afterwards
#include "./headers/gui/SceneManager.h"
int main()
{
  constexpr int screenWidth = 800;
  constexpr int screenHeight = 600;

  Image icon = LoadImage("src/resources/images/Icon.png");

  SetConfigFlags(FLAG_WINDOW_RESIZABLE); // Window configuration flags

  InitWindow(screenWidth, screenHeight, "LIBRE"); //creates window
  
  SetWindowIcon(icon);// set window image

  MaximizeWindow();//makes window fullscreeen

  SetWindowMinSize(GetScreenWidth(), GetScreenHeight());// fix window size

  SetTargetFPS(60);// set fps of window

  SceneManager *scene = new SceneManager; // Creates a Scene Manager that shows the login screen

  while (!WindowShouldClose())
  {
    BeginDrawing();
    scene->Draw();
    scene->Update();
    EndDrawing();
  }

  UnloadImage(icon);
  CloseWindow();
}
