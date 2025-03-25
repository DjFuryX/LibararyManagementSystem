
#ifndef SCENE_H
#define SCENE_H
#define RAYGUI_IMPLEMENTATION
#include <iostream>
using namespace std;
#include "raygui.h"
#include <raymath.h>

#include "src/headers/LibraryManagement.h"
#include "src/headers/FileManagement/FileManager.h"

#define maxInputSize 128

class Scene
{
protected:
    Font headingFont;
    Font subheadingFont;
    Font textFont;
    Color backgroundColor;
    Texture2D backgroundTexture;
    Rectangle bounds;
    Rectangle nameBox;
    Rectangle passwordBox;

public:
    Scene()
    {

        backgroundTexture = LoadTexture("src/resources/images/BookShelf.png");
        // load default font files
        headingFont = LoadFontEx("src/resources/fonts/Century-Gothic-Bold.ttf", 72, 0, 256);
        subheadingFont = LoadFontEx("src/resources/fonts/copperplate-gothic-light.ttf", 72, 0, 256);
        textFont = LoadFontEx("src/resources/fonts/Tahoma-Regular-font.ttf", 72, 0, 256);
        // generate Mipmaps for higher quality texture

        GenTextureMipmaps(&headingFont.texture);
        GenTextureMipmaps(&subheadingFont.texture);
        GenTextureMipmaps(&textFont.texture);
        // set texture filter to prevent blurry fonts
        SetTextureFilter(headingFont.texture, TEXTURE_FILTER_TRILINEAR);
        SetTextureFilter(subheadingFont.texture, TEXTURE_FILTER_TRILINEAR);
        SetTextureFilter(textFont.texture, TEXTURE_FILTER_TRILINEAR);
        // set text alignment and color
        GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, 0x000000ff);
        GuiSetStyle(DEFAULT, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
        // set background color
        backgroundColor = WHITE;
        // screen clickable screen space
        bounds = {0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()};
        //
        nameBox = {centerPositionHorizontal(500), 420, 500, 50};
        passwordBox = {centerPositionHorizontal(500), 540, 500, 50};


        GuiSetStyle(DEFAULT, TEXT_COLOR_FOCUSED, ColorToInt(SKYBLUE));
        // Load style properties provided
        GuiSetStyle(TEXTBOX, BASE_COLOR_NORMAL, ColorToInt(LIGHTGRAY));
        GuiSetStyle(TEXTBOX, BASE_COLOR_PRESSED, ColorToInt(WHITE));
        GuiSetStyle(TEXTBOX, TEXT_COLOR_FOCUSED, ColorToInt(LIGHTGRAY));
        GuiSetStyle(TEXTBOX, TEXT_COLOR_PRESSED, ColorToInt(BLACK));
        // GuiSetStyle(TEXTBOX, TEXT_COLOR_NORMAL,ColorToInt(LIGHTGRAY));

        // set toggle to appear transparent
        GuiSetStyle(TOGGLE, BASE_COLOR_NORMAL, ColorToInt(Fade(BLACK, 0)));
        GuiSetStyle(TOGGLE, TEXT_COLOR_PRESSED, ColorToInt(BLACK));
        GuiSetStyle(TOGGLE, BASE_COLOR_PRESSED, ColorToInt(Fade(BLACK, 0)));
        GuiSetStyle(TOGGLE, BASE_COLOR_FOCUSED, ColorToInt(Fade(BLACK, 0)));
        GuiSetStyle(TOGGLE, BORDER_COLOR_NORMAL, ColorToInt(Fade(BLACK, 0)));
        GuiSetStyle(TOGGLE, BORDER_COLOR_PRESSED, ColorToInt(Fade(BLACK, 0)));
        GuiSetStyle(TOGGLE, BORDER_COLOR_FOCUSED, ColorToInt(Fade(BLACK, 0)));
    }

    virtual void Draw()
    {
        ClearBackground(backgroundColor);
        DrawTexture(backgroundTexture, 0, 0, WHITE);
    }

    float centerPositionHorizontal(float lenght)
    {
        return (((float)GetScreenWidth() / 2) - (lenght / 2));
    }

    float centerPositionVertical(float width)
    {
        return (((float)GetScreenHeight() / 2) - (width / 2));
    }

    void buttonClear(bool &state, char *text, char *defaultText)
    {
        state = !state;
        
        if (state && strcmp(text, defaultText) == 0)
        {
            strcpy(text, "");
        }
        else if (strlen(text) == 0)
        {
            strcpy(text, defaultText);
        }
    }

    bool isButtonPressed(Rectangle bounds)
    {
        Vector2 mousePoint = GetMousePosition();

        if (CheckCollisionPointRec(mousePoint, bounds) && (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)))
        {
            return true;
        }
        return false;
    }

    bool IsMouseOver(Rectangle bounds){
        Vector2 mousePoint = GetMousePosition();

        if (CheckCollisionPointRec(mousePoint, bounds))
        {
            return true;
        }
        return false;
    }

    bool isHovered(Rectangle bounds)
    {
        Vector2 mousePoint = GetMousePosition();

        if (CheckCollisionPointRec(mousePoint, bounds))
        {
            DrawRectangleRounded(bounds, .2, 2, WHITE); // Draw container border
            return true;
        }
        return false;
    }

    bool ScreenPressed()
    {

        Vector2 mousePoint = GetMousePosition();
        // Check button state
        if (CheckCollisionPointRec(mousePoint, bounds) && (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)))
        {
            return true;
        }
        return false;
    }

    ~Scene()
    {
        UnloadTexture(backgroundTexture);
    }
};

#endif