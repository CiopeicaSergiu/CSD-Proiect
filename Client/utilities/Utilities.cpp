#include "Utilities.h"
#include <fstream>

namespace utils {

std::string readFromFile(const std::string path) {

  std::ifstream file(path);
  std::string text{""};
  std::string line;

  while (std::getline(file, line)) {
    text += std::move(line);
    text += '\n';
  }

  file.close();

  return text;
}

void writeToFile(const std::string path, const std::string &text) {
  std::ofstream file(path);
  file << text;
  file.close();
}

} // namespace utils