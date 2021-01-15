#include "DBService.h"

void DBService::init()
{   
    try {
        sql = new soci::session(soci::odbc, "dsn=OracleODBC-21");
    }
    catch(const soci::soci_error e)
    {
         std::cout << e.what() << std::endl;
    }
    catch(const std::exception e)
    {
         std::cout << e.what() << std::endl;
    }
}

void DBService::close()
{
    sql->close();
    delete sql;
}

std::vector<std::vector<std::string>> DBService::getTableData(const std::string & s)
{
    try
    {
    
    if(s == "hufce")
    {
        std::vector<std::vector<std::string>> res;
        std::vector<std::string> hufces;
        std::vector<std::string> hufcowis;

        int count;
        *sql<<"select count(*) from hufce;", soci::into(count);

        hufces.resize(count);
        hufcowis.resize(count);

        *sql<<"select h.nazwa, i.imie || ' ' || i.nazwisko from hufce h left outer join hufcowi huf \
                on (h.nazwa = huf.hufiec) left outer join instruktorzy i on(huf.hufcowy = i.id_instr);", soci::into(hufces), soci::into(hufcowis);            

        for(int i = 0; i < hufces.size(); i++)
        {
            res.push_back({hufces[i],hufcowis[i]});
        }
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
        std::vector<std::string> ids;
        std::vector<std::string> imies;
        std::vector<std::string> nazwiskas;
        std::vector<std::string> emails;
        std::vector<std::string> rozkaz_s;
        std::vector<std::string> st_instrs;
        std::vector<std::string> st_harcerskis;    
        std::vector<std::string> hufce_s;

        int count;
        *sql<<"select count(*) from instruktorzy;", soci::into(count);


        ids.resize(count);
        imies.resize(count);
        nazwiskas.resize(count);
        emails.resize(count);
        rozkaz_s.resize(count);
        st_instrs.resize(count);
        st_harcerskis.resize(count);
        hufce_s.resize(count);

        *sql<<"select id_instr, imie, nazwisko, email, rozkaz_przyjecia, st_instr, st_harc, hufiec from instruktorzy order by nazwisko;", 
        soci::into(ids), soci::into(imies), soci::into(nazwiskas), soci::into(emails), soci::into(rozkaz_s), 
        soci::into(st_instrs), soci::into(st_harcerskis), soci::into(hufce_s);

        for(int i = 0; i < ids.size(); i++)
        {
            res.push_back({ids[i],imies[i],nazwiskas[i],emails[i],rozkaz_s[i],st_instrs[i],st_harcerskis[i],hufce_s[i]});
        }
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

    }
    catch(const soci::soci_error e)
    {
        return {{}};
    }
    catch(const std::exception e)
    {
        return {{}};
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


std::vector<std::vector<std::string>> DBService::getWplatyIndData(const std::vector<std::string> & dat)
{
    return {{"Jan", "Kowalski", "aaa@aaa", "pwd", "Gniazdo", "100"}};
}
std::vector<std::vector<std::string>> DBService::getWplatyHufData(const std::vector<std::string> & dat)
{
    return{{"Gniazdo", "1000"}};
}
std::vector<std::vector<std::string>> DBService::getUzupelnieniaData()
{
    return {{"Jan", "Kowalski", "aaa@aaa", "pwd", "Gniazdo", "05-2020"}};
}
std::vector<std::vector<std::string>> DBService::getOpoznieniaData(const std::vector<std::string> & dat)
{
    return {{"Jan", "Kowalski", "aaa@aaa", "pwd", "Gniazdo", "05-2019"}};
}

std::vector<std::string> DBService::getPossibleHufcowi()
{
    try
    {

    std::vector<std::string> res;

    int count;
    *sql<<"select count(*) from instruktorzy;", soci::into(count);

    res.resize(count);

    *sql<<"select imie || ' ' || nazwisko from instruktorzy order by nazwisko;", soci::into(res);
    return res;

    }
    catch(const soci::soci_error e)
    {
        return {};
    }
    catch(const std::exception e)
    {
        return {};
    }

    return {};
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
    try
    {   
        if(hufiec.size() != 2)
            return false;
        *sql<<"BEGIN dodajHufiec(?,?); END;", soci::use(hufiec[0]) ,soci::use(hufiec[1]);
        *sql<<"BEGIN commit; END;";
    }
    catch(const soci::soci_error e)
    {
        return false;
    }
    catch(const std::exception e)
    {
        return false;
    }

   
    return true;
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

bool DBService::resetBaza(const std::string & data)
{
    return false;
}
bool DBService::resetWplaty(const std::string & data)
{
    return false;
}