#include "StatusForm.h"

StatusForm::StatusForm(int ID, DBService * service)
    : PopUpFrame(NULL, ID, wxT("Formularz statusu instruktora"), wxDefaultPosition, wxSize(580, 220+40), wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX)), _db{service}
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
    Connect(wxWindowID(ID::OK), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(StatusForm::onOK));
}

void StatusForm::reload()
{
    _statusInput->Clear();
    for(auto & std: _statusData)
        _statusInput->Append(std);

}

void StatusForm::fillStatusData(const std::vector<std::string> & hD)
{
    _statusData = hD;
}

void StatusForm::setInstruktor(const std::string & s)
{
    _instruktor = s;
}

void StatusForm::setOnOK(const std::function<void()> & f)
{
    _okFun = f;
}

void StatusForm::onOK(wxCommandEvent & event)
{
    std::unique_ptr<wxMessageDialog> dial;
    bool res = false;

    std::vector<std::string> data; 

    if(_statusInput->GetSelection() != wxNOT_FOUND )
        data.push_back(std::string(_statusInput->GetString(_statusInput->GetSelection())));
    
    data.push_back(_instruktor);

    data.push_back(std::string(_dataDInput->GetValue()));
    data.push_back(std::string(_dataMInput->GetValue()));
    data.push_back(std::string(_dataRInput->GetValue()));

    res = _db->insertStatus(data);

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