#include "InstruktorForm.h"

InstruktorForm::InstruktorForm(int ID)
    : PopUpFrame(NULL, ID, wxT("Formularz instruktora"), wxDefaultPosition, wxSize(560, 630+40), wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX))
{
    _panel = std::make_unique<wxPanel>(this, -1);

    _imieLabel = std::make_unique<wxStaticText>(_panel.get(), wxID_ANY, wxT("Imię:"), wxPoint(20,50), wxSize(200,30));
    _nazwiskoLabel = std::make_unique<wxStaticText>(_panel.get(), wxID_ANY, wxT("Nazwisko:"), wxPoint(20,100), wxSize(200,30));
    _emailLabel = std::make_unique<wxStaticText>(_panel.get(), wxID_ANY, wxT("E-mail:"), wxPoint(20,150), wxSize(200,30));
    _rozkazLabel = std::make_unique<wxStaticText>(_panel.get(), wxID_ANY, wxT("Rozkaz:"), wxPoint(20,200), wxSize(200,30));
    _stopienInstrLabel = std::make_unique<wxStaticText>(_panel.get(), wxID_ANY, wxT("Stopień instruktorski:"), wxPoint(20,250), wxSize(200,30));
    _stopienHarcLabel = std::make_unique<wxStaticText>(_panel.get(), wxID_ANY, wxT("Stopień harcerski:"), wxPoint(20,340), wxSize(200,30));
    _hufiecLabel = std::make_unique<wxStaticText>(_panel.get(), wxID_ANY, wxT("Hufiec:"), wxPoint(20,430), wxSize(200,30));
    _dataLabel = std::make_unique<wxStaticText>(_panel.get(), wxID_ANY, wxT("Data (dd-mm-yyyy):"), wxPoint(20,550), wxSize(200,30));

    _imieInput = std::make_unique<wxTextCtrl>(_panel.get(), wxWindowID(ID::IMIE), wxT(""), wxPoint(200,50), wxSize(300,30));
    _nazwiskoInput = std::make_unique<wxTextCtrl>(_panel.get(), wxWindowID(ID::NAZWISKO), wxT(""), wxPoint(200,100), wxSize(300,30));
    _emailInput = std::make_unique<wxTextCtrl>(_panel.get(), wxWindowID(ID::EMAIL), wxT(""), wxPoint(200,150), wxSize(300,30));
    _rozkazInput = std::make_unique<wxTextCtrl>(_panel.get(), wxWindowID(ID::ROZKAZ), wxT(""), wxPoint(200,200), wxSize(300,30));
    _stopienInstrInput = std::make_unique<wxListBox>(_panel.get(), wxWindowID(ID::STOPIEN_INSTR), wxPoint(200,250), wxSize(300,70));
    _stopienHarcInput = std::make_unique<wxListBox>(_panel.get(), wxWindowID(ID::STOPIEN_HARC), wxPoint(200,340), wxSize(300,70));
    _hufiecInput = std::make_unique<wxListBox>(_panel.get(), wxWindowID(ID::HUFIEC), wxPoint(200,430), wxSize(300,100));
    _dataDInput = std::make_unique<wxTextCtrl>(_panel.get(), wxWindowID(ID::DATA_D), wxT(""), wxPoint(200,550), wxSize(40,30));
    _dataMInput = std::make_unique<wxTextCtrl>(_panel.get(), wxWindowID(ID::DATA_M), wxT(""), wxPoint(250,550), wxSize(40,30));
    _dataRInput = std::make_unique<wxTextCtrl>(_panel.get(), wxWindowID(ID::DATA_R), wxT(""), wxPoint(300,550), wxSize(80,30));

    _okButton = std::make_unique<wxButton>(_panel.get(), wxWindowID(ID::OK), wxT("OK") ,wxPoint(500, 590), wxSize(50,30));

    Connect(ID, wxEVT_CLOSE_WINDOW, wxCommandEventHandler(InstruktorForm::close));
}

void InstruktorForm::reload()
{
    //TO DO
    _stopienInstrInput->Append(std::vector<wxString>{wxT("pwd"), wxT("phm"), wxT("hm")});
    _stopienHarcInput->Append(std::vector<wxString>{wxT("HO"), wxT("HR")});

}