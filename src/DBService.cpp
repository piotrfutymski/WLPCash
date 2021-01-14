#include "DBService.h"

void DBService::init()
{

}

void DBService::close()
{
}

std::vector<std::vector<std::string>> DBService::getTableData(const std::string & s)
{
    if(s == "hufce")
    {
         std::vector<std::vector<std::string>> res;
        res.push_back({"Gniazdo","Antoni Kozanecki"});
        res.push_back({"Test","Jan Kowalski"});
        res.push_back({"Test","Jan Kowalski"});
        res.push_back({"Test","Jan Kowalski"});
        res.push_back({"Test","Jan Kowalski"});
        res.push_back({"Test","Jan Kowalski"});
        res.push_back({"Test","Jan Kowalski"});
        res.push_back({"Test","Jan Kowalski"});
        res.push_back({"Test","Jan Kowalski"});
        res.push_back({"Test-10","Jan Kowalski"});
        res.push_back({"Test-11","Jan Kowalski"});
        res.push_back({"Test-12","Jan Kowalski"});
        return res;
    }

    if(s == "druzyny")
    {
        std::vector<std::vector<std::string>> res;
        res.push_back({"PDH Jar","8", "NIE", "Stefan Grot Rowecki", "Piotr Futymski", "Gniazdo", "Harcerska"});
        res.push_back({"PDH","17", "NIE", "Nie wiem", "Jan Minksztym", "Gniazdo", "Harcerska"});
        return res;
    }

    if(s == "instruktorzy")
    {
        std::vector<std::vector<std::string>> res;
        res.push_back({"1","Jan", "Kowalski", "jan.kowalski@123.pl", "L05/2020", "phm.", "HR", "Gniazdo"});
        res.push_back({"2","Jan", "Kowalski2", "jan.kowalski@321.pl", "L05/2020", "phm.", "HR", "Gniazdo"});
        return res;
    }

    if(s == "okresy")
    {
        std::vector<std::vector<std::string>> res;
        res.push_back({"01-2000","12-2018", "0"});
        res.push_back({"01-2019","12-2019", "15"});
        res.push_back({"01-2020","", "16"});
        return res;
    }

    if(s == "wplaty")
    {
        std::vector<std::vector<std::string>> res;
        res.push_back({"1","Jan","Kowalski", "120", "15-03-2020"});
        res.push_back({"2","Adam","Kasprzak", "180", "29-04-2020"});
        return res;
    }

    return {{}};

}

std::vector<std::vector<std::string>> DBService::getStanyInstruktora(const std::string & instruktor)
{
    return{
        {"czynny","13-04-2017", "19-09-2019"},
        {"urlop", "19-09-2019", ""}
    };
}

std::vector<std::vector<std::string>> DBService::getWplatyInstruktora(const std::string & instruktor)
{
     std::vector<std::vector<std::string>> res;
        res.push_back({"1","Jan","Kowalski", "120", "15-03-2020"});
        res.push_back({"2","Jan","Kowalski", "180", "29-04-2020"});
        return res;
}

std::vector<std::string> DBService::getPossibleHufcowi()
{
    return {"Jan Kowalski", "Antoni Kozanecki"};
}

std::vector<std::string> DBService::getPossibleDruzynowi()
{
    return {"Jan Kowalski", "Antoni Kozanecki"};
}

std::vector<std::string> DBService::getAllInstruktorzy()
{
    return {"Jan Kowalski", "Antoni Kozanecki"};
}

std::vector<std::string> DBService::getPossibleHufce()
{
    return {"Gniazdo", "Test"};
}
std::vector<std::string> DBService::getPossibleTypyDruzyn()
{
    return {"Harcerska", "Zuchowa", "Wedrownicza"};
}

std::vector<std::string> DBService::getPossibleStopnieInstr()
{
    return {"pwd", "phm", "hm"};
}
std::vector<std::string> DBService::getPossibleStopnieHarc()
{
    return {"HO", "HR"};
}

std::vector<std::string> DBService::getPossibleStatusy()
{
    return {"czynny", "urlop", "rezerwa", "skreslony"};
}

//CHANGING DATA

bool DBService::updateHufiec(const std::string & nazwa, const std::vector<std::string> & hufiec)
{
    return false;
}

bool DBService::insertHufiec(const std::vector<std::string> & hufiec)
{
    return false;
}

bool DBService::deleteHufiec(const std::string & nazwa)
{
    return false;
}

bool DBService::updateDruzyna(const std::string & nazwa, const std::string & numer, const std::vector<std::string> & druzyna)
{
    return false;
}
bool DBService::insertDruzyna(const std::vector<std::string> & druzyna)
{
    return false;
}
bool DBService::deleteDruzyna(const std::string & nazwa, const std::string & numer)
{
    return false;
}

bool DBService::updateInstruktor(const std::string & imie, const std::string & nazwisko, const std::vector<std::string> & instruktor)
{
    return false;
}
bool DBService::insertInstruktor(const std::vector<std::string> & instruktor)
{
    return false;
}
bool DBService::deleteInstruktor(const std::string & imie, const std::string & nazwisko)
{
    return false;
}


bool DBService::insertStatus(const std::vector<std::string> & status)
{
    return false;
}

bool DBService::deleteStatus(const std::string & dataPocz, const std::string & instruktor)
{
    return false;
}

bool DBService::insertOkres(const std::vector<std::string> & okres)
{
    return false;
}

bool DBService::deleteOkres(const std::string & dataPocz)
{
    return false;
}

bool DBService::updateWplata(const std::string & id, const std::vector<std::string> & wplata)
{
    return false;
}
bool DBService::insertWplata(const std::vector<std::string> & wplata)
{
    return false;
}
bool DBService::deleteWplata(const std::string & id)
{
    return false;
}