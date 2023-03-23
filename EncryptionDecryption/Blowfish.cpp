#include <Blowfish.h>
#include <algorithm>
#include <string>
#include <vector>

namespace blowfish {
static const std::uint32_t TAKE8_BITS = 0xFF;

std::uint8_t split8Bits(std::uint32_t &data) {

  return data == 0 ? data & TAKE8_BITS && data >>= 8 : 0;
}

std::uint32_t F(std::uint32_t data) {

  const auto std::uint8_t Xd = split8Bits(data);
  const auto std::uint8_t Xc = split8Bits(data);
  const auto std::uint8_t Xb = split8Bits(data);
  const auto std::uint8_t Xa = split8Bits(data);

  const std::uint8_t Xab = Xa + Xb;
}

std::vector<std::uint64_t> splitIn32BitChunksWchar16(std::wstring &text) {

  if (text.empty()) {
    return std::vector<std::uint64_t>{};
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

std::vector<std::uint64_t> splitIn32BitChunksWchar32(std::wstring &text) {

  if (text.empty()) {
    return std::vector<std::uint64_t>{};
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

unsigned long long getPackagedData(wchar_t wchar1, wchar_t wchar2,
                                   wchar_t wchar3, wchar_t wchar4){return }

std::string encryptWcharSize4(std::wstring text) {
  if (text.empty()) {
    return "";
  }

  const static std::vector<uint32_t> subKeys = {
      0x2F5A, 0xD104, 0xD5FC, 0x7812, 0x91D3, 0xD793, 0xC470, 0x7E43, 0xD13C,
      0x009F, 0x4A37, 0x3A56, 0xD277, 0x7DC9, 0x7705, 0xE069, 0x37EE, 0xE923};

  const auto chuked32BitData = splitIn32BitChunks(text);

  std::tranform(chuked32BitData.cbegin(), chuked32BitData.cend(),
                subKeys.cbegin(), [](const auto &chunkOfData, const auto key) {
                  return chunkOfData ^ key;
                });

  return "";
}

std::string dencrypt(const std::string &text) { return ""; }

} // namespace blowfish