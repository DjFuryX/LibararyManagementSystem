
#include <raylib.h>
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
  SetWindowIcon(icon);                            // set window image
  MaximizeWindow();
  SetWindowMinSize(GetScreenWidth(), GetScreenHeight()); // fix window size
  ToggleFullscreen();
  SetTargetFPS(60); // set fps of window

  SceneManager *scene = new SceneManager; // Creates a Scene Manager that shows the login screen

  while (!WindowShouldClose())
  {
    BeginDrawing(); // start gui draw call

    scene->Draw(); // draw for current scene

    scene->Update(); // update scene functions

    EndDrawing(); // end gui draw call
  }

  delete scene; // call destructor and save library information

  UnloadImage(icon); // free image from memory

  CloseWindow(); // closes the window
}
