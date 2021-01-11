#include "ResetFrame.h"

ResetFrame::ResetFrame(int ID)
    : PopUpFrame(NULL, ID, wxT(""), wxDefaultPosition, wxSize(360, 190+40), wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX))
{
    _panel = std::make_unique<wxPanel>(this, -1);

    _label = std::make_unique<wxStaticText>(_panel.get(), wxID_ANY, wxT("Wybierz datę do kiedy ma trwać zerowy okres składkowy"), wxPoint(20,20), wxSize(300,100));

    _dataDInput = std::make_unique<wxTextCtrl>(_panel.get(), wxWindowID(ID::DATA_D), wxT(""), wxPoint(20,80), wxSize(40,30));
    _dataMInput = std::make_unique<wxTextCtrl>(_panel.get(), wxWindowID(ID::DATA_M), wxT(""), wxPoint(70,80), wxSize(40,30));
    _dataRInput = std::make_unique<wxTextCtrl>(_panel.get(), wxWindowID(ID::DATA_R), wxT(""), wxPoint(120,80), wxSize(80,30));

    _okButton = std::make_unique<wxButton>(_panel.get(), wxWindowID(ID::OK), wxT("OK") ,wxPoint(290, 150), wxSize(50,30));

    Connect(ID, wxEVT_CLOSE_WINDOW, wxCommandEventHandler(ResetFrame::close));
}

void ResetFrame::reload()
{
    //TO DO

}