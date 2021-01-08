#pragma once
#include "PopUpFrame.h"

class DruzynaForm : public PopUpFrame
{
public:
    DruzynaForm(int ID);

    virtual void reload();

private:

    //GUI

    std::unique_ptr<wxPanel> _panel;

    std::unique_ptr<wxStaticText> _nazwaLabel;
    std::unique_ptr<wxStaticText> _numerLabel;
    std::unique_ptr<wxStaticText> _probnaLabel;
    std::unique_ptr<wxStaticText> _patronLabel;
    std::unique_ptr<wxStaticText> _hufiecLabel;
    std::unique_ptr<wxStaticText> _druzynowyLabel;
    std::unique_ptr<wxStaticText> _typLabel;
    
    std::unique_ptr<wxTextCtrl> _nazwaInput;
    std::unique_ptr<wxTextCtrl> _numerInput;
    std::unique_ptr<wxListBox> _probnaInput;
    std::unique_ptr<wxTextCtrl> _patronInput;
    std::unique_ptr<wxListBox> _druzynowyInput;
    std::unique_ptr<wxListBox> _hufiecInput;
    std::unique_ptr<wxListBox> _typInput;

    std::unique_ptr<wxButton> _okButton;


private:

    enum class ID
    {
        NAZWA = 1, NUMER, PROBNA, PATRON, DRUZYNOWY, HUFIEC, TYP, OK
    };


};