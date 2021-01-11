#pragma once
#include "TableFrame.h"
#include "HufiecForm.h"
#include "DruzynaForm.h"
#include "InstruktorForm.h"
#include "StatusForm.h"
#include "OkresForm.h"
#include "ChooseWplatyFrame.h"
#include "WplataForm.h"
#include "RaportyFrame.h"
#include "ResetFrame.h"
#include "DBService.h"

class MainFrame : public wxFrame
{
public:

    MainFrame();

private:
    //DATABASE OBJECT
    //DBService _db;

    // GUI ELEMENTS

    std::unique_ptr<wxPanel> _panel;

    std::unique_ptr<wxButton> _hufceButton;
    std::unique_ptr<wxButton> _druzynyButton;
    std::unique_ptr<wxButton> _instruktorzyButton;
    std::unique_ptr<wxButton> _okresyButton;
    std::unique_ptr<wxButton> _wplatyButton;
    std::unique_ptr<wxButton> _raportyButton;
    std::unique_ptr<wxButton> _resetBazyButton;
    std::unique_ptr<wxButton> _resetWplatButton;

    // CHILD FRAMES

    std::unique_ptr<TableFrame> _hufceFrame;
    std::unique_ptr<HufiecForm> _hufiecForm;

    std::unique_ptr<TableFrame> _druzynyFrame;
    std::unique_ptr<DruzynaForm> _druzynaForm;

    std::unique_ptr<TableFrame> _instruktorzyFrame;
    std::unique_ptr<InstruktorForm> _instruktorForm;

    std::unique_ptr<TableFrame> _stanyInstruktoraFrame;
    std::unique_ptr<StatusForm> _statusInstruktoraForm;

    std::unique_ptr<TableFrame> _okresyFrame;
    std::unique_ptr<OkresForm>  _okresForm;

    std::unique_ptr<ChooseWplatyFrame> _chooseWplatyFrame;
    std::unique_ptr<TableFrame> _wplatyFrame;
    std::unique_ptr<WplataForm> _wplataForm;

    std::unique_ptr<RaportyFrame> _raportyFrame;
    std::unique_ptr<TableFrame> _raportWplatIndFrame;
    std::unique_ptr<TableFrame> _raportWplatHufFrame;
    std::unique_ptr<TableFrame> _raportUzupelnienFrame;

    std::unique_ptr<ResetFrame> _resetFrame;

private:

    enum class ID
    {
        HUFCE = 1, DRUZYNY, INSTRUKTORZY, OKRESY,
        WPLATY, RAPORTY, RESET_BAZY, RESET_WPLAT
    };

private:

    void onHufce(wxCommandEvent & event);
    void onInstruktorzy(wxCommandEvent & event);
    void onDruzyny(wxCommandEvent & event);
    void onOkresy(wxCommandEvent & event);
    void onWplaty(wxCommandEvent & event);
    void onRaporty(wxCommandEvent & event);
    void onResetBazy(wxCommandEvent & event);

    void openTable(const std::string & name,  std::unique_ptr<TableFrame> & frame);
    void openPopUp(PopUpFrame * frame);

    void closeAll();

};

