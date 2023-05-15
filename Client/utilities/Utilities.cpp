#include "Utilities.h"
#include <codecvt>
#include <fstream>
#include <locale>
#include <sstream>

namespace utils {

std::string readFromFile(const std::string path) {

  std::ifstream file(path);
  std::string text;
  std::string line;

  while (std::getline(file, line)) {
    text += std::move(line);
    text += '\n';
  }

  file.close();

  return text;
}

void writeToFile(const std::string &path, const std::wstring &text) {
  std::wofstream file(path);
  file << text;
  file.close();
}

std::wstring to_wstring(std::string &text) {
  if (text.empty()) {
    return L"";
  }

  std::wstring convertedText;
  auto nrWithoutGroup = text.size() % 4;
  convertedText.reserve(text.size() / 4 + nrWithoutGroup);

  while (nrWithoutGroup--) {
    text.push_back(' ');
  }

  for (size_t i = 0; i < text.size(); i += 4) {
    convertedText.push_back((static_cast<std::uint32_t>(text[i]) << 24) |
                            (static_cast<std::uint32_t>(text[i + 1]) << 16) |
                            (static_cast<std::uint32_t>(text[i + 2]) << 8) |
                            static_cast<std::uint32_t>(text[i + 3]));
  }
  //
  return convertedText;
}

std::string to_string(const std::wstring &text) {
  if (text.empty()) {
    return "";
  }
  const static std::uint64_t TAKE_8 = 0xFF000000;

  std::string convertedText;
  convertedText.reserve(4 * text.size());

  for (auto ch : text) {
    convertedText.push_back((ch & TAKE_8) >> 24);
    convertedText.push_back(((ch << 8) & TAKE_8) >> 24);
    convertedText.push_back(((ch << 16) & TAKE_8) >> 24);
    convertedText.push_back(((ch << 24) & TAKE_8) >> 24);
  }

  return convertedText;
}

std::wstring readFile(const char *filename) {
  std::wifstream wif(filename);
  wif.imbue(std::locale(std::locale(), new std::codecvt_utf8<wchar_t>));
  std::wstringstream wss;
  wss << wif.rdbuf();
  return wss.str();
}

} // namespace utils