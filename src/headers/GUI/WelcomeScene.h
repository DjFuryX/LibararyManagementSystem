
#ifndef WELCOMESCENE_H
#define WELCOMESCENE_H
#include "Scene.h"
class WelcomeScene : public Scene
{
private:
    Color headingColor;
    Color subHeadingColor;
    Color textColor;

    char message[maxInputSize] = "Welcome";
    char idString[maxInputSize] = "0000";
    string idmessage = "Library Number: ";

    int animFrames = 0;
    int currentAnimFrame = 0;             // Current animation frame to load and draw
    int frameDelay = 0;                   // Frame delay to switch between animation frames
    unsigned int nextFrameDataOffset = 0; // Current byte offset to next frame in image.data
    int frameCounter = 0;
    Image imScarfyAnim;
    Texture2D texScarfyAnim;

public:
    WelcomeScene()
    {
        Scene::backgroundColor = LIGHTGRAY;
        imScarfyAnim = LoadImageAnim("src/resources/images/book.gif", &animFrames);
        texScarfyAnim = LoadTextureFromImage(imScarfyAnim);
        // generate Mipmaps for higher quality fonts
        GenTextureMipmaps(&texScarfyAnim);
        // set texture filter to prevent blurry fonts
        SetTextureFilter(texScarfyAnim, TEXTURE_FILTER_TRILINEAR);
    }

    void Draw()
    {
        float position = centerPositionHorizontal(1000);
        ClearBackground(backgroundColor);
        DrawTexture(backgroundTexture, 0, 0, WHITE);

        GuiLabelFont((Rectangle){position, 100, 1000, 50}, "Welcome to LIBRE", headingFont, 50, 0x686868ff);
        GuiLabelFont((Rectangle){position, 200, 1000, 50}, message, textFont, 50, 0x000000ff);
        GuiLabelFont((Rectangle){position, 300, 1000, 50}, idString, textFont, 50, 0x000000ff);

        DrawTexture(texScarfyAnim,832, 500, WHITE);
        DrawGIF();
        GuiLabelFont((Rectangle){position, 750, 1000, 50}, "Press Anywhere to Continue", headingFont, 30, 0x686868ff);
        GuiLabelFont((Rectangle){position, 1000, 1000, 50}, "A Comprehensive Library Management System", subheadingFont, 40, 0x000000ff);
    }

    void DrawGIF()
    {
        frameCounter++;
        if (frameCounter >= frameDelay)
        {
            // Move to next frame
            // NOTE: If final frame is reached we return to first frame
            currentAnimFrame++;
            if (currentAnimFrame >= animFrames)
                currentAnimFrame = 0;

            // Get memory offset position for next frame data in image.data
            nextFrameDataOffset = imScarfyAnim.width * imScarfyAnim.height * 4 * currentAnimFrame;

            // Update GPU texture data with next frame image data
            // WARNING: Data size (frame size) and pixel format must match already created texture
            UpdateTexture(texScarfyAnim, ((unsigned char *)imScarfyAnim.data) + nextFrameDataOffset);

            frameCounter = 0;
        }
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
};
#endif