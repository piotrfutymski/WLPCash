#include "OkresForm.h"

OkresForm::OkresForm(int ID, DBService * service)
    : PopUpFrame(NULL, ID, wxT("Formularz okresu składkowego"), wxDefaultPosition, wxSize(580, 180+40), wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX)), _db{service}
{
    _panel = std::make_unique<wxPanel>(this, -1);

    _kwotaLabel = std::make_unique<wxStaticText>(_panel.get(), wxID_ANY, wxT("Kwota:"), wxPoint(20,50), wxSize(200,30));
    _dataLabel = std::make_unique<wxStaticText>(_panel.get(), wxID_ANY, wxT("Data rozp. (mm-yyyy):"), wxPoint(20,110), wxSize(200,30));

    _kwotaInput = std::make_unique<wxTextCtrl>(_panel.get(), wxWindowID(ID::KWOTA), wxT(""), wxPoint(200,50), wxSize(300,30));
    _dataMInput = std::make_unique<wxTextCtrl>(_panel.get(), wxWindowID(ID::DATA_M), wxT(""), wxPoint(200,110), wxSize(40,30));
    _dataRInput = std::make_unique<wxTextCtrl>(_panel.get(), wxWindowID(ID::DATA_R), wxT(""), wxPoint(250,110), wxSize(80,30));

    _okButton = std::make_unique<wxButton>(_panel.get(), wxWindowID(ID::OK), wxT("OK") ,wxPoint(500, 150), wxSize(50,30));

    Connect(ID, wxEVT_CLOSE_WINDOW, wxCommandEventHandler(OkresForm::close));
    Connect(wxWindowID(ID::OK), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(OkresForm::onOK));
}

void OkresForm::reload()
{
}

void OkresForm::setOnOK(const std::function<void()> & f)
{
    _okFun = f;
}

void OkresForm::onOK(wxCommandEvent & event)
{
     std::unique_ptr<wxMessageDialog> dial;
    bool res = false;

    std::vector<std::string> data;
    data.push_back(std::string(_dataMInput->GetValue()));
    data.push_back(std::string(_dataRInput->GetValue()));
    data.push_back(std::string(_kwotaInput->GetValue()));

    res = _db->insertOkres(data);

    if(res)
    {
        dial = std::make_unique<wxMessageDialog>(nullptr, wxT("Polecenie wykonane"), wxT("Info"), wxOK);
    }
    else
    {
        dial = std::make_unique<wxMessageDialog>(nullptr, wxT("Nie udało się wykonać polecenia"), wxT("Błąd"), wxOK | wxICON_ERROR);
    }

    dial->ShowModal(); 

    if(_okFun)
        _okFun();
}