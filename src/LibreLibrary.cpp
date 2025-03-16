
#include <raylib.h>

// testing Remove afterwards
#include "./headers/gui/SceneManager.h"
int main()
{
  constexpr int screenWidth = 800;
  constexpr int screenHeight = 600;
  Image icon = LoadImage("src/resources/images/Icon.png");

  SetConfigFlags(FLAG_WINDOW_RESIZABLE); // Window configuration flags

  InitWindow(screenWidth, screenHeight, "LIBRE");
  SetWindowIcon(icon);
  MaximizeWindow();
  SetWindowMinSize(GetScreenWidth(), GetScreenHeight());
  SetTargetFPS(60);

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
