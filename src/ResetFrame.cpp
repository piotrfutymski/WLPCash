#include "ResetFrame.h"

ResetFrame::ResetFrame(int ID, DBService * db)
    : PopUpFrame(NULL, ID, wxT(""), wxDefaultPosition, wxSize(360, 190+40), wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX)), _db{db}
{
    _panel = std::make_unique<wxPanel>(this, -1);

    _label = std::make_unique<wxStaticText>(_panel.get(), wxID_ANY, wxT("Pierwszy okres składkowy będzie wynosił 0 zł i rozpocznie się 01.2020"), wxPoint(20,20), wxSize(300,150));

    _okButton = std::make_unique<wxButton>(_panel.get(), wxWindowID(ID::OK), wxT("OK") ,wxPoint(290, 150), wxSize(50,30));

    Connect(ID, wxEVT_CLOSE_WINDOW, wxCommandEventHandler(ResetFrame::close));
    Connect(wxWindowID(ID::OK), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(ResetFrame::onOK));
}

void ResetFrame::reload()
{

}

void ResetFrame::setOnlyWplaty(bool onW)
{
    _onlyWplaty = onW;
}

void ResetFrame::onOK(wxCommandEvent & event)
{
    std::unique_ptr<wxMessageDialog> dial1, dial2;
    bool res = false;

    dial1 = std::make_unique<wxMessageDialog>(nullptr, wxT("Czy na pewno chcesz dokonac resetu? Ta operacja jest nieodwołalna"), wxT("Info"), wxYES_NO);

    if(dial1->ShowModal() != wxID_YES)
        return;

    if(_onlyWplaty)
    {
        res = _db->resetWplaty();
        if(res)
        {
            dial2 = std::make_unique<wxMessageDialog>(nullptr, wxT("Zresetowano Wpłaty"), wxT("Info"), wxOK);
        }
        else
        {
            dial2 = std::make_unique<wxMessageDialog>(nullptr, wxT("Nie udało się zresetować Wpłat"), wxT("Błąd"), wxOK | wxICON_ERROR);
        }
    }
    else
    {
        res = _db->resetBaza();
        if(res)
        {
            dial2 = std::make_unique<wxMessageDialog>(nullptr, wxT("Zresetowano Bazę"), wxT("Info"), wxOK);
        }
        else
        {
            dial2 = std::make_unique<wxMessageDialog>(nullptr, wxT("Nie udało się zresetować Bazy"), wxT("Błąd"), wxOK | wxICON_ERROR);
        }
    }

    dial2->ShowModal();
}