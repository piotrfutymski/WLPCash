#include "MainFrame.h"

MainFrame::MainFrame()
    : wxFrame(NULL, 9912, "WLP Cash", wxDefaultPosition, {280,440}, wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX))
{
    _db.init();

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
    Connect(wxWindowID(ID::OKRESY), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::onOkresy));  
    Connect(wxWindowID(ID::WPLATY), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::onWplaty)); 
    Connect(wxWindowID(ID::RAPORTY), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::onRaporty)); 
    Connect(wxWindowID(ID::RESET_BAZY), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::onResetBazy)); 

    Connect(9912, wxEVT_CLOSE_WINDOW, wxCommandEventHandler(MainFrame::close));

    //FRAMES

    //---

    _hufceFrame = std::make_unique<TableFrame>(std::string("Hufce"), 300, wxWindowID(ID::HUFCE)+1000, std::vector<std::pair<std::string,int>>({{"Nazwa",120},{"Hufcowy",180}}));
    _hufceFrame->setOnModify([&](const std::vector<std::string> & hufiec){
        if(!_hufiecForm->isOpened())
            _hufiecForm->Show();
        _hufiecForm->fillHufocowyData(_db.getPossibleHufcowi());
        _hufiecForm->setNazwa(hufiec[0]);
        _hufiecForm->setHufcowy(hufiec[1]);
        _hufiecForm->setModify(true);
        _hufiecForm->reload();
    });

    _hufceFrame->setOnDel([&](const std::vector<std::string> & hufiec){
        std::unique_ptr<wxMessageDialog> dial;
        bool res = _db.deleteHufiec(hufiec[0]);
        if(res)
        {
            dial = std::make_unique<wxMessageDialog>(nullptr, wxT("Polecenie wykonane"), wxT("Info"), wxOK);
        }
        else
        {
            dial = std::make_unique<wxMessageDialog>(nullptr, wxT("Nie udało się wykonać polecenia"), wxT("Błąd"), wxOK | wxICON_ERROR);
        }
        dial->ShowModal();
        openTable("hufce", _hufceFrame);
    });


    _hufceFrame->setOnAdd([&](){
       if(!_hufiecForm->isOpened())
            _hufiecForm->Show();
        _hufiecForm->fillHufocowyData(_db.getPossibleHufcowi());
        _hufiecForm->setNazwa("");
        _hufiecForm->setModify(false);
        _hufiecForm->reload();
    });

    _hufiecForm = std::make_unique<HufiecForm>(wxWindowID(ID::HUFCE)+2000, &_db);
    _hufiecForm->setOnOK([&](){
        openTable("hufce", _hufceFrame);
    });

    //---



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

    _okresyFrame = std::make_unique<TableFrame>(std::string("Okresy skladkowe"), 400, wxWindowID(ID::OKRESY)+1000,
    std::vector<std::pair<std::string,int>>({{"Poczatek okresu",150},{"Koniec okresu",150},{"Kwota",100}}), TableFrame::TableStyle::OnlyLast);
    _okresyFrame->setOnAdd([&](){
        if(!_okresForm->isOpened())
            _okresForm->Show();
        _okresForm->reload();
    });

    _okresForm = std::make_unique<OkresForm>(wxWindowID(ID::OKRESY)+2000);

    _chooseWplatyFrame = std::make_unique<ChooseWplatyFrame>(wxWindowID(ID::WPLATY)+1000);
    _chooseWplatyFrame->setOnAll([&](){
        openTable("wplaty", _wplatyFrame);
    });

    _wplatyFrame = std::make_unique<TableFrame>(std::string("Wplaty"), 400, wxWindowID(ID::WPLATY)+2000,
    std::vector<std::pair<std::string,int>>({{"Imie",100},{"Nazwisko",100},{"Kwota",100}, {"Data",100}}));
    _wplatyFrame->setOnAdd([&](){
        if(!_wplataForm->isOpened())
            _wplataForm->Show();
        _wplataForm->reload();
    });

    _wplataForm = std::make_unique<WplataForm>(wxWindowID(ID::WPLATY)+3000);


    _raportyFrame = std::make_unique<RaportyFrame>(wxWindowID(ID::RAPORTY)+1000);
    _raportyFrame->setOnGenerate([&](){
        openPopUp(_raportWplatIndFrame.get());
    }, 0);
    _raportyFrame->setOnGenerate([&](){
        openPopUp(_raportWplatHufFrame.get());
    }, 1);
    _raportyFrame->setOnGenerate([&](){
        openPopUp(_raportUzupelnienFrame.get());
    }, 2);


    _raportWplatIndFrame = std::make_unique<TableFrame>(std::string("Raport wpłat indywidualnych"), 650, wxWindowID(ID::RAPORTY)+2000,
    std::vector<std::pair<std::string,int>>({{"Imie",100},{"Nazwisko",100},{"E-Mail",150}, {"St. instr.",100}, {"Hufiec", 100}, {"SUMA [zl]", 100}}), TableFrame::TableStyle::Raport);

    _raportWplatHufFrame = std::make_unique<TableFrame>(std::string("Raport wpłat w hufcach"), 200, wxWindowID(ID::RAPORTY)+3000,
    std::vector<std::pair<std::string,int>>({{"Nazwa",100}, {"SUMA [zl]", 100}}), TableFrame::TableStyle::Raport);

    _raportUzupelnienFrame = std::make_unique<TableFrame>(std::string("Raport opóźnień"), 700, wxWindowID(ID::RAPORTY)+4000,
    std::vector<std::pair<std::string,int>>({{"Imie",100},{"Nazwisko",100},{"E-Mail",150}, {"St. instr.",100}, {"Hufiec", 100}, {"Do kiedy oplacono", 150}}), TableFrame::TableStyle::Raport);

    
    _resetFrame = std::make_unique<ResetFrame>(wxWindowID(ID::RESET_BAZY)+1000);



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

void MainFrame::onOkresy(wxCommandEvent & event)
{
    openTable("okresy", _okresyFrame);
}

void MainFrame::onWplaty(wxCommandEvent & event)
{
    this->closeAll();
    openPopUp(_chooseWplatyFrame.get());
}

void MainFrame::onRaporty(wxCommandEvent & event)
{
    this->closeAll();
    openPopUp(_raportyFrame.get());
}

void MainFrame::onResetBazy(wxCommandEvent & event)
{
    this->closeAll();
    openPopUp(_resetFrame.get());
}


void MainFrame::openTable(const std::string & name,  std::unique_ptr<TableFrame> & frame)
{
    this->closeAll();    
    frame->Show();
    frame->fillData(_db.getTableData(name));
    frame->reload();
}

void MainFrame::openPopUp(PopUpFrame * frame)
{
    if(!frame->isOpened())
            frame->Show();
    
    frame->reload();
}

void MainFrame::closeAll()
{
    _hufceFrame->Close();
    _hufiecForm->Close();

    _druzynyFrame->Close();
    _druzynaForm->Close();

    _instruktorzyFrame->Close();
    _instruktorForm->Close();

    _stanyInstruktoraFrame->Close();
    _statusInstruktoraForm->Close();

    _okresyFrame->Close();
    _okresForm->Close();

    _chooseWplatyFrame->Close();
    _wplatyFrame->Close();
    _wplataForm->Close();

    _raportyFrame->Close();
    _raportWplatIndFrame->Close();
    _raportWplatHufFrame->Close();
    _raportUzupelnienFrame->Close();

    _resetFrame->Close();
}

void MainFrame::close(wxCommandEvent & event)
{
    _db.close();
    wxFrame::Destroy();
}