#include "HufiecForm.h"


HufiecForm::HufiecForm(int ID, DBService * service)
    : PopUpFrame(NULL, ID, wxT("Formularz hufca"), wxDefaultPosition, wxSize(580, 250+40), wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX)), _db{service}
{
    _panel = std::make_unique<wxPanel>(this, -1);

    _nazwaLabel = std::make_unique<wxStaticText>(_panel.get(), wxID_ANY, wxT("Nazwa:"), wxPoint(20,50), wxSize(200,30));
    _hufcowyLabel = std::make_unique<wxStaticText>(_panel.get(), wxID_ANY, wxT("Hufcowy"), wxPoint(20,100), wxSize(200,30));

    _nazwaInput = std::make_unique<wxTextCtrl>(_panel.get(), wxWindowID(ID::NAZWA), wxT(""), wxPoint(200,50), wxSize(300,30));
    _hufcowyInput = std::make_unique<wxListBox>(_panel.get(), wxWindowID(ID::HUFCOWY), wxPoint(200,100), wxSize(300,100));

    _okButton = std::make_unique<wxButton>(_panel.get(), wxWindowID(ID::OK), wxT("OK") ,wxPoint(500, 210), wxSize(50,30));

    Connect(ID, wxEVT_CLOSE_WINDOW, wxCommandEventHandler(HufiecForm::close));
    Connect(wxWindowID(ID::OK), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(HufiecForm::onOK));
}

void HufiecForm::reload()
{
    _hufcowyInput->Clear();
    for(auto & std: _hufcowyData)
        _hufcowyInput->Append(std);

    _nazwaInput->SetValue(_nazwa);
    _hufcowyInput->SetSelection(_hufcowyInput->FindString(_hufcowy));
}


void HufiecForm::fillHufocowyData(const std::vector<std::wstring> & hD)
{
    _hufcowyData = hD;
}

void HufiecForm::setNazwa(const std::wstring & s)
{
    _nazwa = s;
}

void HufiecForm::setHufcowy(const std::wstring & s)
{
    _hufcowy = s;
}

void HufiecForm::setModify(bool m)
{
    _modify = m;
}

void HufiecForm::setOnOK(const std::function<void()> & f)
{
    _okFun = f;
}

void HufiecForm::onOK(wxCommandEvent& WXUNUSED(event))
{
    std::unique_ptr<wxMessageDialog> dial;
    bool res = false;

    std::vector<std::wstring> data;
    data.push_back(std::wstring(_nazwaInput->GetValue()));

    if(_hufcowyInput->GetSelection() != wxNOT_FOUND )
        data.push_back(std::wstring(_hufcowyInput->GetString(_hufcowyInput->GetSelection())));

    if(_modify)
    {
        res = _db->updateHufiec(_nazwa, data);
    }
    else
    {
        res = _db->insertHufiec(data);
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
