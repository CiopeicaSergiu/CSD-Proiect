#include <string>

namespace utils {
std::string readFromFile(const std::string path);
void writeToFile(const std::string &path, const std::wstring &text);
std::wstring to_wstring(std::string &text);
std::string to_string(const std::wstring &text);
std::wstring readFile(const char *filename);
} // namespace utils