#include <string>

namespace utils {
std::string readFromFile(const std::string path);
void writeToFile(const std::string path, const std::string &text);
} // namespace utils