#include "DBService.h"

std::vector<std::vector<std::string>> DBService::getData(const std::string & s)
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

}