#include <string>
#include <vector>

namespace boost::json {
class value;
}

namespace Json = boost::json;

namespace utils {
std::string readFromFile(const std::string path);
void writeToFile(const std::string &path, const std::wstring &text);
std::wstring to_wstring(std::string &text);
std::string to_string(const std::wstring &text);
std::wstring readFile(const char *filename);
Json::value toBoostValue(const std::string &data);
std::vector<std::uint32_t> toVecUint32(std::vector<std::uint8_t> &vecUint8);
std::vector<std::uint8_t> toVecUint8(const std::vector<std::uint32_t> &vec);
} // namespace utils