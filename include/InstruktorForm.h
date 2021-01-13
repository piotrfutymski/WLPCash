#pragma once
#include "PopUpFrame.h"
#include "DBService.h"

class InstruktorForm : public PopUpFrame
{
public:
    InstruktorForm(int ID, DBService * db);

    virtual void reload();
    
    void fillStopienInstrData(const std::vector<std::string> & hD);
    void fillstopienHarcData(const std::vector<std::string> & hD);
    void fillHufiecData(const std::vector<std::string> & hD);

    void setImie(const std::string & s);
    void setNazwisko(const std::string & s);
    void setEmail(const std::string & s);
    void setRozkaz(const std::string & s);
    void setStopienInstr(const std::string & s);
    void setStopienHarc(const std::string & s);
    void setHufiec(const std::string & s);

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

    std::string _imie;
    std::string _nazwisko;
    std::string _email;
    std::string _rozkaz;
    std::string _stopienInstr;
    std::string _stopienHarc;
    std::string _hufiec;

    std::vector<std::string> _stopienInstrData;
    std::vector<std::string> _stopienHarcData;
    std::vector<std::string> _hufiecData;
    
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