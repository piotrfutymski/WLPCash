#include <string>
#include <sstream>
#include <iomanip>

class DateConverter
{
public:
    static std::string glue(std::string d, std::string m, std::string r)
    {
        std::stringstream stream;
        stream << std::setfill ('0') << std::right
        << std::setw(2) << d
        << std::setw(1) << "-" 
        << std::setw(2) << m 
        << std::setw(1) << "-"
        << std::setw(4) << r;
        return stream.str();
    }
};