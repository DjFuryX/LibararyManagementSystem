#ifndef POPUP_H
#define POPUP_H
#include "Scene.h"
#include <chrono>

class PopUp : public Scene
{
private:
    chrono::steady_clock::time_point startTime;
    chrono::steady_clock::time_point currentTime;
    int duration;
    int timeSeconds;
    int timeMilliSeconds;
    int Endtime;

    Rectangle messageBox;
    string message;
    Color color;



public:
    PopUp()
    {
        duration = 5;
        startTime = chrono::steady_clock::now();
        messageBox = {(float)GetScreenWidth() - 200, (float)GetScreenHeight() - 100, 200, 100};
        color = GREEN;
        message = "No Message";
    }

    PopUp(int seconds, string text)
    {
        duration = seconds;
        startTime = chrono::steady_clock::now();
        message = text;
        color = RED;
    }

    void Draw()
    {
        currentTime = std::chrono::steady_clock::now();
        timeSeconds = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();
        timeMilliSeconds = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count();

        if (timeSeconds < duration)
        {
            cout << "Program has been running for " << timeSeconds << " seconds |" << " duration: " << duration << endl;
            DrawRectangleRounded(messageBox, 0.2, 0, Fade(color, Lerp(0, 1, timeMilliSeconds * 0.001)));
            GuiSetStyle(DEFAULT, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
            GuiLabelFont(messageBox, message.c_str(), headingFont, 24, ColorToInt(Fade(WHITE, Lerp(0, 1, timeMilliSeconds * 0.001))));
        }
        else{
            
            DrawRectangleRounded(messageBox, 0.2, 0, Fade(color, Lerp(1, 0, timeMilliSeconds * 0.0001)));
            GuiSetStyle(DEFAULT, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
            GuiLabelFont(messageBox, message.c_str(), headingFont, 24, ColorToInt(Fade(WHITE, Lerp(1, 0, timeMilliSeconds * 0.0001))));
        }

    }

    ~PopUp() {}
};

#endif