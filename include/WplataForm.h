#pragma once
#include "PopUpFrame.h"
#include "DBService.h"

class WplataForm : public PopUpFrame
{
public:
    WplataForm(int ID, DBService * db);

    virtual void reload();

    void fillInstruktorData(const std::vector<std::string> & hD);

    void setInstruktor(const std::string & s);
    void setKwota(const std::string & s);
    void setDataD(const std::string & s);
    void setDataM(const std::string & s);
    void setDataR(const std::string & s);
    void setID(const std::string & s);

    void setModify(bool m);
    void setOnOK(const std::function<void()> & f);

private:

    //GUI

    std::unique_ptr<wxPanel> _panel;

    std::unique_ptr<wxStaticText> _instruktorLabel;
    std::unique_ptr<wxStaticText> _kwotaLabel;
    std::unique_ptr<wxStaticText> _dataLabel;

    std::unique_ptr<wxListBox> _instruktorInput;
    std::unique_ptr<wxTextCtrl> _kwotaInput;
    std::unique_ptr<wxTextCtrl> _dataDInput;
    std::unique_ptr<wxTextCtrl> _dataMInput;
    std::unique_ptr<wxTextCtrl> _dataRInput;

    std::unique_ptr<wxButton> _okButton;

    //DATA

    std::string _instruktor;
    std::string _kwota;
    std::string _dataD;
    std::string _dataM;
    std::string _dataR;

    std::string _id;

    std::vector<std::string> _instruktorData;

    
    //MODE

    bool _modify;

    //SERVICE

    DBService * _db;

    //Function

    std::function<void()> _okFun;

private:

    enum class ID
    {
        INSTRUKTOR = 1, KWOTA, DATA_D, DATA_M, DATA_R, OK
    };

    void onOK(wxCommandEvent & event);

};