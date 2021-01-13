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

    std::vector<std::string> getPossibleHufcowi();
    std::vector<std::string> getPossibleDruzynowi();
    std::vector<std::string> getPossibleHufce();
    std::vector<std::string> getPossibleTypyDruzyn();

    //UPDATE FUNCTIONS (changing data in database)

    bool updateHufiec(const std::string & nazwa, const std::vector<std::string> & hufiec);
    bool insertHufiec(const std::vector<std::string> & hufiec);
    bool deleteHufiec(const std::string & nazwa);

    bool updateDruzyna(const std::string & nazwa, const std::string & numer, const std::vector<std::string> & druzyna);
    bool insertDruzyna(const std::vector<std::string> & druzyna);
    bool deleteDruzyna(const std::string & nazwa, const std::string & numer);

private:

};