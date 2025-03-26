
#include <raylib.h>

// testing Remove afterwards
#include "./headers/GUI/SceneManager.h"
int main()
{
  constexpr int screenWidth = 800;
  constexpr int screenHeight = 600;

  Image icon = LoadImage("src/resources/images/Icon.png");

  SetConfigFlags(FLAG_WINDOW_RESIZABLE); // Window configuration flags
  // Enable MSAA (Multi-Sample Anti-Aliasing)
  SetConfigFlags(FLAG_MSAA_4X_HINT);

  InitWindow(screenWidth, screenHeight, "LIBRE"); // creates window

  SetWindowIcon(icon); // set window image

  MaximizeWindow(); // makes window fullscreeen

  SetWindowMinSize(GetScreenWidth(), GetScreenHeight()); // fix window size
 
 // ToggleFullscreen();

  SetTargetFPS(60); // set fps of window

  SceneManager *scene = new SceneManager; // Creates a Scene Manager that shows the login screen

  while (!WindowShouldClose())
  {
    BeginDrawing();
    scene->Draw();
    scene->Update();
    EndDrawing();
  }

  delete scene;

  UnloadImage(icon);
  CloseWindow();
}
