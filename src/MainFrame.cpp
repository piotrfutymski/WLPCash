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
    Connect(wxWindowID(ID::RESET_WPLAT), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::onResetWplat)); 

    Connect(9912, wxEVT_CLOSE_WINDOW, wxCommandEventHandler(MainFrame::close));

    //FRAMES

    //---

    _hufceFrame = std::make_unique<TableFrame>(std::wstring(L"Hufce"), 300, wxWindowID(ID::HUFCE)+1000, std::vector<std::pair<std::wstring,int>>({{L"Nazwa",120},{L"Hufcowy",180}}));
    _hufceFrame->setOnModify([&](const std::vector<std::wstring> & hufiec){
        if(!_hufiecForm->isOpened())
            _hufiecForm->Show();
        _hufiecForm->fillHufocowyData(_db.getPossibleHufcowi());
        _hufiecForm->setNazwa(hufiec[0]);
        _hufiecForm->setHufcowy(hufiec[1]);
        _hufiecForm->setModify(true);
        _hufiecForm->reload();
    });

    _hufceFrame->setOnDel([&](const std::vector<std::wstring> & hufiec){
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
        openTable(L"hufce", _hufceFrame);
    });


    _hufceFrame->setOnAdd([&](){
       if(!_hufiecForm->isOpened())
            _hufiecForm->Show();
        _hufiecForm->fillHufocowyData(_db.getPossibleHufcowi());
        _hufiecForm->setNazwa(L"");
        _hufiecForm->setModify(false);
        _hufiecForm->reload();
    });

    _hufiecForm = std::make_unique<HufiecForm>(wxWindowID(ID::HUFCE)+2000, &_db);
    _hufiecForm->setOnOK([&](){
        openTable(L"hufce", _hufceFrame);
    });

    //---

    _druzynyFrame = std::make_unique<TableFrame>(std::wstring(L"Drużyny"), 830, wxWindowID(ID::DRUZYNY)+1000,
    std::vector<std::pair<std::wstring, int>>({{L"Nazwa", 100},{L"Numer",70},{L"Czy próbna",80},{L"Patron",200},{L"Drużynowy",180},{L"Hufiec",100},{L"Typ",100}}));
    _druzynyFrame->setOnModify([&](const std::vector<std::wstring> & druzyna){
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

    _druzynyFrame->setOnDel([&](const std::vector<std::wstring> & druzyna){
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
        openTable(L"druzyny", _druzynyFrame);
    });

    _druzynyFrame->setOnAdd([&](){
       if(!_druzynaForm->isOpened())
            _druzynaForm->Show();
        _druzynaForm->fillDruzynowyData(_db.getPossibleDruzynowi());
        _druzynaForm->fillHufiecData(_db.getPossibleHufce());
        _druzynaForm->fillTypData(_db.getPossibleTypyDruzyn());
        _druzynaForm->setNazwa(L"");
        _druzynaForm->setNumer(L"");
        _druzynaForm->setPatron(L"");

        _druzynaForm->setModify(false);
        _druzynaForm->reload();
    });

    _druzynaForm = std::make_unique<DruzynaForm>(wxWindowID(ID::DRUZYNY)+2000, &_db);
    _druzynaForm->setOnOK([&](){
        openTable(L"druzyny", _druzynyFrame);
    });

    //---

    _instruktorzyFrame = std::make_unique<TableFrame>(std::wstring(L"Instruktorzy"), 850, wxWindowID(ID::INSTRUKTORZY)+1000, 
    std::vector<std::pair<std::wstring,int>>({{L"ID",50},{L"Imię",100},{L"Nazwisko",100},{L"E-mail",200},{L"Rozkaz",100},{L"St. instr.",100},{L"St. harcerski",100},{L"Hufiec",100}}), TableFrame::TableStyle::Special);
    
    _instruktorzyFrame->setOnModify([&](const std::vector<std::wstring> & instruktor){
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

    _instruktorzyFrame->setOnDel([&](const std::vector<std::wstring> & instruktor){
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
        openTable(L"instruktorzy", _instruktorzyFrame);
    });

    _instruktorzyFrame->setOnAdd([&](){
        if(!_instruktorForm->isOpened())
            _instruktorForm->Show();
        _instruktorForm->fillStopienInstrData(_db.getPossibleStopnieInstr());
        _instruktorForm->fillstopienHarcData(_db.getPossibleStopnieHarc());
        _instruktorForm->fillHufiecData(_db.getPossibleHufce());

        _instruktorForm->setImie(L"");
        _instruktorForm->setNazwisko(L"");
        _instruktorForm->setEmail(L"");
        _instruktorForm->setRozkaz(L"");

        _instruktorForm->setModify(false);
        _instruktorForm->reload();
    });

    _instruktorzyFrame->setOnSpec([&](const std::vector<std::wstring> & instr){
        _stanyInstruktoraFrame->Show();
        _stanyInstruktoraFrame->fillData(_db.getStanyInstruktora(instr[1] + L" " +instr[2]));
        _stanyInstruktoraFrame->reload();
        _stanyInstruktoraFrame->setValue(instr[1] + L" " +instr[2]);
        _stanyInstruktoraFrame->SetTitle(L"Stany instruktora: " + instr[1] + L" " +instr[2]);
    });

    _instruktorForm = std::make_unique<InstruktorForm>(wxWindowID(ID::INSTRUKTORZY)+2000, &_db);
    _instruktorForm->setOnOK([&](){
        openTable(L"instruktorzy", _instruktorzyFrame);
    });

    //---

    _stanyInstruktoraFrame = std::make_unique<TableFrame>(std::wstring(L"Stany instruktora"), 300, wxWindowID(ID::INSTRUKTORZY)+3000,
    std::vector<std::pair<std::wstring,int>>({{L"Nazwa",100},{L"Data rozp.",100},{L"Data zak.",100}}), TableFrame::TableStyle::OnlyLast);

    _stanyInstruktoraFrame->setOnDel([&](const std::vector<std::wstring> & stan){
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

    _okresyFrame = std::make_unique<TableFrame>(std::wstring(L"Okresy skladkowe"), 400, wxWindowID(ID::OKRESY)+1000,
    std::vector<std::pair<std::wstring,int>>({{L"Początek okresu",150},{L"Koniec okresu",150},{L"Kwota[zł]",100}}), TableFrame::TableStyle::OnlyLast);
    
    _okresyFrame->setOnDel([&](const std::vector<std::wstring> &okres){
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
        openTable(L"okresy", _okresyFrame);
    });

    _okresyFrame->setOnAdd([&](){
        if(!_okresForm->isOpened())
            _okresForm->Show();

        _okresForm->reload();
    });

    _okresForm = std::make_unique<OkresForm>(wxWindowID(ID::OKRESY)+2000, &_db);
    _okresForm->setOnOK([&](){
        openTable(L"okresy", _okresyFrame);
    });

    //---

    _chooseWplatyFrame = std::make_unique<ChooseWplatyFrame>(wxWindowID(ID::WPLATY)+1000);
    _chooseWplatyFrame->setOnConcrete([&](){
        closeAll();    
        _wplatyFrame->Show();
        auto data = _db.getWplatyInstruktora(_chooseWplatyFrame->getInstruktor());
        _wplatyFrame->fillData(data);
        _wplatyFrame->reload();
        _wplatyFrame->setValue(_chooseWplatyFrame->getInstruktor());
    });
    _chooseWplatyFrame->setOnAll([&](){
        openTable(L"wplaty", _wplatyFrame);
        _wplatyFrame->setValue(L"-");
    });



    _wplatyFrame = std::make_unique<TableFrame>(std::wstring(L"Wpłaty"), 450, wxWindowID(ID::WPLATY)+2000,
    std::vector<std::pair<std::wstring,int>>({{L"ID",50},{L"Imie",100},{L"Nazwisko",100},{L"Kwota[zł]",100}, {L"Data",100}}));
    _wplatyFrame->setOnModify([&](const std::vector<std::wstring> & wplata){
        if(!_wplataForm->isOpened())
            _wplataForm->Show();
        _wplataForm->fillInstruktorData(_db.getAllInstruktorzy());

        _wplataForm->setID(wplata[0]);
        _wplataForm->setInstruktor(wplata[1]+L" "+wplata[2]);
        _wplataForm->setKwota(wplata[3]);
        _wplataForm->setDataD(std::wstring(1, wplata[4][0]) + std::wstring(1, wplata[4][1]));
        _wplataForm->setDataM(std::wstring(1, wplata[4][3]) + std::wstring(1, wplata[4][4]));
        _wplataForm->setDataR(std::wstring(1, wplata[4][6]) + std::wstring(1, wplata[4][7])+ std::wstring(1, wplata[4][8])+ std::wstring(1, wplata[4][9]));

        _wplataForm->setModify(true);
        _wplataForm->reload();
    });

    _wplatyFrame->setOnDel([&](const std::vector<std::wstring> & wplata){
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
            openTable(L"wplaty", _wplatyFrame);
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

        _wplataForm->setID(L"");
        _wplataForm->setKwota(L"");
        _wplataForm->setDataD(L"");
        _wplataForm->setDataM(L"");
        _wplataForm->setDataR(L"");

        _wplataForm->setModify(false);
        _wplataForm->reload();
    });

    _wplataForm = std::make_unique<WplataForm>(wxWindowID(ID::WPLATY)+3000, &_db);
    _wplataForm->setOnOK([&](){
        if(_wplatyFrame->getValue() == L"-")
        {
            openTable(L"wplaty", _wplatyFrame);
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
    _raportyFrame->setOnGenerate([&](const std::vector<std::wstring> & dat){
        _raportWplatIndFrame->fillData(_db.getWplatyIndData(dat));
        openPopUp(_raportWplatIndFrame.get());
    }, 0);
    _raportyFrame->setOnGenerate([&](const std::vector<std::wstring> & dat){
        _raportWplatHufFrame->fillData(_db.getWplatyHufData(dat));
        openPopUp(_raportWplatHufFrame.get());
    }, 1);
    _raportyFrame->setOnGenerate([&](const std::vector<std::wstring> & dat){
        _raportUzupelnienFrame->fillData(_db.getUzupelnieniaData());
        openPopUp(_raportUzupelnienFrame.get());
    }, 2);
    _raportyFrame->setOnGenerate([&](const std::vector<std::wstring> & dat){
        _raportUzupelnienFrame->fillData(_db.getOpoznieniaData(dat));
        openPopUp(_raportUzupelnienFrame.get());
    }, 3);


    _raportWplatIndFrame = std::make_unique<TableFrame>(std::wstring(L"Raport wpłat indywidualnych"), 650, wxWindowID(ID::RAPORTY)+2000,
    std::vector<std::pair<std::wstring,int>>({{L"Imię",100},{L"Nazwisko",100},{L"E-Mail",150}, {L"St. instr.",100}, {L"Hufiec", 100}, {L"SUMA [zł]", 100}}), TableFrame::TableStyle::Raport);

    _raportWplatHufFrame = std::make_unique<TableFrame>(std::wstring(L"Raport wpłat w hufcach"), 200, wxWindowID(ID::RAPORTY)+3000,
    std::vector<std::pair<std::wstring,int>>({{L"Nazwa",100}, {L"SUMA [zł]", 100}}), TableFrame::TableStyle::Raport);

    _raportUzupelnienFrame = std::make_unique<TableFrame>(std::wstring(L"Raport opóźnień"), 700, wxWindowID(ID::RAPORTY)+4000,
    std::vector<std::pair<std::wstring,int>>({{L"Imię",100},{L"Nazwisko",100},{L"E-Mail",150}, {L"St. instr.",100}, {L"Hufiec", 100}, {L"Do kiedy opłacono", 150}}), TableFrame::TableStyle::Raport);

    //---
    
    _resetFrame = std::make_unique<ResetFrame>(wxWindowID(ID::RESET_BAZY)+1000, &_db);

}

void MainFrame::onHufce(wxCommandEvent& WXUNUSED(event))
{
    openTable(L"hufce", _hufceFrame);
}

void MainFrame::onDruzyny(wxCommandEvent & event)
{
    openTable(L"druzyny", _druzynyFrame);
}

void MainFrame::onInstruktorzy(wxCommandEvent& WXUNUSED(event))
{
    openTable(L"instruktorzy", _instruktorzyFrame);
}

void MainFrame::onOkresy(wxCommandEvent & event)
{
    openTable(L"okresy", _okresyFrame);
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
    _resetFrame->setOnlyWplaty(false);
}

void MainFrame::onResetWplat(wxCommandEvent & event)
{
    this->closeAll();
    openPopUp(_resetFrame.get());
    _resetFrame->setOnlyWplaty(true);
}

void MainFrame::openTable(const std::wstring & name,  std::unique_ptr<TableFrame> & frame)
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
