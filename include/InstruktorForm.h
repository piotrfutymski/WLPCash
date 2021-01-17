#pragma once
#include "PopUpFrame.h"
#include "DBService.h"

class InstruktorForm : public PopUpFrame
{
public:
    InstruktorForm(int ID, DBService * db);

    virtual void reload();
    
    void fillStopienInstrData(const std::vector<std::wstring> & hD);
    void fillstopienHarcData(const std::vector<std::wstring> & hD);
    void fillHufiecData(const std::vector<std::wstring> & hD);

    void setImie(const std::wstring & s);
    void setNazwisko(const std::wstring & s);
    void setEmail(const std::wstring & s);
    void setRozkaz(const std::wstring & s);
    void setStopienInstr(const std::wstring & s);
    void setStopienHarc(const std::wstring & s);
    void setHufiec(const std::wstring & s);

    void setModify(bool m);
    void setOnOK(const std::function<void()> & f);

private:

    //GUI

    std::unique_ptr<wxPanel> _panel;

    std::unique_ptr<wxStaticText> _imieLabel;
    std::unique_ptr<wxStaticText> _nazwiskoLabel;
    std::unique_ptr<wxStaticText> _emailLabel;
    std::unique_ptr<wxStaticText> _rozkazLabel;
    std::unique_ptr<wxStaticText> _stopienInstrLabel;
    std::unique_ptr<wxStaticText> _stopienHarcLabel;
    std::unique_ptr<wxStaticText> _hufiecLabel;
    std::unique_ptr<wxStaticText> _dataLabel;
    
    std::unique_ptr<wxTextCtrl> _imieInput;
    std::unique_ptr<wxTextCtrl> _nazwiskoInput;
    std::unique_ptr<wxTextCtrl> _emailInput;
    std::unique_ptr<wxTextCtrl> _rozkazInput;
    std::unique_ptr<wxListBox> _stopienInstrInput;
    std::unique_ptr<wxListBox> _stopienHarcInput;
    std::unique_ptr<wxListBox> _hufiecInput;
    std::unique_ptr<wxTextCtrl> _dataDInput;
    std::unique_ptr<wxTextCtrl> _dataMInput;
    std::unique_ptr<wxTextCtrl> _dataRInput;

    std::unique_ptr<wxButton> _okButton;

    //DATA

    std::wstring _imie;
    std::wstring _nazwisko;
    std::wstring _email;
    std::wstring _rozkaz;
    std::wstring _stopienInstr;
    std::wstring _stopienHarc;
    std::wstring _hufiec;

    std::vector<std::wstring> _stopienInstrData;
    std::vector<std::wstring> _stopienHarcData;
    std::vector<std::wstring> _hufiecData;
    
    //MODE

    bool _modify;

    //SERVICE

    DBService * _db;

    //Function

    std::function<void()> _okFun;

private:

    enum class ID
    {
        IMIE = 1, NAZWISKO, EMAIL, ROZKAZ, STOPIEN_INSTR, STOPIEN_HARC, HUFIEC, DATA_D, DATA_M, DATA_R, OK
    };

    void onOK(wxCommandEvent & event);


};
