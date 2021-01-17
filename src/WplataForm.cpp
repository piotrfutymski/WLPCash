#include "WplataForm.h"

WplataForm::WplataForm(int ID, DBService * db)
    : PopUpFrame(NULL, ID, wxT("Formularz wpłaty"), wxDefaultPosition, wxSize(580, 270+40), wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX)), _db{db}
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
    Connect(wxWindowID(ID::OK), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(WplataForm::onOK));
}

void WplataForm::reload()
{
    _instruktorInput->Clear();
    for(auto & std: _instruktorData)
        _instruktorInput->Append(std);

    _kwotaInput->SetValue(_kwota);
    _dataDInput->SetValue(_dataD);
    _dataMInput->SetValue(_dataM);
    _dataRInput->SetValue(_dataR);
    if(_instruktorInput->FindString(_instruktor) != wxNOT_FOUND)
        _instruktorInput->SetSelection(_instruktorInput->FindString(_instruktor));

}

void WplataForm::fillInstruktorData(const std::vector<std::wstring> & hD)
{
    _instruktorData = hD;
}

void WplataForm::setInstruktor(const std::wstring & s)
{
    _instruktor = s;
}
void WplataForm::setKwota(const std::wstring & s)
{
    _kwota = s;
}
void WplataForm::setDataD(const std::wstring & s)
{
    _dataD = s;
}
void WplataForm::setDataM(const std::wstring & s)
{
    _dataM = s;
}
void WplataForm::setDataR(const std::wstring & s)
{
    _dataR = s;
}

void WplataForm::setID(const std::wstring & s)
{
    _id = s;
}

void WplataForm::setModify(bool m)
{
    _modify = m;
}
void WplataForm::setOnOK(const std::function<void()> & f)
{
    _okFun = f;
}

void WplataForm::onOK(wxCommandEvent & event)
{
    std::unique_ptr<wxMessageDialog> dial;
    bool res = false;

    std::vector<std::wstring> data;

    if(_instruktorInput->GetSelection() != wxNOT_FOUND )
        data.push_back(std::wstring(_instruktorInput->GetString(_instruktorInput->GetSelection())));

    data.push_back(std::wstring(_kwotaInput->GetValue()));
    data.push_back(std::wstring(_dataDInput->GetValue()));
    data.push_back(std::wstring(_dataMInput->GetValue()));
    data.push_back(std::wstring(_dataRInput->GetValue()));

    if(_modify)
    {
        res = _db->updateWplata(_id, data);
    }
    else
    {
        res = _db->insertWplata(data);
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
