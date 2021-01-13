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

    //UPDATE FUNCTIONS (changing data in database)

    bool updateHufiec(const std::string & nazwa, const std::vector<std::string> & hufiec);
    bool insertHufiec(const std::vector<std::string> & hufiec);
    bool deleteHufiec(const std::string & nazwa);

private:

};