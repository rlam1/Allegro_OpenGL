#pragma once

#include "common_header.h"
#define SIMPLE_OPENGL_CLASS_NAME "Simple_openGL_class"

/********************************

Class:	COpenGLControl

Purpose:	Provides convenient usage
of OpenGL

********************************/

class COpenGLControl {
public:
    bool InitOpenGL(void(*a_InitScene)(LPVOID), void(*a_RenderScene)(LPVOID), void(*a_ReleaseScene)(LPVOID), std::string sTitle, LPVOID lpParam);

    void ResizeOpenGLViewportFull();

    void Render(LPVOID lpParam);
    void ReleaseOpenGLControl(LPVOID lpParam);

    void MakeCurrent();
    void SwapBuffersM();

private:
    HDC hDC;
    HWND* hWnd;
    HGLRC hRC;
    int iMajorVersion, iMinorVersion;

    ALLEGRO_DISPLAY *display;

    void(*InitScene)(LPVOID lpParam), (*RenderScene)(LPVOID lpParam), (*ReleaseScene)(LPVOID lpParam);
};

LRESULT CALLBACK MsgHandlerSimpleOpenGLClass(HWND, UINT, WPARAM, LPARAM);