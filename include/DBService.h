#pragma once
#include <vector>
#include <string>



class DBService
{
public:
    void init();
    void close();

    //SELECT FUNCTIONS (getting data from database)

    std::vector<std::vector<std::string>> getTableData(const std::string & s);
    std::vector<std::vector<std::string>> getStanyInstruktora(const std::string & instruktor);
    std::vector<std::vector<std::string>> getWplatyInstruktora(const std::string & instruktor);

    std::vector<std::string> getPossibleHufcowi();
    std::vector<std::string> getPossibleDruzynowi();
    std::vector<std::string> getAllInstruktorzy();
    std::vector<std::string> getPossibleHufce();
    std::vector<std::string> getPossibleTypyDruzyn();
    std::vector<std::string> getPossibleStopnieInstr();
    std::vector<std::string> getPossibleStopnieHarc();
    std::vector<std::string> getPossibleStatusy();

    //UPDATE FUNCTIONS (changing data in database)

    bool updateHufiec(const std::string & nazwa, const std::vector<std::string> & hufiec);
    bool insertHufiec(const std::vector<std::string> & hufiec);
    bool deleteHufiec(const std::string & nazwa);

    bool updateDruzyna(const std::string & nazwa, const std::string & numer, const std::vector<std::string> & druzyna);
    bool insertDruzyna(const std::vector<std::string> & druzyna);
    bool deleteDruzyna(const std::string & nazwa, const std::string & numer);

    bool updateInstruktor(const std::string & imie, const std::string & nazwisko, const std::vector<std::string> & instruktor);
    bool insertInstruktor(const std::vector<std::string> & instruktor);
    bool deleteInstruktor(const std::string & imie, const std::string & nazwisko);

    bool insertStatus(const std::vector<std::string> & status);
    bool deleteStatus(const std::string & dataPocz, const std::string & instruktor);

    bool insertOkres(const std::vector<std::string> & okres);
    bool deleteOkres(const std::string & dataPocz);

    bool updateWplata(const std::string & id, const std::vector<std::string> & wplata);
    bool insertWplata(const std::vector<std::string> & wplata);
    bool deleteWplata(const std::string & id);

private:

};