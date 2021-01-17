#pragma once
#include <vector>
#include <string>
#include <soci/soci.h>
#include <soci/odbc/soci-odbc.h>
#include <iostream>
#include "DateConverter.h"
#define MAX_ROWS 1000


class DBService
{
public:
    void init();
    void close();

    //SELECT FUNCTIONS (getting data from database)

    std::vector<std::vector<std::wstring>> getTableData(const std::wstring & s);
    std::vector<std::vector<std::wstring>> getStanyInstruktora(const std::wstring & instruktor);
    std::vector<std::vector<std::wstring>> getWplatyInstruktora(const std::wstring & instruktor);

    std::vector<std::vector<std::wstring>> getWplatyIndData(const std::vector<std::wstring> & dat);
    std::vector<std::vector<std::wstring>> getWplatyHufData(const std::vector<std::wstring> & dat);
    std::vector<std::vector<std::wstring>> getUzupelnieniaData();
    std::vector<std::vector<std::wstring>> getOpoznieniaData(const std::vector<std::wstring> & dat);

    std::vector<std::wstring> getPossibleHufcowi();
    std::vector<std::wstring> getPossibleDruzynowi();
    std::vector<std::wstring> getAllInstruktorzy();
    std::vector<std::wstring> getPossibleHufce();
    std::vector<std::wstring> getPossibleTypyDruzyn();
    std::vector<std::wstring> getPossibleStopnieInstr();
    std::vector<std::wstring> getPossibleStopnieHarc();
    std::vector<std::wstring> getPossibleStatusy();

    //UPDATE FUNCTIONS (changing data in database)

    bool updateHufiec(const std::wstring & nazwa, const std::vector<std::wstring> & hufiec);
    bool insertHufiec(const std::vector<std::wstring> & hufiec);
    bool deleteHufiec(const std::wstring & nazwa);

    bool updateDruzyna(const std::wstring & nazwa, const std::wstring & numer, const std::vector<std::wstring> & druzyna);
    bool insertDruzyna(const std::vector<std::wstring> & druzyna);
    bool deleteDruzyna(const std::wstring & nazwa, const std::wstring & numer);

    bool updateInstruktor(const std::wstring & imie, const std::wstring & nazwisko, const std::vector<std::wstring> & instruktor);
    bool insertInstruktor(const std::vector<std::wstring> & instruktor);
    bool deleteInstruktor(const std::wstring & imie, const std::wstring & nazwisko);

    bool insertStatus(const std::vector<std::wstring> & status);
    bool deleteStatus(const std::wstring & dataPocz, const std::wstring & instruktor);

    bool insertOkres(const std::vector<std::wstring> & okres);
    bool deleteOkres(const std::wstring & dataPocz);

    bool updateWplata(const std::wstring & id, const std::vector<std::wstring> & wplata);
    bool insertWplata(const std::vector<std::wstring> & wplata);
    bool deleteWplata(const std::wstring & id);

    //

    bool resetBaza();
    bool resetWplaty();

private:
    soci::session *sql;
};
