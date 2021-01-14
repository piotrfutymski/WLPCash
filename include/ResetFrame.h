#pragma once
#include "PopUpFrame.h"
#include "DBService.h"

class ResetFrame : public PopUpFrame
{
public:
    ResetFrame(int ID, DBService * service);

    virtual void reload();

    void setOnlyWplaty(bool onW);

private:

    //GUI

    std::unique_ptr<wxPanel> _panel;

    std::unique_ptr<wxStaticText> _label;

    std::unique_ptr<wxTextCtrl> _dataMInput;
    std::unique_ptr<wxTextCtrl> _dataRInput;

    std::unique_ptr<wxButton> _okButton;

    //

    bool _onlyWplaty = true;

    DBService * _db;

private:

    enum class ID
    {
        DATA_D = 1, DATA_M=10, DATA_R=20, OK=30
    };

private:

    void onOK(wxCommandEvent & event);

};