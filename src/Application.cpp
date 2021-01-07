#include "Application.h"

bool Application::OnInit()
{
    MainFrame *frame = new MainFrame();
    frame->Show(true);
    return true;
}