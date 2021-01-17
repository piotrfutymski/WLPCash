#include <string>
#include <sstream>
#include <iomanip>
#include <codecvt>
#include <locale>

class DateConverter
{
public:
    static std::wstring glue(std::wstring d, std::wstring m, std::wstring r)
    {
        std::wstringstream stream;
        stream << std::setfill (L'0') << std::right
        << std::setw(2) << d
        << std::setw(1) << L"-" 
        << std::setw(2) << m 
        << std::setw(1) << L"-"
        << std::setw(4) << r;
        return stream.str();
    }

    using convert_t = std::codecvt_utf8<wchar_t>;
    static std::wstring_convert<convert_t, wchar_t> strconverter;

    static std::string to_string(std::wstring wstr)
    {
        return strconverter.to_bytes(wstr);
    }

    static std::wstring to_wstring(std::string str)
    {
        return strconverter.from_bytes(str);
    }
};
