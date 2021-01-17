#include "InstruktorForm.h"

InstruktorForm::InstruktorForm(int ID, DBService * db)
    : PopUpFrame(NULL, ID, wxT("Formularz instruktora"), wxDefaultPosition, wxSize(580, 630+40), wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX)), _db{db}
{
    _panel = std::make_unique<wxPanel>(this, -1);

    _imieLabel = std::make_unique<wxStaticText>(_panel.get(), wxID_ANY, wxT("Imię:"), wxPoint(20,50), wxSize(200,30));
    _nazwiskoLabel = std::make_unique<wxStaticText>(_panel.get(), wxID_ANY, wxT("Nazwisko:"), wxPoint(20,100), wxSize(200,30));
    _emailLabel = std::make_unique<wxStaticText>(_panel.get(), wxID_ANY, wxT("E-mail:"), wxPoint(20,150), wxSize(200,30));
    _rozkazLabel = std::make_unique<wxStaticText>(_panel.get(), wxID_ANY, wxT("Rozkaz:"), wxPoint(20,200), wxSize(200,30));
    _stopienInstrLabel = std::make_unique<wxStaticText>(_panel.get(), wxID_ANY, wxT("Stopień instruktorski:"), wxPoint(20,250), wxSize(200,30));
    _stopienHarcLabel = std::make_unique<wxStaticText>(_panel.get(), wxID_ANY, wxT("Stopień harcerski:"), wxPoint(20,340), wxSize(200,30));
    _hufiecLabel = std::make_unique<wxStaticText>(_panel.get(), wxID_ANY, wxT("Hufiec:"), wxPoint(20,430), wxSize(200,30));
    _dataLabel = std::make_unique<wxStaticText>(_panel.get(), wxID_ANY, wxT("Data rozkazu (dd-mm-yyyy):"), wxPoint(20,550), wxSize(200,30));

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
    Connect(wxWindowID(ID::OK), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(InstruktorForm::onOK));

}

void InstruktorForm::reload()
{
    _stopienHarcInput->Clear();
    for(auto & std: _stopienHarcData)
        _stopienHarcInput->Append(std);

    _stopienInstrInput->Clear();
    for(auto & std: _stopienInstrData)
        _stopienInstrInput->Append(std);
    
    _hufiecInput->Clear();
    for(auto & std: _hufiecData)
        _hufiecInput->Append(std);



    _imieInput->SetValue(_imie);
    _nazwiskoInput->SetValue(_nazwisko);
    _emailInput->SetValue(_email);
    _rozkazInput->SetValue(_rozkaz);
    _stopienInstrInput->SetSelection(_stopienInstrInput->FindString(_stopienInstr));
    _stopienHarcInput->SetSelection(_stopienHarcInput->FindString(_stopienHarc));
    _hufiecInput->SetSelection(_hufiecInput->FindString(_hufiec));
}

void InstruktorForm::fillStopienInstrData(const std::vector<std::wstring> & hD)
{
    _stopienInstrData = hD;
}
void InstruktorForm::fillstopienHarcData(const std::vector<std::wstring> & hD)
{
    _stopienHarcData = hD;
}
void InstruktorForm::fillHufiecData(const std::vector<std::wstring> & hD)
{
    _hufiecData= hD;
}

void InstruktorForm::setImie(const std::wstring & s)
{
    _imie = s;
}
void InstruktorForm::setNazwisko(const std::wstring & s)
{
    _nazwisko = s;
}
void InstruktorForm::setEmail(const std::wstring & s)
{
    _email = s;
}
void InstruktorForm::setRozkaz(const std::wstring & s)
{
    _rozkaz = s;
}
void InstruktorForm::setStopienInstr(const std::wstring & s)
{
    _stopienInstr = s;
}
void InstruktorForm::setStopienHarc(const std::wstring & s)
{
    _stopienHarc = s;
}
void InstruktorForm::setHufiec(const std::wstring & s)
{
    _hufiec = s;
}

void InstruktorForm::setModify(bool m)
{
    _modify = m;
}
void InstruktorForm::setOnOK(const std::function<void()> & f)
{
    _okFun = f;
}

void InstruktorForm::onOK(wxCommandEvent & event)
{
    std::unique_ptr<wxMessageDialog> dial;
    bool res = false;

    std::vector<std::wstring> data;
    data.push_back(std::wstring(_imieInput->GetValue()));
    data.push_back(std::wstring(_nazwiskoInput->GetValue()));
    data.push_back(std::wstring(_emailInput->GetValue()));
    data.push_back(std::wstring(_rozkazInput->GetValue()));

    if(_stopienInstrInput->GetSelection() != wxNOT_FOUND )
        data.push_back(std::wstring(_stopienInstrInput->GetString(_stopienInstrInput->GetSelection())));
    
    if(_stopienHarcInput->GetSelection() != wxNOT_FOUND )
        data.push_back(std::wstring(_stopienHarcInput->GetString(_stopienHarcInput->GetSelection())));
    
    if(_hufiecInput->GetSelection() != wxNOT_FOUND )
        data.push_back(std::wstring(_hufiecInput->GetString(_hufiecInput->GetSelection())));
    else
        data.push_back(std::wstring(L""));
    

    if(_modify)
    {
        res = _db->updateInstruktor(_imie, _nazwisko, data);
    }
    else
    {
        data.push_back(std::wstring(_dataDInput->GetValue()));
        data.push_back(std::wstring(_dataMInput->GetValue()));
        data.push_back(std::wstring(_dataRInput->GetValue()));
        res = _db->insertInstruktor(data);
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
