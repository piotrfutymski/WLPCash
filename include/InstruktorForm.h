#pragma once
#include "PopUpFrame.h"

class InstruktorForm : public PopUpFrame
{
public:
    InstruktorForm(int ID);

    virtual void reload();

private:

    //GUI

    std::unique_ptr<wxPanel> _panel;

    std::unique_ptr<wxStaticText> _imieLabel;
    std::unique_ptr<wxStaticText> _nazwiskoLabel;
    std::unique_ptr<wxStaticText> _emailLabel;
    std::unique_ptr<wxStaticText> _rozkazLabel;
    std::unique_ptr<wxStaticText> _stopienInstrLabel;
    std::unique_ptr<wxStaticText> _stopienHarcLabel;
    std::unique_ptr<wxStaticText> _hufiecLabel;
    std::unique_ptr<wxStaticText> _dataLabel;
    
    std::unique_ptr<wxTextCtrl> _imieInput;
    std::unique_ptr<wxTextCtrl> _nazwiskoInput;
    std::unique_ptr<wxTextCtrl> _emailInput;
    std::unique_ptr<wxTextCtrl> _rozkazInput;
    std::unique_ptr<wxListBox> _stopienInstrInput;
    std::unique_ptr<wxListBox> _stopienHarcInput;
    std::unique_ptr<wxListBox> _hufiecInput;
    std::unique_ptr<wxTextCtrl> _dataDInput;
    std::unique_ptr<wxTextCtrl> _dataMInput;
    std::unique_ptr<wxTextCtrl> _dataRInput;

    std::unique_ptr<wxButton> _okButton;


private:

    enum class ID
    {
        IMIE = 1, NAZWISKO, EMAIL, ROZKAZ, STOPIEN_INSTR, STOPIEN_HARC, HUFIEC, DATA_D, DATA_M, DATA_R, OK
    };


};