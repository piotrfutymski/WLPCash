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
        res.push_back({"Jan","Kowalski", "120", "15-03-2020"});
        res.push_back({"Adam","Kasprzak", "180", "29-04-2020"});
        return res;
    }

    return {{}};

}

std::vector<std::string> DBService::getPossibleHufcowi()
{
    return {"Jan Kowalski", "Antoni Kozanecki"};
}


std::vector<std::string> DBService::getPossibleDruzynowi()
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