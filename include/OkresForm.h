#pragma once
#include "PopUpFrame.h"

class OkresForm : public PopUpFrame
{
public:
    OkresForm(int ID);

    virtual void reload();

private:

    //GUI

    std::unique_ptr<wxPanel> _panel;

    std::unique_ptr<wxStaticText> _kwotaLabel;
    std::unique_ptr<wxStaticText> _dataLabel;

    std::unique_ptr<wxTextCtrl> _kwotaInput;
    std::unique_ptr<wxTextCtrl> _dataMInput;
    std::unique_ptr<wxTextCtrl> _dataRInput;

    std::unique_ptr<wxButton> _okButton;

private:

    enum class ID
    {
        KWOTA = 1, DATA_D, DATA_M, DATA_R, OK
    };


};