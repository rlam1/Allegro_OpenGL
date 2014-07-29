#pragma once

#include "openGLControl.h"

class COpenGLWinApp {
public:
    COpenGLControl oglControl; // OpenGL Control

    bool CreateAppWindow(std::string sTitle);

    void AppBody();
    void Shutdown();

private:
    std::string sAppName;

    bool bAppActive; // To check if application is active (not minimized)

    ALLEGRO_DISPLAY *display;
};

namespace Keys
{
    int Key(int iKey);
    int Onekey(int iKey);
    extern char kp[256];
}

extern COpenGLWinApp appMain;

void InitScene(LPVOID), RenderScene(LPVOID), ReleaseScene(LPVOID);