#pragma once
#include "PopUpFrame.h"
#include "DBService.h"

class OkresForm : public PopUpFrame
{
public:
    OkresForm(int ID, DBService * service);

    virtual void reload();

    void setOnOK(const std::function<void()> & f);

private:

    //GUI

    std::unique_ptr<wxPanel> _panel;

    std::unique_ptr<wxStaticText> _kwotaLabel;
    std::unique_ptr<wxStaticText> _dataLabel;

    std::unique_ptr<wxTextCtrl> _kwotaInput;
    std::unique_ptr<wxTextCtrl> _dataMInput;
    std::unique_ptr<wxTextCtrl> _dataRInput;

    std::unique_ptr<wxButton> _okButton;

    //SERVICE

    DBService * _db;

    //Function

    std::function<void()> _okFun;

private:

    enum class ID
    {
        KWOTA = 1, DATA_D, DATA_M, DATA_R, OK
    };

    void onOK(wxCommandEvent & event);

};