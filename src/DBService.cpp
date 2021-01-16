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
        if(count == 0)
            return{};

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

        std::vector<std::string> nazwas;
        std::vector<std::string> numers;
        std::vector<std::string> probnas;
        std::vector<std::string> patrons;
        std::vector<std::string> druzynowys;
        std::vector<std::string> hufiecs;
        std::vector<std::string> typs;

        int count;
        *sql<<"select count(*) from druzyny;", soci::into(count);

        if(count == 0)
            return{};

        nazwas.resize(count);
        numers.resize(count);
        probnas.resize(count);
        patrons.resize(count);
        druzynowys.resize(count);
        hufiecs.resize(count);
        typs.resize(count);

        *sql<<"select d.nazwa, d.numer, d.probna, d.patron, (i.imie || ' ' || i.nazwisko), d.hufiec, d.typ_druzyny from \
                druzyny d left outer join instruktorzy i on(d.druzynowy = i.id_instr) order by d.nazwa;", 
                soci::into(nazwas), soci::into(numers), soci::into(probnas), soci::into(patrons), soci::into(druzynowys),
                soci::into(hufiecs), soci::into(typs);

        for (int i = 0; i < count; i++)
        {
            res.push_back({nazwas[i], numers[i],probnas[i],patrons[i],druzynowys[i],hufiecs[i],typs[i]});
        }
        

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
        if(count == 0)
            return{};


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

        for(int i = 0; i < count; i++)
        {
            res.push_back({ids[i],imies[i],nazwiskas[i],emails[i],rozkaz_s[i],st_instrs[i],st_harcerskis[i],hufce_s[i]});
        }
        return res;
    }

    if(s == "okresy")
    {
        std::vector<std::vector<std::string>> res;
        std::vector<std::string> pocztks;
        std::vector<std::string> koncs;
        std::vector<std::string> kwots;

        int count;
        *sql<<"select count(*) from okresy_skladkowe;", soci::into(count);
        if(count == 0)
            return{};

        pocztks.resize(count);
        koncs.resize(count);
        kwots.resize(count);

        *sql<<"select to_char(poczatek, 'MM-YYYY'), COALESCE(to_char(koniec, 'MM-YYYY') , 'brak'), kwota from okresy_skladkowe order by poczatek;", 
            soci::into(pocztks), soci::into(koncs), soci::into(kwots);

        for(int i = 0; i < count; i++)
        {
            res.push_back({pocztks[i],koncs[i],kwots[i]});
        }

        return res;
    }

    if(s == "wplaty")
    {
        std::vector<std::vector<std::string>> res;
        std::vector<std::string> ids;
        std::vector<std::string> imies;
        std::vector<std::string> nazwiskos;
        std::vector<std::string> kwotas;
        std::vector<std::string> datas;

        int count;
        *sql<<"select count(*) from wplaty;", soci::into(count);
        if(count == 0)
            return{};

        ids.resize(count);
        imies.resize(count);
        nazwiskos.resize(count);
        kwotas.resize(count);
        datas.resize(count);

        *sql<<"select id_wplaty, imie, nazwisko, kwota, to_char(data, 'DD-MM-YYYY') from wplaty left \
        join instruktorzy on(instruktor = id_instr) order by nazwisko, data;", 
            soci::into(ids), soci::into(imies), soci::into(nazwiskos), soci::into(kwotas), soci::into(datas);


        for(int i = 0; i < count; i++)
        {
            res.push_back({ids[i],imies[i],nazwiskos[i],kwotas[i],datas[i]});
        }
        return res;
    }

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

std::vector<std::vector<std::string>> DBService::getStanyInstruktora(const std::string & instruktor)
{
    try
    {
        std::vector<std::vector<std::string>> res;
        std::vector<std::string> status;
        std::vector<std::string> poczatek;
        std::vector<std::string> koniec;

        int count;
        *sql<<"select count(*) from stany_instruktorow where instruktor = (select id_instr from instruktorzy where (imie || ' ' || nazwisko) = ?);", 
            soci::use(instruktor), soci::into(count);
        if(count == 0)
            return{};

        status.resize(count);
        poczatek.resize(count);
        koniec.resize(count);

        *sql<<"select to_char(poczatek, 'MM-YYYY'), COALESCE(to_char(koniec, 'DD-MM-YYYY') , 'brak'), status from stany_instruktorow where instruktor \
        = (select id_instr from instruktorzy where (imie || ' ' || nazwisko) = ?) order by poczatek;", 
        soci::use(instruktor), soci::into(poczatek), soci::into(koniec), soci::into(status);

         for(int i = 0; i < count; i++)
        {
            res.push_back({status[i],poczatek[i],koniec[i]});
        }
        return res;

    }
    catch(const std::exception& e)
    {
        return {};
    }
    return {};
   
}

std::vector<std::vector<std::string>> DBService::getWplatyInstruktora(const std::string & instruktor)
{
    try
    {

    std::vector<std::vector<std::string>> res;
    std::vector<std::string> ids;
    std::vector<std::string> imies;
    std::vector<std::string> nazwiskos;
    std::vector<std::string> kwotas;
    std::vector<std::string> datas;

    int count;
    *sql<<"select count(*) from wplaty where instruktor = (select id_instr from instruktorzy where (imie || ' ' || nazwisko) = ?);",
    soci::use(instruktor), soci::into(count);
    if(count == 0)
        return{};

    ids.resize(count);
    imies.resize(count);
    nazwiskos.resize(count);
    kwotas.resize(count);
    datas.resize(count);

    *sql<<"select id_wplaty, imie, nazwisko, kwota, to_char(data, 'DD-MM-YYYY') from wplaty left \
    join instruktorzy on(instruktor = id_instr) where instruktor = (select id_instr from instruktorzy where (imie || ' ' || nazwisko) = ?) \
     order by nazwisko, data;", 
        soci::use(instruktor), soci::into(ids), soci::into(imies), soci::into(nazwiskos), soci::into(kwotas), soci::into(datas);

    for(int i = 0; i < count; i++)
    {
        res.push_back({ids[i],imies[i],nazwiskos[i],kwotas[i],datas[i]});
    }
    return res;

    }
    catch(const std::exception& e)
    {
        return {};
    }
    return {};
}


std::vector<std::vector<std::string>> DBService::getWplatyIndData(const std::vector<std::string> & dat)
{
    try
    {
        if(dat.size()!=6)
            return {};

        std::vector<std::vector<std::string>> res;

        std::vector<std::string> imies;
        std::vector<std::string> nazwiskas;
        std::vector<std::string> emails;
        std::vector<std::string> st_instrs;  
        std::vector<std::string> hufce_s;
        std::vector<std::string> kwota_s;

        int count;
        *sql<<"select count(*) from instruktorzy;", soci::into(count);
        if(count == 0)
            return{};

        imies.resize(count);
        nazwiskas.resize(count);
        emails.resize(count);
        st_instrs.resize(count);
        hufce_s.resize(count);
        kwota_s.resize(count);

        *sql<<"select imie, nazwisko, email, st_instr, hufiec, sumaSkladekInstruktoraWOkresie(id_instr, ?,?) from instruktorzy order by nazwisko;", 
        soci::use(DateConverter::glue(dat[0],dat[1],dat[2])),soci::use(DateConverter::glue(dat[3],dat[4],dat[5])),
        soci::into(imies), soci::into(nazwiskas), soci::into(emails), soci::into(st_instrs), soci::into(hufce_s),  soci::into(kwota_s);

        for(int i = 0; i < count; i++)
        {
            res.push_back({imies[i],nazwiskas[i],emails[i],st_instrs[i],hufce_s[i],kwota_s[i]});
        }
        return res;

    }
    catch(const std::exception& e)
    {
        return {};
    }
    return {};
}
std::vector<std::vector<std::string>> DBService::getWplatyHufData(const std::vector<std::string> & dat)
{
    try
    {

    if(dat.size()!=6)
        return {};

    std::vector<std::vector<std::string>> res;
    std::vector<std::string> nazwa;
    std::vector<std::string> kwota;

    int count;
    *sql<<"select count(*) from hufce;", soci::into(count);

    nazwa.resize(count);
    kwota.resize(count);

    *sql<<"select nazwa, sumaSkladekHufcaWOkresie(nazwa, ?,?,?,?,?,?) from hufce order by nazwa;", 
    soci::use(DateConverter::glue(dat[0],dat[1],dat[2])),soci::use(DateConverter::glue(dat[3],dat[4],dat[5])),
    soci::into(nazwa), soci::into(kwota);
    
    for(int i = 0; i < count; i++)
    {
        res.push_back({nazwa[i],kwota[i]});
    }
    return res;

    }
    catch(const std::exception& e)
    {
        return {};
    }
    return {};
}
std::vector<std::vector<std::string>> DBService::getUzupelnieniaData()
{
    try
    {

        std::vector<std::vector<std::string>> res;

        std::vector<std::string> imies;
        std::vector<std::string> nazwiskas;
        std::vector<std::string> emails;
        std::vector<std::string> st_instrs;  
        std::vector<std::string> hufce_s;
        std::vector<std::string> uzupelnie_s;

        int count;
        *sql<<"select count(*) from instruktorzy;", soci::into(count);
        if(count == 0)
            return{};

        imies.resize(count);
        nazwiskas.resize(count);
        emails.resize(count);
        st_instrs.resize(count);
        hufce_s.resize(count);
        uzupelnie_s.resize(count);

        *sql<<"select imie, nazwisko, email, st_instr, hufiec, doKiedyUzupelniono(id_instr) from instruktorzy order by nazwisko;", 
        soci::into(imies), soci::into(nazwiskas), soci::into(emails), soci::into(st_instrs), soci::into(hufce_s),  soci::into(uzupelnie_s);

        for(int i = 0; i < count; i++)
        {
            res.push_back({imies[i],nazwiskas[i],emails[i],st_instrs[i],hufce_s[i],uzupelnie_s[i]});
        }
        return res;

    }
    catch(const std::exception& e)
    {
        return {};
    }
    return {};
}
std::vector<std::vector<std::string>> DBService::getOpoznieniaData(const std::vector<std::string> & dat)
{
    try
    {
        if(dat.size()!=3)
        return {};

        std::vector<std::vector<std::string>> res;

        std::vector<std::string> imies;
        std::vector<std::string> nazwiskas;
        std::vector<std::string> emails;
        std::vector<std::string> st_instrs;  
        std::vector<std::string> hufce_s;
        std::vector<std::string> uzupelnie_s;

        int count;
        *sql<<"select count(*) from instruktorzy;", soci::into(count);
        if(count == 0)
            return{};

        imies.resize(count);
        nazwiskas.resize(count);
        emails.resize(count);
        st_instrs.resize(count);
        hufce_s.resize(count);
        uzupelnie_s.resize(count);

        *sql<<"select imie, nazwisko, email, st_instr, hufiec, doKiedyUzupelniono(id_instr) from instruktorzy where czyUzupelnionoDo(id_instr,?) = 'NIE' order by nazwisko;",
        soci::use(DateConverter::glue(dat[0],dat[1],dat[2])),
        soci::into(imies), soci::into(nazwiskas), soci::into(emails), soci::into(st_instrs), soci::into(hufce_s),  soci::into(uzupelnie_s);

        for(int i = 0; i < count; i++)
        {
            res.push_back({imies[i],nazwiskas[i],emails[i],st_instrs[i],hufce_s[i],uzupelnie_s[i]});
        }
        return res;

    }
    catch(const std::exception& e)
    {
        return {};
    }
    return {};
}

std::vector<std::string> DBService::getPossibleHufcowi()
{
    return getAllInstruktorzy();
}

std::vector<std::string> DBService::getPossibleDruzynowi()
{
    return getAllInstruktorzy();
}

std::vector<std::string> DBService::getAllInstruktorzy()
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
    catch(const std::exception e)
    {
        return {};
    }

    return {};
}

std::vector<std::string> DBService::getPossibleHufce()
{
    try
    {

    std::vector<std::string> res;

    int count;
    *sql<<"select count(*) from hufce;", soci::into(count);

    res.resize(count);

    *sql<<"select nazwa from hufce order by nazwa;", soci::into(res);
    return res;

    }
    catch(const std::exception e)
    {
        return {};
    }

    return {};
}
std::vector<std::string> DBService::getPossibleTypyDruzyn()
{
    try
    {

    std::vector<std::string> res;

    int count;
    *sql<<"select count(*) from typy_druzyn;", soci::into(count);

    res.resize(count);

    *sql<<"select nazwa from typy_druzyn order by nazwa;", soci::into(res);
    return res;

    }
    catch(const std::exception e)
    {
        return {};
    }

    return {};
}

std::vector<std::string> DBService::getPossibleStopnieInstr()
{
    try
    {

    std::vector<std::string> res;

    int count;
    *sql<<"select count(*) from stopnie_instruktorskie;", soci::into(count);

    res.resize(count);

    *sql<<"select nazwa from stopnie_instruktorskie order by nazwa;", soci::into(res);
    return res;

    }
    catch(const std::exception e)
    {
        return {};
    }

    return {};
}
std::vector<std::string> DBService::getPossibleStopnieHarc()
{
    try
    {

    std::vector<std::string> res;

    int count;
    *sql<<"select count(*) from stopnie_harcerskie;", soci::into(count);

    res.resize(count);

    *sql<<"select nazwa from stopnie_harcerskie order by nazwa;", soci::into(res);
    return res;

    }
    catch(const std::exception e)
    {
        return {};
    }

    return {};
}

std::vector<std::string> DBService::getPossibleStatusy()
{
    try
    {

    std::vector<std::string> res;

    int count;
    *sql<<"select count(*) from statusy;", soci::into(count);

    res.resize(count);

    *sql<<"select nazwa from statusy order by nazwa;", soci::into(res);
    return res;

    }
    catch(const std::exception e)
    {
        return {};
    }

    return {};
}

//CHANGING DATA

bool DBService::updateHufiec(const std::string & nazwa, const std::vector<std::string> & hufiec)
{
    try
    {   
        if(hufiec.size() != 2)
            return false;
        *sql<<"BEGIN modyfikujHufiec(?,?,?); END;",soci::use(nazwa), soci::use(hufiec[0]) ,soci::use(hufiec[1]);
        *sql<<"BEGIN commit; END;";
    }
    catch(const std::exception e)
    {
        return false;
    }
   
    return true;
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
    catch(const std::exception e)
    {
        return false;
    }
   
    return true;
}

bool DBService::deleteHufiec(const std::string & nazwa)
{
    try
    {   
        *sql<<"BEGIN usunHufiec(?); END;", soci::use(nazwa);
        *sql<<"BEGIN commit; END;";
    }
    catch(const std::exception e)
    {
        return false;
    }
   
    return true;
}

bool DBService::updateDruzyna(const std::string & nazwa, const std::string & numer, const std::vector<std::string> & druzyna)
{
    try
    {   
        if(druzyna.size() != 7)
            return false;
        *sql<<"BEGIN modyfikujDruzyne(?,?,?,?,?,?,?,?,?); END;",soci::use(nazwa),soci::use(numer), 
        soci::use(druzyna[0]) ,soci::use(druzyna[1]),soci::use(druzyna[2]) ,soci::use(druzyna[3]),
        soci::use(druzyna[4]) ,soci::use(druzyna[5]),soci::use(druzyna[6]);
        *sql<<"BEGIN commit; END;";
    }
    catch(const std::exception e)
    {
        return false;
    }
   
    return true;
}
bool DBService::insertDruzyna(const std::vector<std::string> & druzyna)
{
    try
    {   
        if(druzyna.size() != 7)
            return false;
        *sql<<"BEGIN dodajDruzyne(?,?,?,?,?,?,?); END;", 
        soci::use(druzyna[0]) ,soci::use(druzyna[1]),soci::use(druzyna[2]) ,soci::use(druzyna[3]),
        soci::use(druzyna[4]) ,soci::use(druzyna[5]),soci::use(druzyna[6]);
        *sql<<"BEGIN commit; END;";
    }
    catch(const std::exception e)
    {
        return false;
    }
   
    return true;
}
bool DBService::deleteDruzyna(const std::string & nazwa, const std::string & numer)
{
    try
    {   
        *sql<<"BEGIN usunDruzyne(?,?); END;",soci::use(nazwa),soci::use(numer); 
        *sql<<"BEGIN commit; END;";
    }
    catch(const std::exception e)
    {
        return false;
    }
   
    return true;
}

bool DBService::updateInstruktor(const std::string & imie, const std::string & nazwisko, const std::vector<std::string> & instruktor)
{
    try
    {   
        if(instruktor.size() != 7)
            return false;
        *sql<<"BEGIN modyfikujInstruktora(?,?,?,?,?,?,?,?,?); END;",soci::use(imie),soci::use(nazwisko), 
        soci::use(instruktor[0]) ,soci::use(instruktor[1]),soci::use(instruktor[2]) ,soci::use(instruktor[3]),
        soci::use(instruktor[4]) ,soci::use(instruktor[5]),soci::use(instruktor[6]);
        *sql<<"BEGIN commit; END;";
    }
    catch(const std::exception e)
    {
        return false;
    }
   
    return true;
}
bool DBService::insertInstruktor(const std::vector<std::string> & instruktor)
{
    try
    {   
        if(instruktor.size() != 10)
            return false;
        *sql<<"BEGIN dodajInstruktora(?,?,?,?,?,?,?,?); END;",
        soci::use(instruktor[0]) ,soci::use(instruktor[1]),soci::use(instruktor[2]) ,soci::use(instruktor[3]),
        soci::use(instruktor[4]) ,soci::use(instruktor[5]),soci::use(instruktor[6]),
        soci::use(DateConverter::glue(instruktor[7],instruktor[8],instruktor[9]));
        *sql<<"BEGIN commit; END;";
    }
    catch(const std::exception e)
    {
        return false;
    }
   
    return true;
}
bool DBService::deleteInstruktor(const std::string & imie, const std::string & nazwisko)
{
    try
    {   
        *sql<<"BEGIN usunInstruktora(?,?); END;",soci::use(imie),soci::use(nazwisko); 
        *sql<<"BEGIN commit; END;";
    }
    catch(const std::exception e)
    {
        return false;
    }
   
    return true;
}


bool DBService::insertStatus(const std::vector<std::string> & status)
{
    try
    {   
        if(status.size() != 5)
            return false;
        *sql<<"BEGIN dodajStatus(?,?,?); END;",
        soci::use(status[0]) ,soci::use(status[1]),soci::use(DateConverter::glue(status[2],status[3],status[4]));
        *sql<<"BEGIN commit; END;";
    }
    catch(const std::exception e)
    {
        return false;
    }
   
    return true;
}

bool DBService::deleteStatus(const std::string & dataPocz, const std::string & instruktor)
{
    try
    {   
        *sql<<"BEGIN usunStatus(?,?); END;", soci::use(dataPocz),soci::use(instruktor);
        *sql<<"BEGIN commit; END;";
    }
    catch(const std::exception e)
    {
        return false;
    }
   
    return true;
}

bool DBService::insertOkres(const std::vector<std::string> & okres)
{
    try
    {   
        if(okres.size() != 4)
            return false;
        *sql<<"BEGIN dodajOkresSladkowy(?,?); END;",
        soci::use(okres[0]) ,soci::use(DateConverter::glue("1",okres[1],okres[2]));
        *sql<<"BEGIN commit; END;";
    }
    catch(const std::exception e)
    {
        return false;
    }
   
    return true;
}

bool DBService::deleteOkres(const std::string & dataPocz)
{
    try
    {   
        *sql<<"BEGIN usunOkresSladkowy(?); END;", soci::use("01-"+dataPocz);
        *sql<<"BEGIN commit; END;";
    }
    catch(const std::exception e)
    {
        return false;
    }
    return true;
}

bool DBService::updateWplata(const std::string & id, const std::vector<std::string> & wplata)
{
    try
    {   
        if(wplata.size() != 5)
            return false;
        *sql<<"BEGIN modyfikujWplate(?,?,?,?); END;", soci::use(id),
        soci::use(wplata[0]) ,soci::use(wplata[1]), DateConverter::glue(wplata[2],wplata[3],wplata[4]);
        *sql<<"BEGIN commit; END;";
    }
    catch(const std::exception e)
    {
        return false;
    }
   
    return true;
}
bool DBService::insertWplata(const std::vector<std::string> & wplata)
{
    try
    {   
        if(wplata.size() != 5)
            return false;
        *sql<<"BEGIN dodajWplate(?,?,?); END;",
        soci::use(wplata[0]) ,soci::use(wplata[1]), DateConverter::glue(wplata[2],wplata[3],wplata[4]);
        *sql<<"BEGIN commit; END;";
    }
    catch(const std::exception e)
    {
        return false;
    }
   
    return true;
}
bool DBService::deleteWplata(const std::string & id)
{
    try
    {   
        *sql<<"BEGIN usunWplate(?); END;", soci::use(id);
        *sql<<"BEGIN commit; END;";
    }
    catch(const std::exception e)
    {
        return false;
    }
   
    return true;
}

bool DBService::resetBaza()
{
    try
    {   
        *sql<<"BEGIN resetBazy(); END;";
        *sql<<"BEGIN commit; END;";
    }
    catch(const std::exception e)
    {
        return false;
    }
    return true;
}


bool DBService::resetWplaty()
{
    try
    {   
        *sql<<"BEGIN resetWplat(); END;";
        *sql<<"BEGIN commit; END;";
    }
    catch(const std::exception e)
    {
        return false;
    }
    return true;
}