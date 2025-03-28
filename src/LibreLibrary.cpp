
#include <raylib.h>
#include "./headers/GUI/SceneManager.h"
int main()
{
  constexpr int screenWidth = 1920;
  constexpr int screenHeight = 1080;

  Image icon = LoadImage("src/resources/images/Icon.png");

  SetConfigFlags(FLAG_WINDOW_RESIZABLE); // Window configuration flags
  // Enable MSAA (Multi-Sample Anti-Aliasing)
  SetConfigFlags(FLAG_MSAA_4X_HINT);

  InitWindow(screenWidth, screenHeight, "LIBRE"); // creates window
  SetWindowIcon(icon);                            // set window image
  SetWindowMinSize(screenWidth, screenHeight); // fix window size
  ToggleFullscreen();
  SetTargetFPS(60); // set fps of window

  SceneManager *scene = new SceneManager; // Creates a Scene Manager that controls the flow of the program

  while (!WindowShouldClose())//runs unot escape is pressed
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
