#pragma once
#include "PopUpFrame.h"

class HufiecForm : public PopUpFrame
{
public:
    HufiecForm(int ID);

    virtual void reload();

private:

    //GUI

    std::unique_ptr<wxPanel> _panel;

    std::unique_ptr<wxStaticText> _nazwaLabel;
    std::unique_ptr<wxStaticText> _hufcowyLabel;
    
    std::unique_ptr<wxTextCtrl> _nazwaInput;
    std::unique_ptr<wxListBox> _hufcowyInput;

    std::unique_ptr<wxButton> _okButton;

    std::string _nazwa;
    std::vector<std::string> _hufcowyData;

private:

    enum class ID
    {
        NAZWA = 1, HUFCOWY, OK
    };


};