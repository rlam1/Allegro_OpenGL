/* Based on tutorial code from:

   http://www.mbsoftworks.sk/index.php?page=tutorials&series=1
   
*/

#include "common_header.h"
#include "appmain.h"

COpenGLWinApp appMain;

/*Creates main application window.*/
bool COpenGLWinApp::CreateAppWindow(std::string sTitle)
{
    al_init();
    display = nullptr;
    al_set_new_display_flags(ALLEGRO_OPENGL | ALLEGRO_OPENGL_FORWARD_COMPATIBLE);
    display = al_create_display(640, 480);
    al_set_window_title(display, sTitle.c_str());

    if (!oglControl.InitOpenGL(InitScene, RenderScene, NULL, &oglControl))
        return false;

    return true;
}

/*Main application body infinite loop.*/
void COpenGLWinApp::AppBody()
{
    if (bAppActive)
        oglControl.Render(&oglControl);
}

/*Shuts down application and releases used memory*/
void COpenGLWinApp::Shutdown()
{
    
}

int main(int argc, char **argv)
{
    if (!appMain.CreateAppWindow("03.) Shaders Are Coming - Tutorial by Michal Bubnar (www.mbsoftworks.sk)"))
        return 0;

    appMain.AppBody();
    appMain.Shutdown();

    al_flip_display();

    al_rest(5.0);
}