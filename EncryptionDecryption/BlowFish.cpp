#include "BlowFish.h"
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <fstream>
#include <iostream>
#include <iterator>
#include <mutex>
#include <string>
#include <utility>
#include <vector>

namespace blowfish {
static const std::uint32_t TAKE8_BITS = 0xFF;
static constexpr std::uint64_t TWO_POW_THIRTYTWO = 4294967296;

static std::vector<std::uint32_t> S1;
static std::vector<std::uint32_t> S2;
static std::vector<std::uint32_t> S3;
static std::vector<std::uint32_t> S4;

static const std::string Sbox1Path{"./EncryptionDecryption/Sbox1.txt"};
static const std::string Sbox2Path{"./EncryptionDecryption/Sbox2.txt"};
static const std::string Sbox3Path{"./EncryptionDecryption/Sbox3.txt"};
static const std::string Sbox4Path{"./EncryptionDecryption/Sbox4.txt"};

static std::once_flag areKeysInitialized;
static std::once_flag areReverseKeysInitialized;

static const std::uint32_t NR_RUNDS = 16;

static std::vector<uint32_t> pKeys;
static std::vector<uint32_t> pKeysReverse;

template <typename T> void printVec(const std::vector<T> vec) {
  std::cout << "\nVec: ";
  for (const auto &el : vec) {
    std::cout << el << ", ";
  }

  std::cout << "\n";
}

std::uint8_t split8Bits(std::uint32_t &data) {

  const auto chuncked8Bits = data == 0 ? data & TAKE8_BITS : 0;
  data >>= 8;
  return chuncked8Bits;
}

bool initializeSubstitutionBox(const std::string path,
                               std::vector<std::uint32_t> &Sbox) {
  std::ifstream file(path);

  std::string line;
  Sbox.reserve(256);
  while (std::getline(file, line)) {
    boost::trim(line);
    std::vector<std::string> vec;
    boost::split(vec, line, boost::is_any_of(" "), boost::token_compress_on);
    // printVec(vec);
    std::transform(vec.begin(), vec.end(), std::back_inserter(Sbox),
                   [](const auto &substitutionValue) {
                     return stol("0x" + substitutionValue, nullptr, 16);
                   });
  }
  file.close();
  std::cout << "Box size: " << Sbox.size() << "\n";
  return Sbox.size() != 256;
}

//

std::uint32_t F(std::uint32_t data) {

  const std::uint8_t Xa = split8Bits(data);
  const std::uint8_t Xb = split8Bits(data);
  const std::uint8_t Xc = split8Bits(data);
  const std::uint8_t Xd = split8Bits(data);

  if (S1.empty() || S2.empty() || S3.empty() || S4.empty()) {
    if (initializeSubstitutionBox(Sbox1Path, S1)) {
      std::cerr
          << "Information required in susbstitution box s1 is not present!\n";
      exit(EXIT_FAILURE);
    }
    if (initializeSubstitutionBox(Sbox1Path, S2)) {
      std::cerr
          << "Information required in susbstitution box s2 is not present!\n";
      exit(EXIT_FAILURE);
    }
    if (initializeSubstitutionBox(Sbox1Path, S3)) {
      std::cerr
          << "Information required in susbstitution box s3 is not present!\n";
      exit(EXIT_FAILURE);
    }
    if (initializeSubstitutionBox(Sbox1Path, S4)) {
      std::cerr
          << "Information required in susbstitution box s4 is not present!\n";
      exit(EXIT_FAILURE);
    }
  }

  std::uint32_t XaNew = S1[Xa];
  std::uint32_t XbNew = S2[Xb];
  std::uint32_t XcNew = S3[Xc];
  std::uint32_t XdNew = S4[Xd];

  return ((((XaNew + XbNew) % TWO_POW_THIRTYTWO) ^ XcNew) + XdNew) %
         TWO_POW_THIRTYTWO;
} // namespace blowfish

std::vector<std::uint32_t> splitIn32BitChunksWchar16(std::wstring &text) {

  if (text.empty()) {
    return std::vector<std::uint32_t>{};
  }

  std::vector<std::uint32_t> chunkedData;

  if (text.size() % 2 != 0) {
    text.push_back(' ');
  }

  chunkedData.reserve(text.size());

  for (size_t i = 0; i < text.size(); i += 2) {
    chunkedData.emplace_back((text[i] << 16) | (text[i + 1]));
  }

  return chunkedData;
}

std::vector<std::uint32_t> splitIn32BitChunksWchar32(std::wstring &text) {

  if (text.empty()) {
    return std::vector<std::uint32_t>{};
  }

  if (text.size() % 2 == 1) {
    text.push_back(' ');
  }

  std::vector<std::uint32_t> chunkedData;
  chunkedData.reserve(text.size());
  std::transform(text.cbegin(), text.cend(), std::back_inserter(chunkedData),
                 [](const auto wchar) { return wchar; });

  return chunkedData;
}

std::vector<std::uint32_t> splitIn32BitChunks(std::wstring &text) {

  return sizeof(wchar_t) == 4
             ? splitIn32BitChunksWchar32(text)
             : sizeof(wchar_t) == 2 ? splitIn32BitChunksWchar16(text)
                                    : std::vector<std::uint32_t>{};
}

std::vector<std::uint32_t> splitAndPaddManualKey(std::wstring key) {
  if (key.size() < pKeys.size()) {
    std::cout << "Yes sir\n";
    key.append(key.substr(0, pKeys.size() - key.size()));
  }

  return splitIn32BitChunks(key);
}

void initializePKeys(const std::wstring &manualKey) {
  const std::vector<uint32_t> harcodedKeys{
      0x6B9B8DB3, 0xE8AFD413, 0x4B9A1F4A, 0x60A48FEA, 0x2CC34519, 0xCD58D244,
      0xC26FE723, 0xAED6C8B5, 0x86E73ECA, 0x062141E0, 0x524620B1, 0x9EE084B2,
      0x4BECE1BD, 0x05962030, 0x445AE44E, 0xAC4B8B42, 0x5383662D, 0x56FA18EA};
  std::cout << "initializePKeys1\n";
  std::wcout << "Manual Key... " << manualKey << "\n";
  const auto chuckedManualKeys = splitAndPaddManualKey(manualKey);

  pKeys.reserve(harcodedKeys.size());

  std::transform(harcodedKeys.cbegin(), harcodedKeys.cend(),
                 chuckedManualKeys.begin(), std::back_inserter(pKeys),
                 [](const auto hardCodedKey, const auto manualKey) {
                   return hardCodedKey ^ manualKey;
                 });

  std::cout << "initializePKeys2\n";
}

std::wstring encryptWcharSize4(std::wstring text,
                               const std::wstring &manualKey) {

  if (text.empty()) {
    return L"";
  }

  std::cout << "encryptWcharSize4 1\n";

  // std::call_once(areKeysInitialized, initializePKeys, manualKey);
  initializePKeys(manualKey);
  std::cout << "encryptWcharSize4 2\n";

  auto chuked32BitData = splitIn32BitChunks(text);

  for (auto chuked32BitDataIt = chuked32BitData.begin();
       chuked32BitDataIt != chuked32BitData.end(); chuked32BitDataIt += 2) {
    const auto Xl = chuked32BitDataIt;
    const auto Xr = std::next(chuked32BitDataIt);

    for (std::uint32_t i = 0; i < NR_RUNDS; ++i) {
      *Xl = *Xl ^ pKeys[i];
      *Xr = F(*Xl) ^ *Xr;
      std::swap(*Xl, *Xr);
    }
    std::swap(*Xl, *Xr);
    *Xr = *Xr ^ pKeys[16];
    *Xl = *Xl ^ pKeys[17];
  }

  std::wstring result;
  std::transform(chuked32BitData.begin(), chuked32BitData.end(),
                 std::back_inserter(result), [](const auto ch) { return ch; });

  return result;
}

std::wstring encrypt(const std::wstring &text, const std::wstring &manualKey) {
  return sizeof(wchar_t) == 4 ? encryptWcharSize4(text, manualKey) : L"";
}

std::wstring dencrypt(std::wstring &text, const std::wstring &manualKey) {
  std::cout << "Decryption started......11\n";

  if (text.empty()) {
    return L"";
  }

  if (text.size() % 2 == 1) {
    text.push_back(' ');
  }
  std::cout << "Decryption started......22\n";
  std::cout << "Decryption started......44\n";
  auto initializeDecryptPKeys = [&](const std::wstring &key) {
    pKeysReverse.reserve(pKeys.size());
    std::copy(pKeys.begin(), pKeys.end(), std::back_inserter(pKeysReverse));
    std::reverse(pKeysReverse.begin(), pKeysReverse.end());
  };

  initializeDecryptPKeys(manualKey);

  auto chuked32BitData = splitIn32BitChunks(text);
  std::cout << "Decryption started......4\n";
  for (auto chuked32BitDataIt = chuked32BitData.begin();
       chuked32BitDataIt != chuked32BitData.end(); chuked32BitDataIt += 2) {
    std::cout << "Decryption started......3\n";

    const auto Xl = chuked32BitDataIt;
    const auto Xr = std::next(chuked32BitDataIt);

    for (std::uint32_t i = 0; i < NR_RUNDS; ++i) {
      *Xl = *Xl ^ pKeysReverse[i];
      *Xr = F(*Xl) ^ *Xr;
      std::swap(*Xl, *Xr);
    }
    std::swap(*Xl, *Xr);
    *Xr = *Xr ^ pKeysReverse[16];
    *Xl = *Xl ^ pKeysReverse[17];
  }

  std::wstring result;
  std::transform(chuked32BitData.begin(), chuked32BitData.end(),
                 std::back_inserter(result), [](const auto ch) { return ch; });

  return result;
}

} // namespace blowfish