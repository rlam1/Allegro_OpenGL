#include "common_header.h"
#include "OpenGLControl.h"

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
bool COpenGLControl::InitOpenGL(void(*a_InitScene)(LPVOID), void(*a_RenderScene)(LPVOID), void(*a_ReleaseScene)(LPVOID), LPVOID lpParam)
{
    al_init();
    display = nullptr;
    al_set_new_display_flags(ALLEGRO_OPENGL | ALLEGRO_OPENGL_FORWARD_COMPATIBLE | ALLEGRO_RESIZABLE);
    display = al_create_display(640, 480);

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
    if (RenderScene)RenderScene(lpParam);
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