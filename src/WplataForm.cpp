#include "WplataForm.h"

WplataForm::WplataForm(int ID)
    : PopUpFrame(NULL, ID, wxT("Formularz wpłaty"), wxDefaultPosition, wxSize(580, 270+40), wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX))
{
    _panel = std::make_unique<wxPanel>(this, -1);

    _instruktorLabel = std::make_unique<wxStaticText>(_panel.get(), wxID_ANY, wxT("Instruktor:"), wxPoint(20,50), wxSize(200,30));
    _kwotaLabel = std::make_unique<wxStaticText>(_panel.get(), wxID_ANY, wxT("Kwota(zł):"), wxPoint(20,140), wxSize(200,30));
    _dataLabel = std::make_unique<wxStaticText>(_panel.get(), wxID_ANY, wxT("Data (dd-mm-yyyy):"), wxPoint(20,190), wxSize(200,30));

    _instruktorInput = std::make_unique<wxListBox>(_panel.get(), wxWindowID(ID::INSTRUKTOR), wxPoint(200,50), wxSize(300,70));
    _kwotaInput = std::make_unique<wxTextCtrl>(_panel.get(), wxWindowID(ID::KWOTA), wxT(""), wxPoint(200,140), wxSize(300,30));

    _dataDInput = std::make_unique<wxTextCtrl>(_panel.get(), wxWindowID(ID::DATA_D), wxT(""), wxPoint(200,190), wxSize(40,30));
    _dataMInput = std::make_unique<wxTextCtrl>(_panel.get(), wxWindowID(ID::DATA_M), wxT(""), wxPoint(250,190), wxSize(40,30));
    _dataRInput = std::make_unique<wxTextCtrl>(_panel.get(), wxWindowID(ID::DATA_R), wxT(""), wxPoint(300,190), wxSize(80,30));

    _okButton = std::make_unique<wxButton>(_panel.get(), wxWindowID(ID::OK), wxT("OK") ,wxPoint(500, 230), wxSize(50,30));

    Connect(ID, wxEVT_CLOSE_WINDOW, wxCommandEventHandler(WplataForm::close));
}

void WplataForm::reload()
{
    //TO DO
    _instruktorInput->Append(std::vector<wxString>{wxT("Antoni Kozanecki"), wxT("Jan Kowalski")});

}