#pragma once

#ifndef SCENE_H
#define SCENE_H
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include <iostream>

using namespace std;

class Scene
{
protected:
    Font headingFont;
    Font subheadingFont;
    Font textFont;
    Color backgroundColor;

public:
    Scene()
    {
        //load default font files
        headingFont = LoadFontEx("src/resources/fonts/Century-Gothic-Bold.ttf", 72, 0, 256);
        subheadingFont = LoadFontEx("src/resources/fonts/copperplate-gothic-light.ttf", 72, 0, 256);
        textFont = LoadFontEx("src/resources/fonts/Tahoma-Regular-font.ttf", 72, 0, 256);
        //generate Mipmaps for higher quality fonts
        GenTextureMipmaps(&headingFont.texture);
        GenTextureMipmaps(&subheadingFont.texture);
        GenTextureMipmaps(&textFont.texture);
        //set texture filter to prevent blurry fonts
        SetTextureFilter(headingFont.texture, TEXTURE_FILTER_TRILINEAR);
        SetTextureFilter(subheadingFont.texture, TEXTURE_FILTER_TRILINEAR);
        SetTextureFilter(textFont.texture, TEXTURE_FILTER_TRILINEAR);
        //set text alignment and color
        GuiSetStyle(DEFAULT,TEXT_COLOR_NORMAL, 0x000000ff);
        GuiSetStyle(DEFAULT,TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
        //set background color
        backgroundColor=WHITE;

    }

    virtual void Draw()
    {
        ClearBackground(backgroundColor);
    }

    float centerPositionHorizontal(float lenght){
        return (((float)GetScreenWidth() / 2) - (lenght/ 2));
    }
    
    float centerPositionVertical(float width){
        return (((float)GetScreenHeight() / 2) - (width/ 2));
    }

    void buttonClear(bool &state,char* text){
        state = !state;
        if(state && strcmp(text,"Please enter name")==0){
            strcpy(text,"");
        }
        else if(strlen(text)==0){
            strcpy(text,"Please enter name");
        }

    }
};

#endif