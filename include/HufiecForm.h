#pragma once
#include <functional>
#include "PopUpFrame.h"
#include "DBService.h"

class HufiecForm : public PopUpFrame
{
public:
    HufiecForm(int ID, DBService * service);

    virtual void reload();

    void fillHufocowyData(const std::vector<std::string> & hD);

    void setNazwa(const std::string & s);
    void setHufcowy(const std::string & s);

    void setModify(bool m);
    void setOnOK(const std::function<void()> & f);


private:

    //GUI

    std::unique_ptr<wxPanel> _panel;

    std::unique_ptr<wxStaticText> _nazwaLabel;
    std::unique_ptr<wxStaticText> _hufcowyLabel;
    
    std::unique_ptr<wxTextCtrl> _nazwaInput;
    std::unique_ptr<wxListBox> _hufcowyInput;

    std::unique_ptr<wxButton> _okButton;

    //DATA

    std::string _nazwa;
    std::string _hufcowy;
    std::vector<std::string> _hufcowyData;

    //MODE

    bool _modify;

    //SERVICE

    DBService * _db;

    //Function

    std::function<void()> _okFun;

private:

    enum class ID
    {
        NAZWA = 1, HUFCOWY, OK
    };

    void onOK(wxCommandEvent & event);


};