
#include <raylib.h>

//testing Remove afterwards
#include "./headers/gui/scene.h"
#include "./headers/gui/welcomeScene.h"
#include "./headers/PasswordMangement/Password.h"
#include "./headers/User/Admin.h"
#include "./headers/LibraryManagement.h"
#include "./headers/FileManagement/FileManager.h"
int main()
{
     constexpr int screenWidth = 800;
     constexpr int screenHeight = 600;
     Image icon = LoadImage("src/resources/images/LibraryManagementSystemIcon.png");

     SetConfigFlags(FLAG_WINDOW_RESIZABLE); // Window configuration flags

     InitWindow(screenWidth, screenHeight, "LIBRE");

     WelcomeScene login;

     SetWindowIcon(icon);
     SetTargetFPS(60);

     while (!WindowShouldClose())
     {
         BeginDrawing();

         login.Draw();

         EndDrawing();
     }
     UnloadImage(icon);
     CloseWindow();
}