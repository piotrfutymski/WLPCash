#pragma once
#include <vector>
#include <string>



class DBService
{
public:
    void init();
    void close();
    std::vector<std::vector<std::string>> getData(const std::string & s);
private:

};