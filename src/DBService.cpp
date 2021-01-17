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

std::vector<std::vector<std::wstring>> DBService::getTableData(const std::wstring & s)
{
    try
    {
    
    if(s == L"hufce")
    {
        std::vector<std::vector<std::wstring>> res;
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
            res.push_back({DateConverter::to_wstring(hufces[i]),DateConverter::to_wstring(hufcowis[i])});
        }
        return res;
    }

    if(s == L"druzyny")
    {
        std::vector<std::vector<std::wstring>> res;

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

        *sql<<"select d.nazwa, d.numer, d.probna, coalesce(d.patron,'brak'), (i.imie || ' ' || i.nazwisko), d.hufiec , d.typ_druzyny from \
                druzyny d left outer join instruktorzy i on(d.druzynowy = i.id_instr) order by d.nazwa;", 
                soci::into(nazwas), soci::into(numers), soci::into(probnas), soci::into(patrons), soci::into(druzynowys),
                soci::into(hufiecs), soci::into(typs);

        for (int i = 0; i < count; i++)
        {
            res.push_back({DateConverter::to_wstring(nazwas[i]), DateConverter::to_wstring(numers[i])
            ,DateConverter::to_wstring(probnas[i]),DateConverter::to_wstring(patrons[i]),
            DateConverter::to_wstring(druzynowys[i]),DateConverter::to_wstring(hufiecs[i]),DateConverter::to_wstring(typs[i])});
        }
        

        return res;
    }

    if(s == L"instruktorzy")
    {
        std::vector<std::vector<std::wstring>> res;
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

        *sql<<"select id_instr, imie, nazwisko, email, rozkaz_przyjecia, st_instr, st_harc, coalesce(hufiec, 'brak') from instruktorzy order by nazwisko;", 
        soci::into(ids), soci::into(imies), soci::into(nazwiskas), soci::into(emails), soci::into(rozkaz_s), 
        soci::into(st_instrs), soci::into(st_harcerskis), soci::into(hufce_s);

        for(int i = 0; i < count; i++)
        {
            res.push_back({DateConverter::to_wstring(ids[i]),DateConverter::to_wstring(imies[i]),DateConverter::to_wstring(nazwiskas[i])
            ,DateConverter::to_wstring(emails[i]),DateConverter::to_wstring(rozkaz_s[i]),DateConverter::to_wstring(st_instrs[i]),
            DateConverter::to_wstring(st_harcerskis[i]),DateConverter::to_wstring(hufce_s[i])});
        }
        return res;
    }

    if(s == L"okresy")
    {
        std::vector<std::vector<std::wstring>> res;
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
            res.push_back({DateConverter::to_wstring(pocztks[i]),DateConverter::to_wstring(koncs[i]),DateConverter::to_wstring(kwots[i])});
        }

        return res;
    }

    if(s == L"wplaty")
    {
        std::vector<std::vector<std::wstring>> res;
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
            res.push_back({DateConverter::to_wstring(ids[i]),DateConverter::to_wstring(imies[i]),DateConverter::to_wstring(nazwiskos[i]),
            DateConverter::to_wstring(kwotas[i]),DateConverter::to_wstring(datas[i])});
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

std::vector<std::vector<std::wstring>> DBService::getStanyInstruktora(const std::wstring & instruktor)
{
    try
    {
        std::vector<std::vector<std::wstring>> res;
        std::vector<std::string> status;
        std::vector<std::string> poczatek;
        std::vector<std::string> koniec;

        int count;
        *sql<<"select count(*) from stany_instruktorow where instruktor = (select id_instr from instruktorzy where (imie || ' ' || nazwisko) = ?);", 
            soci::use(DateConverter::to_string(instruktor)), soci::into(count);
        if(count == 0)
            return{};

        status.resize(count);
        poczatek.resize(count);
        koniec.resize(count);

        *sql<<"select to_char(poczatek, 'DD-MM-YYYY'), COALESCE(to_char(koniec, 'DD-MM-YYYY') , 'brak'), status from stany_instruktorow where instruktor \
        = (select id_instr from instruktorzy where (imie || ' ' || nazwisko) = ?) order by poczatek;", 
        soci::use(DateConverter::to_string(instruktor)), soci::into(poczatek), soci::into(koniec), soci::into(status);

         for(int i = 0; i < count; i++)
        {
            res.push_back({DateConverter::to_wstring(status[i]),DateConverter::to_wstring(poczatek[i]),DateConverter::to_wstring(koniec[i])});
        }
        return res;

    }
    catch(const std::exception& e)
    {
        return {};
    }
    return {};
   
}

std::vector<std::vector<std::wstring>> DBService::getWplatyInstruktora(const std::wstring & instruktor)
{
    try
    {

    std::vector<std::vector<std::wstring>> res;
    std::vector<std::string> ids;
    std::vector<std::string> imies;
    std::vector<std::string> nazwiskos;
    std::vector<std::string> kwotas;
    std::vector<std::string> datas;

    int count;
    *sql<<"select count(*) from wplaty where instruktor = (select id_instr from instruktorzy where (imie || ' ' || nazwisko) = ?);",
    soci::use(DateConverter::to_string(instruktor)), soci::into(count);
    if(count == 0)
        return{};

    ids.resize(count);
    imies.resize(count);
    nazwiskos.resize(count);
    kwotas.resize(count);
    datas.resize(count);

    *sql<<"select id_wplaty, imie, nazwisko, kwota, to_char(data, 'DD-MM-YYYY') from wplaty left \
    join instruktorzy on(instruktor = id_instr) where instruktor = (select id_instr from instruktorzy where (imie || ' ' || nazwisko) = ?) \
     order by nazwisko, data desc;", 
        soci::use(DateConverter::to_string(instruktor)), soci::into(ids), soci::into(imies), soci::into(nazwiskos), soci::into(kwotas), soci::into(datas);

    for(int i = 0; i < count; i++)
    {
        res.push_back({DateConverter::to_wstring(ids[i]),DateConverter::to_wstring(imies[i]),DateConverter::to_wstring(nazwiskos[i]),
        DateConverter::to_wstring(kwotas[i]),DateConverter::to_wstring(datas[i])});
    }
    return res;

    }
    catch(const std::exception& e)
    {
        return {};
    }
    return {};
}


std::vector<std::vector<std::wstring>> DBService::getWplatyIndData(const std::vector<std::wstring> & dat)
{
    try
    {
        if(dat.size()!=6)
            return {};

        std::vector<std::vector<std::wstring>> res;

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

        *sql<<"select imie, nazwisko, email, st_instr, coalesce(hufiec, 'brak'), sumaSkladekInstruktoraWOkresie(id_instr, ?,?) from instruktorzy order by nazwisko;", 
        soci::use(DateConverter::to_string(DateConverter::glue(dat[0],dat[1],dat[2]))),soci::use(DateConverter::to_string(DateConverter::glue(dat[3],dat[4],dat[5]))),
        soci::into(imies), soci::into(nazwiskas), soci::into(emails), soci::into(st_instrs), soci::into(hufce_s),  soci::into(kwota_s);

        for(int i = 0; i < count; i++)
        {
            res.push_back({DateConverter::to_wstring(imies[i]),DateConverter::to_wstring(nazwiskas[i]),DateConverter::to_wstring(emails[i]),
            DateConverter::to_wstring(st_instrs[i]),DateConverter::to_wstring(hufce_s[i]),DateConverter::to_wstring(kwota_s[i])});
        }
        return res;

    }
    catch(const std::exception& e)
    {
        return {};
    }
    return {};
}
std::vector<std::vector<std::wstring>> DBService::getWplatyHufData(const std::vector<std::wstring> & dat)
{
    try
    {

    if(dat.size()!=6)
        return {};

    std::vector<std::vector<std::wstring>> res;
    std::vector<std::string> nazwa;
    std::vector<std::string> kwota;

    int count;
    *sql<<"select count(*) from hufce;", soci::into(count);

    nazwa.resize(count);
    kwota.resize(count);

    *sql<<"select nazwa, sumaSkladekHufcaWOkresie(nazwa, ?,?) from hufce order by nazwa;", 
    soci::use(DateConverter::to_string(DateConverter::glue(dat[0],dat[1],dat[2]))),soci::use(DateConverter::to_string(DateConverter::glue(dat[3],dat[4],dat[5]))),
    soci::into(nazwa), soci::into(kwota);
    
    for(int i = 0; i < count; i++)
    {
        res.push_back({DateConverter::to_wstring(nazwa[i]),DateConverter::to_wstring(kwota[i])});
    }
    return res;

    }
    catch(const std::exception& e)
    {
        return {};
    }
    return {};
}
std::vector<std::vector<std::wstring>> DBService::getUzupelnieniaData()
{
    try
    {

        std::vector<std::vector<std::wstring>> res;

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

        *sql<<"select imie, nazwisko, email, st_instr, coalesce(hufiec, 'brak'), to_char(doKiedyUzupelniono(id_instr),'mm-yyyy') from instruktorzy order by nazwisko;", 
        soci::into(imies), soci::into(nazwiskas), soci::into(emails), soci::into(st_instrs), soci::into(hufce_s),  soci::into(uzupelnie_s);

        for(int i = 0; i < count; i++)
        {
            res.push_back({DateConverter::to_wstring(imies[i]),DateConverter::to_wstring(nazwiskas[i]),DateConverter::to_wstring(emails[i]),
            DateConverter::to_wstring(st_instrs[i]),DateConverter::to_wstring(hufce_s[i]),DateConverter::to_wstring(uzupelnie_s[i])});
        }
        return res;

    }
    catch(const std::exception& e)
    {
        return {};
    }
    return {};
}
std::vector<std::vector<std::wstring>> DBService::getOpoznieniaData(const std::vector<std::wstring> & dat)
{
    try
    {
        if(dat.size()!=3)
        return {};

        std::vector<std::vector<std::wstring>> res;

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

        *sql<<"select imie, nazwisko, email, st_instr, coalesce(hufiec, 'brak'), to_char(doKiedyUzupelniono(id_instr),'mm-yyyy') from instruktorzy where czyUzupelnionoDo(id_instr,?) = 'NIE' order by nazwisko;",
        soci::use(DateConverter::to_string(DateConverter::glue(dat[0],dat[1],dat[2]))),
        soci::into(imies), soci::into(nazwiskas), soci::into(emails), soci::into(st_instrs), soci::into(hufce_s),  soci::into(uzupelnie_s);

        for(int i = 0; i < count; i++)
        {
            res.push_back({DateConverter::to_wstring(imies[i]),DateConverter::to_wstring(nazwiskas[i]),DateConverter::to_wstring(emails[i]),
            DateConverter::to_wstring(st_instrs[i]),DateConverter::to_wstring(hufce_s[i]),DateConverter::to_wstring(uzupelnie_s[i])});
        }
        return res;

    }
    catch(const std::exception& e)
    {
        return {};
    }
    return {};
}

std::vector<std::wstring> DBService::getPossibleHufcowi()
{
    return getAllInstruktorzy();
}

std::vector<std::wstring> DBService::getPossibleDruzynowi()
{
    return getAllInstruktorzy();
}

std::vector<std::wstring> DBService::getAllInstruktorzy()
{
    try
    {

    std::vector<std::string> res;
    std::vector<std::wstring> ress;

    int count;
    *sql<<"select count(*) from instruktorzy;", soci::into(count);

    res.resize(count);

    *sql<<"select imie || ' ' || nazwisko from instruktorzy order by nazwisko;", soci::into(res);

    for(auto & x:res)
        ress.push_back(DateConverter::to_wstring(x));

    return ress;

    }
    catch(const std::exception e)
    {
        return {};
    }

    return {};
}

std::vector<std::wstring> DBService::getPossibleHufce()
{
    try
    {

    std::vector<std::string> res;
    std::vector<std::wstring> ress;

    int count;
    *sql<<"select count(*) from hufce;", soci::into(count);

    res.resize(count);

    *sql<<"select nazwa from hufce order by nazwa;", soci::into(res);
    for(auto & x:res)
        ress.push_back(DateConverter::to_wstring(x));

    return ress;

    }
    catch(const std::exception e)
    {
        return {};
    }

    return {};
}
std::vector<std::wstring> DBService::getPossibleTypyDruzyn()
{
    try
    {

    std::vector<std::string> res;
    std::vector<std::wstring> ress;

    int count;
    *sql<<"select count(*) from typy_druzyn;", soci::into(count);

    res.resize(count);

    *sql<<"select nazwa from typy_druzyn order by nazwa;", soci::into(res);
    for(auto & x:res)
        ress.push_back(DateConverter::to_wstring(x));

    return ress;

    }
    catch(const std::exception e)
    {
        return {};
    }

    return {};
}

std::vector<std::wstring> DBService::getPossibleStopnieInstr()
{
    try
    {

    std::vector<std::string> res;
    std::vector<std::wstring> ress;

    int count;
    *sql<<"select count(*) from stopnie_instruktorskie;", soci::into(count);

    res.resize(count);

    *sql<<"select nazwa from stopnie_instruktorskie order by nazwa;", soci::into(res);
    for(auto & x:res)
        ress.push_back(DateConverter::to_wstring(x));

    return ress;

    }
    catch(const std::exception e)
    {
        return {};
    }

    return {};
}
std::vector<std::wstring> DBService::getPossibleStopnieHarc()
{
    try
    {

    std::vector<std::string> res;
    std::vector<std::wstring> ress;

    int count;
    *sql<<"select count(*) from stopnie_harcerskie;", soci::into(count);

    res.resize(count);

    *sql<<"select nazwa from stopnie_harcerskie order by nazwa;", soci::into(res);
    for(auto & x:res)
        ress.push_back(DateConverter::to_wstring(x));

    return ress;

    }
    catch(const std::exception e)
    {
        return {};
    }

    return {};
}

std::vector<std::wstring> DBService::getPossibleStatusy()
{
    try
    {

    std::vector<std::string> res;
    std::vector<std::wstring> ress;

    int count;
    *sql<<"select count(*) from statusy;", soci::into(count);

    res.resize(count);

    *sql<<"select nazwa from statusy order by nazwa;", soci::into(res);
    for(auto & x:res)
        ress.push_back(DateConverter::to_wstring(x));

    return ress;

    }
    catch(const std::exception e)
    {
        return {};
    }

    return {};
}

//CHANGING DATA

bool DBService::updateHufiec(const std::wstring & nazwa, const std::vector<std::wstring> & hufiec)
{
    if(!DateConverter::check_if_valid_data(hufiec))
        return false;
    try
    {   
        if(hufiec.size() != 2)
            return false;
        *sql<<"BEGIN modyfikujHufiec(?,?,?); END;",soci::use(DateConverter::to_string(nazwa)), soci::use(DateConverter::to_string(hufiec[0])) ,
        soci::use(DateConverter::to_string(hufiec[1]));
        *sql<<"BEGIN commit; END;";
    }
    catch(const std::exception e)
    {
        return false;
    }
   
    return true;
}

bool DBService::insertHufiec(const std::vector<std::wstring> & hufiec)
{
    if(!DateConverter::check_if_valid_data(hufiec))
        return false;
    try
    {   
        if(hufiec.size() != 2)
            return false;
        *sql<<"BEGIN dodajHufiec(?,?); END;", soci::use(DateConverter::to_string(hufiec[0])) ,soci::use(DateConverter::to_string(hufiec[1]));
        *sql<<"BEGIN commit; END;";
    }
    catch(const std::exception e)
    {
        return false;
    }
   
    return true;
}

bool DBService::deleteHufiec(const std::wstring & nazwa)
{
    try
    {   
        *sql<<"BEGIN usunHufiec(?); END;", soci::use(DateConverter::to_string(nazwa));
        *sql<<"BEGIN commit; END;";
    }
    catch(const std::exception e)
    {
        return false;
    }
   
    return true;
}

bool DBService::updateDruzyna(const std::wstring & nazwa, const std::wstring & numer, const std::vector<std::wstring> & druzyna)
{
    if(!DateConverter::check_if_valid_data(druzyna))
        return false;
    try
    {   
        if(druzyna.size() != 7)
            return false;
        *sql<<"BEGIN modyfikujDruzyne(?,?,?,?,?,?,?,?,?); END;",soci::use(DateConverter::to_string(nazwa)),soci::use(DateConverter::to_string(numer)), 
        soci::use(DateConverter::to_string(druzyna[0])) ,soci::use(DateConverter::to_string(druzyna[1])),
        soci::use(DateConverter::to_string(druzyna[2])) ,soci::use(DateConverter::to_string(druzyna[3])),
        soci::use(DateConverter::to_string(druzyna[4])) ,soci::use(DateConverter::to_string(druzyna[5])),soci::use(DateConverter::to_string(druzyna[6]));
        *sql<<"BEGIN commit; END;";
    }
    catch(const std::exception e)
    {
        return false;
    }
   
    return true;
}
bool DBService::insertDruzyna(const std::vector<std::wstring> & druzyna)
{
    if(!DateConverter::check_if_valid_data(druzyna))
        return false;
    try
    {   
        if(druzyna.size() != 7)
            return false;
        *sql<<"BEGIN dodajDruzyne(?,?,?,?,?,?,?); END;", 
        soci::use(DateConverter::to_string(druzyna[0])) ,soci::use(DateConverter::to_string(druzyna[1])),soci::use(DateConverter::to_string(druzyna[2])) ,
        soci::use(DateConverter::to_string(druzyna[3])),
        soci::use(DateConverter::to_string(druzyna[4])) ,soci::use(DateConverter::to_string(druzyna[5])),soci::use(DateConverter::to_string(druzyna[6]));
        *sql<<"BEGIN commit; END;";
    }
    catch(const std::exception e)
    {
        return false;
    }
   
    return true;
}
bool DBService::deleteDruzyna(const std::wstring & nazwa, const std::wstring & numer)
{
    try
    {   
        *sql<<"BEGIN usunDruzyne(?,?); END;",soci::use(DateConverter::to_string(nazwa)),soci::use(DateConverter::to_string(numer)); 
        *sql<<"BEGIN commit; END;";
    }
    catch(const std::exception e)
    {
        return false;
    }
   
    return true;
}

bool DBService::updateInstruktor(const std::wstring & imie, const std::wstring & nazwisko, const std::vector<std::wstring> & instruktor)
{
    if(!DateConverter::check_if_valid_data(instruktor))
        return false;
    try
    {   
        if(instruktor.size() != 7)
            return false;
        *sql<<"BEGIN modyfikujInstruktora(?,?,?,?,?,?,?,?,?); END;",soci::use(DateConverter::to_string(imie)),soci::use(DateConverter::to_string(nazwisko)), 
        soci::use(DateConverter::to_string(instruktor[0])) ,soci::use(DateConverter::to_string(instruktor[1])),
        soci::use(DateConverter::to_string(instruktor[2])) ,soci::use(DateConverter::to_string(instruktor[3])),
        soci::use(DateConverter::to_string(instruktor[4])) ,soci::use(DateConverter::to_string(instruktor[5])),soci::use(DateConverter::to_string(instruktor[6]));
        *sql<<"BEGIN commit; END;";
    }
    catch(const std::exception e)
    {
        return false;
    }
   
    return true;
}
bool DBService::insertInstruktor(const std::vector<std::wstring> & instruktor)
{
    if(!DateConverter::check_if_valid_data(instruktor))
        return false;
    try
    {   
        if(instruktor.size() != 10)
            return false;
        *sql<<"BEGIN dodajInstruktora(?,?,?,?,?,?,?,?); END;",
        soci::use(DateConverter::to_string(instruktor[0])) ,soci::use(DateConverter::to_string(instruktor[1])),
        soci::use(DateConverter::to_string(instruktor[2])) ,soci::use(DateConverter::to_string(instruktor[3])),
        soci::use(DateConverter::to_string(instruktor[4])) ,soci::use(DateConverter::to_string(instruktor[5])),soci::use(DateConverter::to_string(instruktor[6])),
        soci::use(DateConverter::to_string(DateConverter::glue(instruktor[7],instruktor[8],instruktor[9])));
        *sql<<"BEGIN commit; END;";
    }
    catch(const std::exception e)
    {
        return false;
    }
   
    return true;
}
bool DBService::deleteInstruktor(const std::wstring & imie, const std::wstring & nazwisko)
{
    try
    {   
        *sql<<"BEGIN usunInstruktora(?,?); END;",soci::use(DateConverter::to_string(imie)),soci::use(DateConverter::to_string(nazwisko)); 
        *sql<<"BEGIN commit; END;";
    }
    catch(const std::exception e)
    {
        return false;
    }
   
    return true;
}


bool DBService::insertStatus(const std::vector<std::wstring> & status)
{
    if(!DateConverter::check_if_valid_data(status))
        return false;
    try
    {   
        if(status.size() != 5)
            return false;
        *sql<<"BEGIN dodajStan(?,?,?); END;",
        soci::use(DateConverter::to_string(status[0])) ,soci::use(DateConverter::to_string(status[1]))
        ,soci::use(DateConverter::to_string(DateConverter::glue(status[2],status[3],status[4])));
        *sql<<"BEGIN commit; END;";
    }
    catch(const std::exception e)
    {
        return false;
    }
   
    return true;
}

bool DBService::deleteStatus(const std::wstring & dataPocz, const std::wstring & instruktor)
{
    try
    {   
        *sql<<"BEGIN usunStan(?,?); END;", soci::use(DateConverter::to_string(dataPocz)),soci::use(DateConverter::to_string(instruktor));
        *sql<<"BEGIN commit; END;";
    }
    catch(const std::exception e)
    {
        return false;
    }
   
    return true;
}

bool DBService::insertOkres(const std::vector<std::wstring> & okres)
{
    if(!DateConverter::check_if_valid_data(okres))
        return false;

    try
    {   
        if(okres.size() != 3)
            return false;
        *sql<<"BEGIN dodajOkresSladkowy(?,?); END;",
        soci::use(DateConverter::to_string(okres[2])) ,soci::use(DateConverter::to_string(DateConverter::glue(L"1",okres[0],okres[1])));
        *sql<<"BEGIN commit; END;";
    }
    catch(const std::exception e)
    {
        return false;
    }
   
    return true;
}

bool DBService::deleteOkres(const std::wstring & dataPocz)
{
    try
    {   
        *sql<<"BEGIN usunOkresSladkowy(); END;";
        *sql<<"BEGIN commit; END;";
    }
    catch(const std::exception e)
    {
        return false;
    }
    return true;
}

bool DBService::updateWplata(const std::wstring & id, const std::vector<std::wstring> & wplata)
{
    if(!DateConverter::check_if_valid_data(wplata))
        return false;

    try
    {   
        if(wplata.size() != 5)
            return false;
        *sql<<"BEGIN modyfikujWplate(?,?,?,?); END;", soci::use(DateConverter::to_string(id)),
        soci::use(DateConverter::to_string(wplata[0])) ,soci::use(DateConverter::to_string(wplata[1])), 
        soci::use(DateConverter::to_string(DateConverter::glue(wplata[2],wplata[3],wplata[4])));
        *sql<<"BEGIN commit; END;";
    }
    catch(const std::exception e)
    {
        return false;
    }
   
    return true;
}
bool DBService::insertWplata(const std::vector<std::wstring> & wplata)
{
    if(!DateConverter::check_if_valid_data(wplata))
        return false;
    try
    {   
        if(wplata.size() != 5)
            return false;
        *sql<<"BEGIN dodajWplate(?,?,?); END;",
        soci::use(DateConverter::to_string(wplata[0])) ,soci::use(DateConverter::to_string(wplata[1])), 
        soci::use(DateConverter::to_string(DateConverter::glue(wplata[2],wplata[3],wplata[4])));
        *sql<<"BEGIN commit; END;";
    }
    catch(const std::exception e)
    {
        return false;
    }
   
    return true;
}
bool DBService::deleteWplata(const std::wstring & id)
{
    try
    {   
        *sql<<"BEGIN usunWplate(?); END;", soci::use(DateConverter::to_string(id));
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
