#pragma once
#include "PopUpFrame.h"
#include "DBService.h"

class DruzynaForm : public PopUpFrame
{
public:
    DruzynaForm(int ID, DBService * db);

    virtual void reload();

    void fillDruzynowyData(const std::vector<std::wstring> & hD);
    void fillHufiecData(const std::vector<std::wstring> & hD);
    void fillTypData(const std::vector<std::wstring> & hD);

    void setNazwa(const std::wstring & s);
    void setNumer(const std::wstring & s);
    void setProbna(const std::wstring & s);
    void setPatron(const std::wstring & s);
    void setDruzynowy(const std::wstring & s);
    void setHufiec(const std::wstring & s);
    void setTyp(const std::wstring & s);


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

    std::wstring _nazwa;
    std::wstring _numer;
    std::wstring _probna;
    std::wstring _patron;
    std::wstring _druzynowy;
    std::wstring _hufiec;
    std::wstring _typ;

    std::vector<std::wstring> _druzynowyData;
    std::vector<std::wstring> _hufiecData;
    std::vector<std::wstring> _typData;

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
