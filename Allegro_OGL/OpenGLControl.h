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
    void setProjection3D(float fFOV, float fAspectRatio, float fNear, float fFar);
    glm::mat4* getProjectionMatrix();

    void Render(LPVOID lpParam);
    void ReleaseOpenGLControl(LPVOID lpParam);

    void MakeCurrent();
    void SwapBuffersM();

    bool setVerticalSynchronization(bool bEnabled);

    int getFPS();

    COpenGLControl();

private:
    ALLEGRO_DISPLAY *display;

    // Used in FPS calculation
    int iFPSCount, iCurrentFPS;
    clock_t tLastSecond;

    // Matrix for persp. projecton
    glm::mat4 mProjection;

    void(*InitScene)(LPVOID lpParam), (*RenderScene)(LPVOID lpParam), (*ReleaseScene)(LPVOID lpParam);
};