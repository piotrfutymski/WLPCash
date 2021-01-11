#pragma once
#include <vector>
#include <string>
#define OTL_ODBC
#include "otlv4.h"


class DBService
{
public:
    void init();
    void close();
    std::vector<std::vector<std::string>> getData(const std::string & s);
private:
    otl_connect db;
};