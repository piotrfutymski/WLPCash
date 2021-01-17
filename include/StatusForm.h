#pragma once
#include "PopUpFrame.h"
#include "DBService.h"

class StatusForm : public PopUpFrame
{
public:
    StatusForm(int ID, DBService * service);

    virtual void reload();

    void fillStatusData(const std::vector<std::wstring> & hD);

    void setInstruktor(const std::wstring & s);

    void setOnOK(const std::function<void()> & f);

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

    //DATA

    std::wstring _instruktor;

    std::vector<std::wstring> _statusData;

    //SERVICE

    DBService * _db;

    //Function

    std::function<void()> _okFun;

private:

    enum class ID
    {
        STATUS = 1, DATA_D, DATA_M, DATA_R, OK
    };

    void onOK(wxCommandEvent & event);

};
