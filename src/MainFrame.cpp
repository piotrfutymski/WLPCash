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
    _druzynyFrame->setOnModify([&](const std::vector<std::string> & druzyna){
        if(!_druzynaForm->isOpened())
            _druzynaForm->Show();
        _druzynaForm->fillDruzynowyData(_db.getPossibleDruzynowi());
        _druzynaForm->fillHufiecData(_db.getPossibleHufce());
        _druzynaForm->fillTypData(_db.getPossibleTypyDruzyn());
        _druzynaForm->setNazwa(druzyna[0]);
        _druzynaForm->setNumer(druzyna[1]);
        _druzynaForm->setProbna(druzyna[2]);
        _druzynaForm->setPatron(druzyna[3]);
        _druzynaForm->setDruzynowy(druzyna[4]);
        _druzynaForm->setHufiec(druzyna[5]);
        _druzynaForm->setTyp(druzyna[6]);

        _druzynaForm->setModify(true);
        _druzynaForm->reload();
    });

    _druzynyFrame->setOnDel([&](const std::vector<std::string> & druzyna){
        std::unique_ptr<wxMessageDialog> dial;
        bool res = _db.deleteDruzyna(druzyna[0], druzyna[1]);
        if(res)
        {
            dial = std::make_unique<wxMessageDialog>(nullptr, wxT("Polecenie wykonane"), wxT("Info"), wxOK);
        }
        else
        {
            dial = std::make_unique<wxMessageDialog>(nullptr, wxT("Nie udało się wykonać polecenia"), wxT("Błąd"), wxOK | wxICON_ERROR);
        }
        dial->ShowModal();
        openTable("druzyny", _druzynyFrame);
    });

    _druzynyFrame->setOnAdd([&](){
       if(!_druzynaForm->isOpened())
            _druzynaForm->Show();
        _druzynaForm->fillDruzynowyData(_db.getPossibleDruzynowi());
        _druzynaForm->fillHufiecData(_db.getPossibleHufce());
        _druzynaForm->fillTypData(_db.getPossibleTypyDruzyn());
        _druzynaForm->setNazwa("");
        _druzynaForm->setNumer("");
        _druzynaForm->setPatron("");

        _hufiecForm->setModify(false);
        _hufiecForm->reload();
    });

    _druzynaForm = std::make_unique<DruzynaForm>(wxWindowID(ID::DRUZYNY)+2000, &_db);
    _druzynaForm->setOnOK([&](){
        openTable("druzyny", _druzynyFrame);
    });

    //---

    _instruktorzyFrame = std::make_unique<TableFrame>(std::string("Instruktorzy"), 850, wxWindowID(ID::INSTRUKTORZY)+1000, 
    std::vector<std::pair<std::string,int>>({{"ID",50},{"Imie",100},{"Nazwisko",100},{"E-mail",200},{"Rozkaz",100},{"St. instr.",100},{"St. harcerski",100},{"Hufiec",100}}), TableFrame::TableStyle::Special);
    
    _instruktorzyFrame->setOnModify([&](const std::vector<std::string> & instruktor){
        if(!_instruktorForm->isOpened())
            _instruktorForm->Show();
        _instruktorForm->fillStopienInstrData(_db.getPossibleStopnieInstr());
        _instruktorForm->fillstopienHarcData(_db.getPossibleStopnieHarc());
        _instruktorForm->fillHufiecData(_db.getPossibleHufce());
  
        _instruktorForm->setImie(instruktor[1]);
        _instruktorForm->setNazwisko(instruktor[2]);
        _instruktorForm->setEmail(instruktor[3]);
        _instruktorForm->setRozkaz(instruktor[4]);
        _instruktorForm->setStopienInstr(instruktor[5]);
        _instruktorForm->setStopienHarc(instruktor[6]);
        _instruktorForm->setHufiec(instruktor[7]);

        _instruktorForm->setModify(true);
        _instruktorForm->reload();
    });

    _instruktorzyFrame->setOnDel([&](const std::vector<std::string> & instruktor){
        std::unique_ptr<wxMessageDialog> dial;
        bool res = _db.deleteInstruktor(instruktor[1], instruktor[2]);
        if(res)
        {
            dial = std::make_unique<wxMessageDialog>(nullptr, wxT("Polecenie wykonane"), wxT("Info"), wxOK);
        }
        else
        {
            dial = std::make_unique<wxMessageDialog>(nullptr, wxT("Nie udało się wykonać polecenia"), wxT("Błąd"), wxOK | wxICON_ERROR);
        }
        dial->ShowModal();
        openTable("instruktorzy", _instruktorzyFrame);
    });

    _instruktorzyFrame->setOnAdd([&](){
        if(!_instruktorForm->isOpened())
            _instruktorForm->Show();
        _instruktorForm->fillStopienInstrData(_db.getPossibleStopnieInstr());
        _instruktorForm->fillstopienHarcData(_db.getPossibleStopnieHarc());
        _instruktorForm->fillHufiecData(_db.getPossibleHufce());

        _instruktorForm->setImie("");
        _instruktorForm->setNazwisko("");
        _instruktorForm->setEmail("");
        _instruktorForm->setRozkaz("");

        _instruktorForm->setModify(false);
        _instruktorForm->reload();
    });

    _instruktorzyFrame->setOnSpec([&](const std::vector<std::string> & instr){
        _stanyInstruktoraFrame->Show();
        _stanyInstruktoraFrame->fillData(_db.getStanyInstruktora(instr[1] + " " +instr[2]));
        _stanyInstruktoraFrame->reload();
        _stanyInstruktoraFrame->setValue(instr[1] + " " +instr[2]);
        _stanyInstruktoraFrame->SetTitle("Stany instruktora: " + instr[1] + " " +instr[2]);
    });

    _instruktorForm = std::make_unique<InstruktorForm>(wxWindowID(ID::INSTRUKTORZY)+2000, &_db);
    _instruktorForm->setOnOK([&](){
        openTable("instruktorzy", _instruktorzyFrame);
    });

    //---

    _stanyInstruktoraFrame = std::make_unique<TableFrame>(std::string("Stany instruktora"), 300, wxWindowID(ID::INSTRUKTORZY)+3000,
    std::vector<std::pair<std::string,int>>({{"Nazwa",100},{"Data rozp.",100},{"Data zak.",100}}), TableFrame::TableStyle::OnlyLast);

    _stanyInstruktoraFrame->setOnDel([&](const std::vector<std::string> & stan){
        std::unique_ptr<wxMessageDialog> dial;
        bool res = _db.deleteStatus(stan[1], _stanyInstruktoraFrame->getValue());
        if(res)
        {
            dial = std::make_unique<wxMessageDialog>(nullptr, wxT("Polecenie wykonane"), wxT("Info"), wxOK);
        }
        else
        {
            dial = std::make_unique<wxMessageDialog>(nullptr, wxT("Nie udało się wykonać polecenia"), wxT("Błąd"), wxOK | wxICON_ERROR);
        }
        dial->ShowModal();
        _stanyInstruktoraFrame->fillData(_db.getStanyInstruktora( _stanyInstruktoraFrame->getValue()));
        _stanyInstruktoraFrame->reload();
        
    });

    _stanyInstruktoraFrame->setOnAdd([&](){
        if(!_statusInstruktoraForm->isOpened())
            _statusInstruktoraForm->Show();

        _statusInstruktoraForm->fillStatusData(_db.getPossibleStatusy());
        _statusInstruktoraForm->setInstruktor(_stanyInstruktoraFrame->getValue());
        _statusInstruktoraForm->reload();
    });

    _statusInstruktoraForm = std::make_unique<StatusForm>(wxWindowID(ID::INSTRUKTORZY)+4000, &_db);
    _statusInstruktoraForm->setOnOK([&](){
        _stanyInstruktoraFrame->fillData(_db.getStanyInstruktora( _stanyInstruktoraFrame->getValue()));
        _stanyInstruktoraFrame->reload();
    });

    //---

    _okresyFrame = std::make_unique<TableFrame>(std::string("Okresy skladkowe"), 400, wxWindowID(ID::OKRESY)+1000,
    std::vector<std::pair<std::string,int>>({{"Poczatek okresu",150},{"Koniec okresu",150},{"Kwota",100}}), TableFrame::TableStyle::OnlyLast);
    
    _okresyFrame->setOnDel([&](const std::vector<std::string> &okres){
        std::unique_ptr<wxMessageDialog> dial;
        bool res = _db.deleteOkres(okres[0]);
        if(res)
        {
            dial = std::make_unique<wxMessageDialog>(nullptr, wxT("Polecenie wykonane"), wxT("Info"), wxOK);
        }
        else
        {
            dial = std::make_unique<wxMessageDialog>(nullptr, wxT("Nie udało się wykonać polecenia"), wxT("Błąd"), wxOK | wxICON_ERROR);
        }
        dial->ShowModal();  
        openTable("okresy", _okresyFrame);
    });

    _okresyFrame->setOnAdd([&](){
        if(!_okresForm->isOpened())
            _okresForm->Show();

        _okresForm->reload();
    });

    _okresForm = std::make_unique<OkresForm>(wxWindowID(ID::OKRESY)+2000, &_db);
    _okresForm->setOnOK([&](){
        openTable("okresy", _okresyFrame);
    });

    //---

    _chooseWplatyFrame = std::make_unique<ChooseWplatyFrame>(wxWindowID(ID::WPLATY)+1000);
    _chooseWplatyFrame->setOnConcrete([&](){
        closeAll();    
        _wplatyFrame->Show();
        _wplatyFrame->fillData(_db.getWplatyInstruktora(_chooseWplatyFrame->getInstruktor()));
        _wplatyFrame->reload();
        _wplatyFrame->setValue(_chooseWplatyFrame->getInstruktor());
    });
    _chooseWplatyFrame->setOnAll([&](){
        openTable("wplaty", _wplatyFrame);
        _wplatyFrame->setValue("-");
    });



    _wplatyFrame = std::make_unique<TableFrame>(std::string("Wplaty"), 450, wxWindowID(ID::WPLATY)+2000,
    std::vector<std::pair<std::string,int>>({{"ID",50},{"Imie",100},{"Nazwisko",100},{"Kwota",100}, {"Data",100}}));
    _wplatyFrame->setOnModify([&](const std::vector<std::string> & wplata){
        if(!_wplataForm->isOpened())
            _wplataForm->Show();
        _wplataForm->fillInstruktorData(_db.getAllInstruktorzy());

        _wplataForm->setID(wplata[0]);
        _wplataForm->setInstruktor(wplata[1]+" "+wplata[2]);
        _wplataForm->setKwota(wplata[3]);
        _wplataForm->setDataD(std::string(1, wplata[4][0]) + std::string(1, wplata[4][1]));
        _wplataForm->setDataM(std::string(1, wplata[4][3]) + std::string(1, wplata[4][4]));
        _wplataForm->setDataR(std::string(1, wplata[4][6]) + std::string(1, wplata[4][7])+ std::string(1, wplata[4][8])+ std::string(1, wplata[4][9]));

        _wplataForm->setModify(true);
        _wplataForm->reload();
    });

    _wplatyFrame->setOnDel([&](const std::vector<std::string> & wplata){
        std::unique_ptr<wxMessageDialog> dial;
        bool res = _db.deleteWplata(wplata[0]);
        if(res)
        {
            dial = std::make_unique<wxMessageDialog>(nullptr, wxT("Polecenie wykonane"), wxT("Info"), wxOK);
        }
        else
        {
            dial = std::make_unique<wxMessageDialog>(nullptr, wxT("Nie udało się wykonać polecenia"), wxT("Błąd"), wxOK | wxICON_ERROR);
        }
        dial->ShowModal();
        if(_wplatyFrame->getValue() == "-")
        {
            openTable("wplaty", _wplatyFrame);
        }
        else
        {
            closeAll();    
            _wplatyFrame->Show();
            _wplatyFrame->fillData(_db.getWplatyInstruktora(_wplatyFrame->getValue()));
            _wplatyFrame->reload();
        }
    });

    _wplatyFrame->setOnAdd([&](){
        if(!_wplataForm->isOpened())
            _wplataForm->Show();
         _wplataForm->fillInstruktorData(_db.getAllInstruktorzy());

        _wplataForm->setID("");
        _wplataForm->setKwota("");
        _wplataForm->setDataD("");
        _wplataForm->setDataM("");
        _wplataForm->setDataR("");

        _wplataForm->setModify(false);
        _wplataForm->reload();
    });

    _wplataForm = std::make_unique<WplataForm>(wxWindowID(ID::WPLATY)+3000, &_db);
    _wplataForm->setOnOK([&](){
        if(_wplatyFrame->getValue() == "-")
        {
            openTable("wplaty", _wplatyFrame);
        }
        else
        {
            closeAll();    
            _wplatyFrame->Show();
            _wplatyFrame->fillData(_db.getWplatyInstruktora(_wplatyFrame->getValue()));
            _wplatyFrame->reload();
        }
    });

    //---


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
    _chooseWplatyFrame->fillInstruktorData(_db.getAllInstruktorzy());
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