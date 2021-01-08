#include "HufiecForm.h"


HufiecForm::HufiecForm(int ID)
    : PopUpFrame(NULL, ID, wxT("Formularz hufca"), wxDefaultPosition, wxSize(560, 250+40), wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX))
{
    _panel = std::make_unique<wxPanel>(this, -1);

    _nazwaLabel = std::make_unique<wxStaticText>(_panel.get(), wxID_ANY, wxT("Nazwa:"), wxPoint(20,50), wxSize(200,30));
    _hufcowyLabel = std::make_unique<wxStaticText>(_panel.get(), wxID_ANY, wxT("Hufcowy"), wxPoint(20,100), wxSize(200,30));

    _nazwaInput = std::make_unique<wxTextCtrl>(_panel.get(), wxWindowID(ID::NAZWA), wxT(""), wxPoint(140,50), wxSize(300,30));
    _hufcowyInput = std::make_unique<wxListBox>(_panel.get(), wxWindowID(ID::HUFCOWY), wxPoint(140,100), wxSize(300,100));

    _okButton = std::make_unique<wxButton>(_panel.get(), wxWindowID(ID::OK), wxT("OK") ,wxPoint(500, 210), wxSize(50,30));

    Connect(ID, wxEVT_CLOSE_WINDOW, wxCommandEventHandler(HufiecForm::close));
}

void HufiecForm::reload()
{
    //TO DO

    _hufcowyInput->Append(std::vector<wxString>{wxT("Antoni Kozanecki"), wxT("Jan Kowalski")});
}