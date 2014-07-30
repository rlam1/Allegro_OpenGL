#pragma once

#include "openGLControl.h"

class COpenGLWinApp {
public:
    COpenGLControl oglControl; // OpenGL Control

    void ResetTimer();
    void UpdateTimer();
    float sof(float fVal);

    bool CreateAppWindow(std::string sTitle);

    void AppBody();
    void Shutdown();

private:
    std::string sAppName;

    bool bAppActive; // To check if application is active (not minimized)
    clock_t tLastFrame;
    float fFrameInterval;

    ALLEGRO_DISPLAY *display;
};

namespace Keys
{
    extern ALLEGRO_KEYBOARD_STATE keyState;
    bool Key(int iKey);
    bool Onekey(int iKey);
    extern bool kp[ALLEGRO_KEY_MAX];
}

extern COpenGLWinApp appMain;

void InitScene(LPVOID), RenderScene(LPVOID), ReleaseScene(LPVOID);