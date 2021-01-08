#pragma once
#include <memory>
#include <vector>
#include <wx/wx.h>

class PopUpFrame : public wxFrame
{
public:

    PopUpFrame();

    PopUpFrame(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &pos=wxDefaultPosition, 
    const wxSize &size=wxDefaultSize, long style=wxDEFAULT_FRAME_STYLE, const wxString &name=wxFrameNameStr);

    bool isOpened()const;

    virtual void reload() = 0;

    bool Show();

protected:

    bool _isOpened = false;

protected:

    void close(wxCommandEvent & event);

};