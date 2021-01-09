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
    Connect(wxWindowID(ID::DRUZYNY), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::onDruzyny));
    Connect(wxWindowID(ID::INSTRUKTORZY), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::onInstruktorzy)); 

    //FRAMES

    _hufceFrame = std::make_unique<TableFrame>(std::string("Hufce"), 300, wxWindowID(ID::HUFCE)+1000, std::vector<std::pair<std::string,int>>({{"Nazwa",120},{"Hufcowy",180}}));
    _hufceFrame->setOnAdd([&](){
        if(!_hufiecForm->isOpened())
            _hufiecForm->Show();
        _hufiecForm->reload();
    });

    _hufiecForm = std::make_unique<HufiecForm>(wxWindowID(ID::HUFCE)+2000);

    _druzynyFrame = std::make_unique<TableFrame>(std::string("Drużyny"), 830, wxWindowID(ID::DRUZYNY)+1000,
    std::vector<std::pair<std::string, int>>({{"Nazwa", 100},{"Numer",70},{"Czy probna",80},{"Patron",200},{"Druzynowy",180},{"Hufiec",100},{"Typ",100}}));
    _druzynyFrame->setOnAdd([&](){
        if(!_druzynaForm->isOpened())
            _druzynaForm->Show();
        _druzynaForm->reload();
    });

    _druzynaForm = std::make_unique<DruzynaForm>(wxWindowID(ID::DRUZYNY)+2000);

    _instruktorzyFrame = std::make_unique<TableFrame>(std::string("Instruktorzy"), 850, wxWindowID(ID::INSTRUKTORZY)+1000, 
    std::vector<std::pair<std::string,int>>({{"ID",50},{"Imie",100},{"Nazwisko",100},{"E-mail",200},{"Rozkaz",100},{"St. instr.",100},{"St. harcerski",100},{"Hufiec",100}}), TableFrame::TableStyle::Special);
    _instruktorzyFrame->setOnAdd([&](){
        if(!_instruktorForm->isOpened())
            _instruktorForm->Show();
        _instruktorForm->reload();
    });
    _instruktorzyFrame->setOnSpec([&](const std::vector<std::string> & instr){
        if(!_stanyInstruktoraFrame->isOpened())
            _stanyInstruktoraFrame->Show();
        _stanyInstruktoraFrame->reload();
        _stanyInstruktoraFrame->SetTitle("Stany instruktora: " + instr[1] + " " +instr[2]);
    });

    _instruktorForm = std::make_unique<InstruktorForm>(wxWindowID(ID::INSTRUKTORZY)+2000);


    _stanyInstruktoraFrame = std::make_unique<TableFrame>(std::string("Stany instruktora"), 300, wxWindowID(ID::INSTRUKTORZY)+3000,
    std::vector<std::pair<std::string,int>>({{"Nazwa",100},{"Data rozp.",100},{"Data zak.",100}}), TableFrame::TableStyle::OnlyLast);
    _stanyInstruktoraFrame->setOnAdd([&](){
        if(!_statusInstruktoraForm->isOpened())
            _statusInstruktoraForm->Show();
        _statusInstruktoraForm->reload();
    });


    _statusInstruktoraForm = std::make_unique<StatusForm>(wxWindowID(ID::INSTRUKTORZY)+4000);
    

}

void MainFrame::onHufce(wxCommandEvent& WXUNUSED(event))
{
    openTable("hufce", _hufceFrame);
}

void MainFrame::onDruzyny(wxCommandEvent & event)
{
    openTable("druzyny", _druzynyFrame);
}

void MainFrame::onInstruktorzy(wxCommandEvent& WXUNUSED(event))
{
    openTable("instruktorzy", _instruktorzyFrame);
}

void MainFrame::openTable(const std::string & name,  std::unique_ptr<TableFrame> & frame)
{
    if(!frame->isOpened())     
        frame->Show();

    DBService testService;
    frame->fillData(testService.getData(name));
    frame->reload();
}