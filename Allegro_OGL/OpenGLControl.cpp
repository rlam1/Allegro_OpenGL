#include "common_header.h"
#include "OpenGLControl.h"

#include <glm/gtc/matrix_transform.hpp>

COpenGLControl::COpenGLControl()
{
    iFPSCount = 0;
    iCurrentFPS = 0;
}

/*-----------------------------------------------

Name:	InitOpenGL

Params:
a_initScene - pointer to init function
a_renderScene - pointer to render function
a_releaseScene - optional parameter of release function

Result:	Initializes OpenGL rendering context
of specified version. If succeeds,
returns true.

/*---------------------------------------------*/
bool COpenGLControl::InitOpenGL(void(*a_InitScene)(LPVOID), void(*a_RenderScene)(LPVOID), void(*a_ReleaseScene)(LPVOID), std::string sTitle, LPVOID lpParam)
{
    al_init();
    display = nullptr;
    al_set_new_display_flags(ALLEGRO_OPENGL | ALLEGRO_OPENGL_FORWARD_COMPATIBLE | ALLEGRO_RESIZABLE);
    display = al_create_display(640, 480);
    al_set_window_title(display, sTitle.c_str());

    RenderScene = a_RenderScene;
    InitScene = a_InitScene;
    ReleaseScene = a_ReleaseScene;

    if (InitScene != NULL)InitScene(lpParam);

    return true;
}

/*Resizes viewport to full window with perspective projection.*/
void COpenGLControl::ResizeOpenGLViewportFull()
{
    GLsizei width = al_get_display_width(display);
    GLsizei height = al_get_display_height(display);

    glViewport(0, 0, width, height);
}

/*-----------------------------------------------

Name:	setProjection3D

Params:	fFOV - field of view angle
fAspectRatio - aspect ratio of width/height
fNear, fFar - distance of near and far clipping plane

/*---------------------------------------------*/

void COpenGLControl::setProjection3D(float fFOV, float fAspectRatio, float fNear, float fFar)
{
    mProjection = glm::perspective(fFOV, fAspectRatio, fNear, fFar);
}

glm::mat4* COpenGLControl::getProjectionMatrix()
{
    return &mProjection;
}

/*-----------------------------------------------

Name:	SwapBuffersM

Params:	none

Result:	Swaps back and front buffer.

/*---------------------------------------------*/

void COpenGLControl::SwapBuffersM()
{
    al_flip_display();
}

/*-----------------------------------------------

Name:	MakeCurrent

Params:	none

Result:	Makes current device and OpenGL rendering
context to those associated with OpenGL
control.

/*---------------------------------------------*/

void COpenGLControl::MakeCurrent()
{
    al_set_target_backbuffer(al_get_current_display());
}

/*-----------------------------------------------

Name:	Render

Params:	lpParam - pointer to whatever you want

Result:	Calls previously set render function.

/*---------------------------------------------*/

void COpenGLControl::Render(LPVOID lpParam)
{
    clock_t tCurrent = clock();
    if ((tCurrent - tLastSecond) >= CLOCKS_PER_SEC)
    {
        tLastSecond += CLOCKS_PER_SEC;
        iFPSCount = iCurrentFPS;
        iCurrentFPS = 0;
    }

    if (RenderScene)RenderScene(lpParam);
    iCurrentFPS++;
}

int COpenGLControl::getFPS()
{
    return iFPSCount;
}

/*-----------------------------------------------

Name:	ReleaseOpenGLControl

Params:	lpParam - pointer to whatever you want

Result:	Calls previously set release function
and deletes rendering context.

/*---------------------------------------------*/

void COpenGLControl::ReleaseOpenGLControl(LPVOID lpParam)
{
    if (ReleaseScene)ReleaseScene(lpParam);

    al_destroy_display(display);
}

bool COpenGLControl::setVerticalSynchronization(bool bEnabled)
{
    if (!wglSwapIntervalEXT)return false;
    if (bEnabled)wglSwapIntervalEXT(1);
    else wglSwapIntervalEXT(0);
    return true;
}