#ifndef POPUP_H
#define POPUP_H
#include "Scene.h"
#include <chrono>

class PopUp : public Scene
{
private:
    chrono::steady_clock::time_point startTime;
    chrono::steady_clock::time_point startFadeTime;
    chrono::steady_clock::time_point currentTime;

    int duration;
    int timeSeconds;
    int timeMilliSeconds;
    float opacity;
    bool fadeout;

    Rectangle messageBox;
    string message;
    Color boxColor;
    Color textColor;

    enum Type
    {
        normal,
        success,
        error
    };

public:
    PopUp()
    {
        duration = 0;
        messageBox = {(float)GetScreenWidth() - 325, (float)GetScreenHeight() - 100, 300, 75};
        boxColor = WHITE;
        textColor = BLACK;
        message = "No Message";
        fadeout = false;
    }

    void ShowPopUp(int seconds, string text,Color color)
    {
        duration = seconds;
        messageBox = {(float)GetScreenWidth() - 325, (float)GetScreenHeight() - 100, 300, 75};
        boxColor = color;
        textColor = BLACK;
        message = text;
        fadeout = false;
        opacity = 0;
        startTime = chrono::steady_clock::now();
    }

    void Draw()
    {
        currentTime = std::chrono::steady_clock::now();
        timeSeconds = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();

        if (timeSeconds < duration)
        {
            timeMilliSeconds = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count();
            opacity = Lerp(0, 1, timeMilliSeconds * 0.002);

           // cout << "Program has been running for " << timeSeconds << " seconds |" << " duration: " << duration << endl;
            DrawRectangleRounded(messageBox, 0.2, 16, Fade(boxColor, opacity));
            GuiSetStyle(DEFAULT, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
            GuiLabelFont(messageBox, message.c_str(), headingFont, 24, ColorToInt(Fade(textColor, opacity)));

            startFadeTime = std::chrono::steady_clock::now();
            fadeout = true;
        }
        else if (fadeout)
        {
            timeMilliSeconds = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startFadeTime).count();

            messageBox = {messageBox.x, Lerp(messageBox.y, 100, 0.005), messageBox.width, messageBox.height};

            DrawRectangleRounded(messageBox, 0.2, 16, Fade(boxColor, Lerp(opacity, 0, timeMilliSeconds * 0.00065)));
            GuiSetStyle(DEFAULT, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
            GuiLabelFont(messageBox, message.c_str(), headingFont, 24, ColorToInt(Fade(textColor, Lerp(opacity, 0, timeMilliSeconds * 0.00065))));
        }
    }

    ~PopUp() {}
};

#endif