#include <vector>
#include <string>

class DBService
{
public:

    std::vector<std::vector<std::string>> getData(const std::string & s);

    std::vector<std::vector<std::string>> getHufceData();
    std::vector<std::vector<std::string>> getInstruktorzyData();
};