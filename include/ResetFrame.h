#pragma once
#include "PopUpFrame.h"

class ResetFrame : public PopUpFrame
{
public:
    ResetFrame(int ID);

    virtual void reload();

private:

    //GUI

    std::unique_ptr<wxPanel> _panel;

    std::unique_ptr<wxStaticText> _label;

    std::unique_ptr<wxTextCtrl> _dataDInput;
    std::unique_ptr<wxTextCtrl> _dataMInput;
    std::unique_ptr<wxTextCtrl> _dataRInput;

    std::unique_ptr<wxButton> _okButton;


private:

    enum class ID
    {
        DATA_D = 1, DATA_M=10, DATA_R=20, OK=30
    };

private:


};