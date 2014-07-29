/* Based on tutorial code from:

   http://www.mbsoftworks.sk/index.php?page=tutorials&series=1
   
*/

#include "common_header.h"
#include "appmain.h"

COpenGLWinApp appMain;

/*Creates main application window.*/
bool COpenGLWinApp::CreateAppWindow(std::string sTitle)
{
    if (!oglControl.InitOpenGL(InitScene, RenderScene, NULL, &oglControl))
        return false;

    return true;
}

/*Main application body infinite loop.*/
void COpenGLWinApp::AppBody()
{
    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    ALLEGRO_TIMER *tick = al_create_timer(1.0 / 60.0);

    al_register_event_source(queue, al_get_display_event_source(al_get_current_display()));
    al_register_event_source(queue, al_get_timer_event_source(tick));

    al_start_timer(tick);

    bool done = false;

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
                oglControl.Render(&oglControl);
                break;
            default:
                break;
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