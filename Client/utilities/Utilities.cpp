#include "Utilities.h"
#include <boost/json/parse.hpp>
#include <codecvt>
#include <fstream>
#include <iostream>
#include <locale>
#include <sstream>

namespace utils {
namespace Json = boost::json;
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
  std::locale::global(std::locale(""));
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

std::vector<std::uint32_t> toVecUint32(std::vector<std::uint8_t> &vecUint8) {
  if (vecUint8.empty()) {
    return {};
  }

  std::vector<std::uint32_t> vecUint32;
  auto nrWithoutGroup = vecUint8.size() % 4;
  vecUint32.reserve(vecUint8.size() / 4 + nrWithoutGroup);

  while (nrWithoutGroup--) {
    vecUint8.push_back(' ');
  }

  for (size_t i = 0; i < vecUint8.size(); i += 4) {
    vecUint32.push_back((static_cast<std::uint32_t>(vecUint8[i]) << 24) |
                        (static_cast<std::uint32_t>(vecUint8[i + 1]) << 16) |
                        (static_cast<std::uint32_t>(vecUint8[i + 2]) << 8) |
                        static_cast<std::uint32_t>(vecUint8[i + 3]));
  }
  //
  return vecUint32;
} // namespace utils

std::vector<std::uint8_t> toVecUint8(const std::vector<std::uint32_t> &vec) {
  if (vec.empty()) {
    return {};
  }
  const static std::uint64_t TAKE_8 = 0xFF000000;

  std::vector<std::uint8_t> vec8Uint;
  vec8Uint.reserve(4 * vec.size());

  for (auto el : vec) {
    vec8Uint.push_back((el & TAKE_8) >> 24);
    vec8Uint.push_back(((el << 8) & TAKE_8) >> 24);
    vec8Uint.push_back(((el << 16) & TAKE_8) >> 24);
    vec8Uint.push_back(((el << 24) & TAKE_8) >> 24);
  }

  return vec8Uint;
}

std::wstring readFile(const char *filename) {
  std::wifstream wif(filename);
  wif.imbue(std::locale(std::locale(), new std::codecvt_utf8<wchar_t>));
  std::wstringstream wss;
  wss << wif.rdbuf();
  return wss.str();
}

Json::value toBoostValue(const std::string &data) {
  Json::error_code errCode;
  Json::value dataValue;

  try {
    dataValue = Json::parse(data, errCode);

  } catch (std::bad_alloc const &e) {
    return {};
  }

  if (errCode) {
    return {};
  }

  return dataValue;
}

} // namespace utils