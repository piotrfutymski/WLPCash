#include "MainFrame.h"

MainFrame::MainFrame()
    : wxFrame(NULL, wxID_ANY, "WLP Cash", wxDefaultPosition, {280,440}, wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX))
{
    _panel = std::make_unique<wxPanel>(this, -1);

    wxSize normalButtonSize = {240,50};

    wxSize smallButtonSize = {100,50};

    _hufceButton = std::make_unique<wxButton>(_panel.get(), wxWindowID(ID::HUFCE), wxT("HUFCE"), wxPoint(20,20), normalButtonSize);
    _druzynyButton = std::make_unique<wxButton>(_panel.get(), wxWindowID(ID::DRUZYNY), wxT("DRUŻYNY"), wxPoint(20,70), normalButtonSize);
    _instruktorzyButton = std::make_unique<wxButton>(_panel.get(), wxWindowID(ID::INSTRUKTORZY), wxT("INSTRUKTORZY"), wxPoint(20,120), normalButtonSize);
    _okresyButton = std::make_unique<wxButton>(_panel.get(), wxWindowID(ID::OKRESY), wxT("OKRESY SKŁADKOWE"), wxPoint(20,170), normalButtonSize);
    _wplatyButton = std::make_unique<wxButton>(_panel.get(), wxWindowID(ID::WPLATY), wxT("WPŁATY"), wxPoint(20,220), normalButtonSize);
    _raportyButton = std::make_unique<wxButton>(_panel.get(), wxWindowID(ID::RAPORTY), wxT("RAPORTY"), wxPoint(20,270), normalButtonSize);

    _resetBazyButton = std::make_unique<wxButton>(_panel.get(), wxWindowID(ID::RESET_BAZY), wxT("Reset Bazy"), wxPoint(20,340), smallButtonSize);
    _resetWplatButton = std::make_unique<wxButton>(_panel.get(), wxWindowID(ID::RESET_WPLAT), wxT("Reset Wpłat"), wxPoint(160,340), smallButtonSize);

    //EVENTS

    Connect(wxWindowID(ID::HUFCE), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::onHufce));
    Connect(wxWindowID(ID::INSTRUKTORZY), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::onInstruktorzy));

    //FRAMES

    _hufceFrame = std::make_unique<TableFrame>(std::string("Hufce"), 300, wxWindowID(ID::HUFCE)+1000, std::vector<std::pair<std::string,int>>({{"Nazwa",120},{"Hufcowy",180}}));
    _instruktorzyFrame = std::make_unique<TableFrame>(std::string("Instruktorzy"), 850, wxWindowID(ID::INSTRUKTORZY)+1000, 
    std::vector<std::pair<std::string,int>>({{"ID",50},{"Imie",100},{"Nazwisko",100},{"E-mail",200},{"Rozkaz",100},{"St. instr.",100},{"St. harcerski",100},{"Hufiec",100}}), true);
}

void MainFrame::onHufce(wxCommandEvent& WXUNUSED(event))
{
    if(!_hufceFrame->isOpened())
    {
        DBService testService;
        _hufceFrame->Show();
        _hufceFrame->fillData(testService.getHufceData());
        _hufceFrame->reload();
    }
}

void MainFrame::onInstruktorzy(wxCommandEvent& WXUNUSED(event))
{
    if(!_instruktorzyFrame->isOpened())
    {
        DBService testService;
        _instruktorzyFrame->Show();
        _instruktorzyFrame->fillData(testService.getInstruktorzyData());
        _instruktorzyFrame->reload();
    }
}