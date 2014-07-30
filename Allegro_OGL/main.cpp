/* Based on tutorial code from:

   http://www.mbsoftworks.sk/index.php?page=tutorials&series=1
   
*/

#include "common_header.h"
#include "appmain.h"

COpenGLWinApp appMain;

bool Keys::kp[ALLEGRO_KEY_MAX] = { 0 };
ALLEGRO_KEYBOARD_STATE Keys::keyState;

/*returns true if key is pressed*/
bool Keys::Key(int iKey)
{
    return al_key_down(&keyState, iKey);
}

/* True if key was pressed only once*/
bool Keys::Onekey(int iKey)
{
    if (Key(iKey) && !kp[iKey])
    {
        kp[iKey] = true;
        return true;
    }

    if (!Key(iKey))
        kp[iKey] = false;

    return false;
}

/*Resets app timer (ex: after re-acvtivation of window)*/
void COpenGLWinApp::ResetTimer()
{
    tLastFrame = clock();
    fFrameInterval = 0.0f;
}

/*Updates appliccation timer*/
void COpenGLWinApp::UpdateTimer()
{
    clock_t tCur = clock();
    fFrameInterval = float(tCur - tLastFrame) / float (CLOCKS_PER_SEC);
    tLastFrame = tCur;
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
    al_install_keyboard();
    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    ALLEGRO_TIMER *tick = al_create_timer(1.0 / 75.0);
    ALLEGRO_DISPLAY *display = al_get_current_display();

    al_register_event_source(queue, al_get_display_event_source(al_get_current_display()));
    al_register_event_source(queue, al_get_timer_event_source(tick));
    al_register_event_source(queue, al_get_keyboard_event_source());

    al_start_timer(tick);

    bool done = false;
    bool draw = false;
    bool bAppActive = true;
    oglControl.setProjection3D(45.0f,
        (float) al_get_display_width(display) / (float) al_get_display_height(display),
        0.001f, 1000.0f); // First call needed to initialize the projection matrix.

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
                oglControl.ResizeOpenGLViewportFull();
                oglControl.setProjection3D(45.0f,
                    (float)al_get_display_width(display) / (float)al_get_display_height(display),
                    0.001f, 1000.0f);
                break;
            case ALLEGRO_EVENT_DISPLAY_SWITCH_OUT:
                bAppActive = false;
                break;
            case ALLEGRO_EVENT_DISPLAY_SWITCH_IN:
                bAppActive = true;
                ResetTimer();
                break;
            case ALLEGRO_EVENT_KEY_DOWN:
                al_get_keyboard_state(&Keys::keyState);
                break;
            case ALLEGRO_EVENT_KEY_UP:
                al_get_keyboard_state(&Keys::keyState);
                break;
            case ALLEGRO_EVENT_TIMER:
                if (bAppActive)
                {
                    UpdateTimer();
                    draw = true;
                }
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
    appMain.ResetTimer();

    std::cout << argv[0] << std::endl;

    appMain.AppBody();
    appMain.Shutdown();
}