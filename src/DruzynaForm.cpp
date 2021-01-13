#include "DruzynaForm.h"

DruzynaForm::DruzynaForm(int ID, DBService * db)
    : PopUpFrame(NULL, ID, wxT("Formularz druzyny"), wxDefaultPosition, wxSize(580, 630+40), wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX)), _db{db}
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
    Connect(wxWindowID(ID::OK), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(DruzynaForm::onOK));
    _probnaInput->Append(std::vector<wxString>{wxT("NIE"), wxT("TAK")});

}

void DruzynaForm::reload()
{
    _druzynowyInput->Clear();
    for(auto & std: _druzynowyData)
        _druzynowyInput->Append(std);
    
    _hufiecInput->Clear();
    for(auto & std: _hufiecData)
        _hufiecInput->Append(std);

    _typInput->Clear();
    for(auto & std: _typData)
        _typInput->Append(std);

    _nazwaInput->SetValue(_nazwa);
    _numerInput->SetValue(_numer);
    _probnaInput->SetSelection(_probnaInput->FindString(_probna));
    _patronInput->SetValue(_patron);
    _druzynowyInput->SetSelection(_druzynowyInput->FindString(_druzynowy));
    _hufiecInput->SetSelection(_hufiecInput->FindString(_hufiec));
    _typInput->SetSelection(_typInput->FindString(_typ));
}

void DruzynaForm::fillDruzynowyData(const std::vector<std::string> & hD)
{
    _druzynowyData = hD;
}
void DruzynaForm::fillHufiecData(const std::vector<std::string> & hD)
{
    _hufiecData = hD;
}
void DruzynaForm::fillTypData(const std::vector<std::string> & hD)
{
    _typData = hD;
}
void DruzynaForm::setNazwa(const std::string & s)
{
    _nazwa = s;
}
void DruzynaForm::setNumer(const std::string & s)
{
    _numer = s;
}
void DruzynaForm::setProbna(const std::string & s)
{
    _probna = s;
}
void DruzynaForm::setPatron(const std::string & s)
{
    _patron = s;
}
void DruzynaForm::setDruzynowy(const std::string & s)
{
    _druzynowy = s;
}
void DruzynaForm::setHufiec(const std::string & s)
{
    _hufiec = s;
}
void DruzynaForm::setTyp(const std::string & s)
{
    _typ = s;
}

void DruzynaForm::setModify(bool m)
{
    _modify = m;
}
void DruzynaForm::setOnOK(const std::function<void()> & f)
{
    _okFun = f;
}

void DruzynaForm::onOK(wxCommandEvent & event)
{
    std::unique_ptr<wxMessageDialog> dial;
    bool res = false;

    std::vector<std::string> data;
    data.push_back(std::string(_nazwaInput->GetValue()));
    data.push_back(std::string(_numerInput->GetValue()));

    if(_probnaInput->GetSelection() != wxNOT_FOUND )
        data.push_back(std::string(_probnaInput->GetString(_probnaInput->GetSelection())));

    data.push_back(std::string(_patronInput->GetValue()));

    if(_druzynowyInput->GetSelection() != wxNOT_FOUND )
        data.push_back(std::string(_druzynowyInput->GetString(_druzynowyInput->GetSelection())));
    if(_hufiecInput->GetSelection() != wxNOT_FOUND )
        data.push_back(std::string(_hufiecInput->GetString(_hufiecInput->GetSelection())));
    if(_typInput->GetSelection() != wxNOT_FOUND )
        data.push_back(std::string(_typInput->GetString(_typInput->GetSelection())));

    if(_modify)
    {
        res = _db->updateDruzyna(_nazwa, _numer, data);
    }
    else
    {
        res = _db->insertDruzyna(data);
    }

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