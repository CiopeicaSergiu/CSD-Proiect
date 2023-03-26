#include "BlowFish.h"
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

namespace blowfish {
static const std::uint32_t TAKE8_BITS = 0xFF;

static std::vector<std::uint32_t> S1;
static std::vector<std::uint32_t> S2;
static std::vector<std::uint32_t> S3;
static std::vector<std::uint32_t> S4;

static const std::string Sbox1Path{"./EncryptionDecryption/Sbox1.txt"};
static const std::string Sbox2Path{"./EncryptionDecryption/Sbox2.txt"};
static const std::string Sbox3Path{"./EncryptionDecryption/Sbox3.txt"};
static const std::string Sbox4Path{"./EncryptionDecryption/Sbox4.txt"};

static const std::uint32_t NR_RUNDS = 16;

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
    printVec(vec);
    std::transform(vec.begin(), vec.end(), std::back_inserter(Sbox),
                   [](const auto &substitutionValue) {
                     return stol("0x" + substitutionValue, nullptr, 16);
                   });
  }
  file.close();
  std::cout << "Box size: " << Sbox.size() << "\n";
  return Sbox.size() != 256;
}

std::uint32_t F(std::uint32_t data) {

  const std::uint8_t Xd = split8Bits(data);
  const std::uint8_t Xc = split8Bits(data);
  const std::uint8_t Xb = split8Bits(data);
  const std::uint8_t Xa = split8Bits(data);

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

  return ((Xa | Xb) ^ Xc) | Xd;
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

std::wstring encryptWcharSize4(std::wstring text) {
  if (text.empty()) {
    return L"";
  }

  const static std::vector<uint32_t> subKeys = {
      0x2F5A, 0xD104, 0xD5FC, 0x7812, 0x91D3, 0xD793, 0xC470, 0x7E43, 0xD13C,
      0x009F, 0x4A37, 0x3A56, 0xD277, 0x7DC9, 0x7705, 0xE069, 0x37EE, 0xE923};

  const auto chuked32BitData = splitIn32BitChunks(text);

  std::vector<std::uint32_t> firstLayer;
  firstLayer.reserve(chuked32BitData.size());

  std::transform(chuked32BitData.cbegin(), chuked32BitData.cend(),
                 subKeys.cbegin(), std::back_inserter(firstLayer),
                 [](const auto &chunkOfData, const auto key) {
                   return chunkOfData ^ key;
                 });

  std::vector<std::uint32_t> secondLayer;
  secondLayer.reserve(256);

  std::transform(chuked32BitData.cbegin(), chuked32BitData.cend(),
                 subKeys.cbegin(), std::back_inserter(firstLayer),
                 [](const auto &chunkOfData, const auto key) {
                   return chunkOfData ^ key;
                 });

  for (auto firstLayerIt = firstLayer.begin(); firstLayerIt != firstLayer.end();
       firstLayerIt += 2) {
    const auto Xl = firstLayerIt;
    const auto Xr = std::next(firstLayerIt);

    for (std::uint32_t i = 0; i < NR_RUNDS; ++i) {
      const auto newXlValue = F(*Xl | subKeys[i]) ^ *Xr;
      *Xr = *Xl;
      *Xl = newXlValue;
    }

    const auto newXrValue = *Xl ^ subKeys[1];
    *Xl = *Xr ^ subKeys[0];
    *Xr = newXrValue;
  }

  std::wstring result;
  std::transform(firstLayer.begin(), firstLayer.end(),
                 std::back_inserter(result), [](const auto ch) { return ch; });

  return result;
}

std::wstring encrypt(std::wstring text) {
  return sizeof(wchar_t) == 4 ? encryptWcharSize4(text) : L"";
}

std::wstring dencrypt(std::wstring text) {
  if (text.empty()) {
    return L"";
  }

  const static std::vector<uint32_t> subKeys{
      0xE923, 0x37EE, 0xE069, 0x7705, 0x7DC9, 0xD277, 0x3A56, 0x4A37, 0x009F,
      0xD13C, 0x7E43, 0xC470, 0xD793, 0x91D3, 0x7812, 0xD5FC, 0xD104, 0x2F5A};

  const auto chuked32BitData = splitIn32BitChunks(text);

  std::vector<std::uint32_t> firstLayer;
  firstLayer.reserve(chuked32BitData.size());

  std::transform(chuked32BitData.cbegin(), chuked32BitData.cend(),
                 subKeys.cbegin(), std::back_inserter(firstLayer),
                 [](const auto &chunkOfData, const auto key) {
                   return chunkOfData ^ key;
                 });

  std::vector<std::uint32_t> secondLayer;
  secondLayer.reserve(256);

  std::transform(chuked32BitData.cbegin(), chuked32BitData.cend(),
                 subKeys.cbegin(), std::back_inserter(firstLayer),
                 [](const auto &chunkOfData, const auto key) {
                   return chunkOfData ^ key;
                 });

  for (auto firstLayerIt = firstLayer.begin(); firstLayerIt != firstLayer.end();
       firstLayerIt += 2) {
    const auto Xl = firstLayerIt;
    const auto Xr = std::next(firstLayerIt);

    for (std::uint32_t i = 0; i < NR_RUNDS; ++i) {
      const auto newXlValue = F(*Xl | subKeys[i]) ^ *Xr;
      *Xr = *Xl;
      *Xl = newXlValue;
    }

    const auto newXrValue = *Xl ^ subKeys[1];
    *Xl = *Xr ^ subKeys[0];
    *Xr = newXrValue;
  }

  std::wstring result;
  std::transform(firstLayer.begin(), firstLayer.end(),
                 std::back_inserter(result), [](const auto ch) { return ch; });

  return result;
}

} // namespace blowfish