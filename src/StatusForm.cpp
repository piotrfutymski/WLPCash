#include "StatusForm.h"

StatusForm::StatusForm(int ID)
    : PopUpFrame(NULL, ID, wxT("Formularz statusu instruktora"), wxDefaultPosition, wxSize(560, 220+40), wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX))
{
    _panel = std::make_unique<wxPanel>(this, -1);

    _statusLabel = std::make_unique<wxStaticText>(_panel.get(), wxID_ANY, wxT("Status:"), wxPoint(20,50), wxSize(200,30));
    _dataLabel = std::make_unique<wxStaticText>(_panel.get(), wxID_ANY, wxT("Data rozp. (dd-mm-yyyy):"), wxPoint(20,140), wxSize(200,30));

    _statusInput = std::make_unique<wxListBox>(_panel.get(), wxWindowID(ID::STATUS), wxPoint(200,50), wxSize(300,70));
    _dataDInput = std::make_unique<wxTextCtrl>(_panel.get(), wxWindowID(ID::DATA_D), wxT(""), wxPoint(200,140), wxSize(40,30));
    _dataMInput = std::make_unique<wxTextCtrl>(_panel.get(), wxWindowID(ID::DATA_M), wxT(""), wxPoint(250,140), wxSize(40,30));
    _dataRInput = std::make_unique<wxTextCtrl>(_panel.get(), wxWindowID(ID::DATA_R), wxT(""), wxPoint(300,140), wxSize(80,30));

    _okButton = std::make_unique<wxButton>(_panel.get(), wxWindowID(ID::OK), wxT("OK") ,wxPoint(500, 180), wxSize(50,30));

    Connect(ID, wxEVT_CLOSE_WINDOW, wxCommandEventHandler(StatusForm::close));
}

void StatusForm::reload()
{
    //TO DO
    _statusInput->Append(std::vector<wxString>{wxT("Czynny"), wxT("Rezerwa"), wxT("Skreślony")});

}