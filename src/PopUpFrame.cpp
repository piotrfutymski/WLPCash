#include "PopUpFrame.h"

PopUpFrame::PopUpFrame() :wxFrame()
{}

PopUpFrame::PopUpFrame(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &pos, 
    const wxSize &size, long style, const wxString &name)
        : wxFrame(parent, id, title, pos, size, style, name)
{
}

bool PopUpFrame::isOpened()const
{
    return _isOpened;
}

bool PopUpFrame::Show()
{
    _isOpened = true;
    return wxFrame::Show();
}

void PopUpFrame::close(wxCommandEvent& WXUNUSED(event))
{
    _isOpened = false;
    wxFrame::Hide();
}