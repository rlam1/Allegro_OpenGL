/* Based on tutorial code from:

   http://www.mbsoftworks.sk/index.php?page=tutorials&series=1
   
*/

#include "common_header.h"
#include "appmain.h"

COpenGLWinApp appMain;

/*Resets app timer (ex: after re-acvtivation of window)*/
void COpenGLWinApp::ResetTimer()
{
    dwLastFrame = GetTickCount();
    fFrameInterval = 0.0f;
}

/*Updates appliccation timer*/
void COpenGLWinApp::UpdateTimer()
{
    DWORD dwCur = GetTickCount();
    fFrameInterval = float(dwCur - dwLastFrame)*0.001f;
    dwLastFrame = dwCur;
}

/*SOF = speed optimized float*/
float COpenGLWinApp::sof(float fVal)
{
    return fVal*fFrameInterval;
}

/*Creates main application window.*/
bool COpenGLWinApp::CreateAppWindow(std::string sTitle)
{
    if (!oglControl.InitOpenGL(InitScene, RenderScene, NULL, sTitle, &oglControl))
        return false;

    return true;
}

/*Main application body infinite loop.*/
void COpenGLWinApp::AppBody()
{
    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    ALLEGRO_TIMER *tick = al_create_timer(1.0 / 75.0);

    al_register_event_source(queue, al_get_display_event_source(al_get_current_display()));
    al_register_event_source(queue, al_get_timer_event_source(tick));

    al_start_timer(tick);

    bool done = false;
    bool draw = false;

    while (!done)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(queue, &ev);

        switch (ev.type)
        {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;
            case ALLEGRO_EVENT_DISPLAY_RESIZE:
                al_acknowledge_resize(al_get_current_display());
                oglControl.ResizeOpenGLViewportFull();
                break;
            case ALLEGRO_EVENT_TIMER:
                draw = true;
                break;
            default:
                break;
        }

        if (al_is_event_queue_empty(queue) && draw == true)
        {
            draw = false;
            oglControl.Render(&oglControl);
        }
    }
}

/*Shuts down application and releases used memory*/
void COpenGLWinApp::Shutdown()
{
    ReleaseScene(&oglControl);
    oglControl.ReleaseOpenGLControl(&oglControl);
}

int main(int argc, char **argv)
{
    if (!appMain.CreateAppWindow("03.) Shaders Are Coming - Tutorial by Michal Bubnar (www.mbsoftworks.sk)"))
        return 0;

    std::cout << argv[0] << std::endl;

    appMain.AppBody();
    appMain.Shutdown();
}