#pragma once
#include "PopUpFrame.h"
#include "DBService.h"

class DruzynaForm : public PopUpFrame
{
public:
    DruzynaForm(int ID, DBService * db);

    virtual void reload();

    void fillDruzynowyData(const std::vector<std::string> & hD);
    void fillHufiecData(const std::vector<std::string> & hD);
    void fillTypData(const std::vector<std::string> & hD);

    void setNazwa(const std::string & s);
    void setNumer(const std::string & s);
    void setProbna(const std::string & s);
    void setPatron(const std::string & s);
    void setDruzynowy(const std::string & s);
    void setHufiec(const std::string & s);
    void setTyp(const std::string & s);


    void setModify(bool m);
    void setOnOK(const std::function<void()> & f);


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

    //DATA

    std::string _nazwa;
    std::string _numer;
    std::string _probna;
    std::string _patron;
    std::string _druzynowy;
    std::string _hufiec;
    std::string _typ;

    std::vector<std::string> _druzynowyData;
    std::vector<std::string> _hufiecData;
    std::vector<std::string> _typData;

    //MODE

    bool _modify;

    //SERVICE

    DBService * _db;

    //Function

    std::function<void()> _okFun;


private:

    enum class ID
    {
        NAZWA = 1, NUMER, PROBNA, PATRON, DRUZYNOWY, HUFIEC, TYP, OK
    };

    void onOK(wxCommandEvent & event);

};