#include <string>

namespace blowfish {
std::wstring encrypt(const std::wstring &text, const std::wstring &manualKey);
std::wstring dencrypt(std::wstring text, const std::wstring &manualKey);

} // namespace blowfish