#pragma once
#include "PopUpFrame.h"

class StatusForm : public PopUpFrame
{
public:
    StatusForm(int ID);

    virtual void reload();

private:

    //GUI

    std::unique_ptr<wxPanel> _panel;

    std::unique_ptr<wxStaticText> _statusLabel;
    std::unique_ptr<wxStaticText> _dataLabel;

    std::unique_ptr<wxListBox> _statusInput;
    std::unique_ptr<wxTextCtrl> _dataDInput;
    std::unique_ptr<wxTextCtrl> _dataMInput;
    std::unique_ptr<wxTextCtrl> _dataRInput;

    std::unique_ptr<wxButton> _okButton;

private:

    enum class ID
    {
        STATUS = 1, DATA_D, DATA_M, DATA_R, OK
    };


};