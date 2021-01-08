#include "DruzynaForm.h"

DruzynaForm::DruzynaForm(int ID)
    : PopUpFrame(NULL, ID, wxT("Formularz druzyny"), wxDefaultPosition, wxSize(560, 630+40), wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX))
{
    _panel = std::make_unique<wxPanel>(this, -1);

    _nazwaLabel = std::make_unique<wxStaticText>(_panel.get(), wxID_ANY, wxT("Nazwa:"), wxPoint(20,50), wxSize(200,30));
    _numerLabel = std::make_unique<wxStaticText>(_panel.get(), wxID_ANY, wxT("Numer:"), wxPoint(20,100), wxSize(200,30));
    _probnaLabel = std::make_unique<wxStaticText>(_panel.get(), wxID_ANY, wxT("Czy próbna:"), wxPoint(20,150), wxSize(200,30));
    _patronLabel = std::make_unique<wxStaticText>(_panel.get(), wxID_ANY, wxT("Patron:"), wxPoint(20,220), wxSize(200,30));
    _druzynowyLabel = std::make_unique<wxStaticText>(_panel.get(), wxID_ANY, wxT("Drużynowy:"), wxPoint(20,270), wxSize(200,30));
    _hufiecLabel = std::make_unique<wxStaticText>(_panel.get(), wxID_ANY, wxT("Hufiec:"), wxPoint(20,390), wxSize(200,30));
    _typLabel = std::make_unique<wxStaticText>(_panel.get(), wxID_ANY, wxT("Typ:"), wxPoint(20,510), wxSize(200,30));

    _nazwaInput = std::make_unique<wxTextCtrl>(_panel.get(), wxWindowID(ID::NAZWA), wxT(""), wxPoint(200,50), wxSize(300,30));
    _numerInput = std::make_unique<wxTextCtrl>(_panel.get(), wxWindowID(ID::NUMER), wxT(""), wxPoint(200,100), wxSize(300,30));
    _probnaInput = std::make_unique<wxListBox>(_panel.get(), wxWindowID(ID::PROBNA), wxPoint(200,150), wxSize(300,50));
    _patronInput = std::make_unique<wxTextCtrl>(_panel.get(), wxWindowID(ID::PATRON), wxT(""), wxPoint(200,220), wxSize(300,30));
    _druzynowyInput = std::make_unique<wxListBox>(_panel.get(), wxWindowID(ID::DRUZYNOWY), wxPoint(200,270), wxSize(300,100));
    _hufiecInput = std::make_unique<wxListBox>(_panel.get(), wxWindowID(ID::HUFIEC), wxPoint(200,390), wxSize(300,100));
    _typInput = std::make_unique<wxListBox>(_panel.get(), wxWindowID(ID::TYP), wxPoint(200,510), wxSize(300,50));

    _okButton = std::make_unique<wxButton>(_panel.get(), wxWindowID(ID::OK), wxT("OK") ,wxPoint(500, 590), wxSize(50,30));

    Connect(ID, wxEVT_CLOSE_WINDOW, wxCommandEventHandler(DruzynaForm::close));
}

void DruzynaForm::reload()
{
    //TO DO

    _probnaInput->Append(std::vector<wxString>{wxT("NIE"), wxT("TAK")});
    _druzynowyInput->Append(std::vector<wxString>{wxT("AA"), wxT("A")});
    _hufiecInput->Append(std::vector<wxString>{wxT("A"), wxT("B")});
    _typInput->Append(std::vector<wxString>{wxT("Zuchowa"), wxT("Harcerska"), wxT("Wędrownicza")});
}