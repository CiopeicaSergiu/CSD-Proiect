#include <codecvt>
#include <iostream>
#include <locale>
#include <sstream>
#include <string>

#include "BlowFish.h"
#include "Settings.h"
#include "Utilities.h"
#include <algorithm>
#include <boost/json/value_to.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/cURLpp.hpp>
#include <iterator>
#include <locale>

static const std::wstring KEY = L"123";

static const std::string protocol{"http://"};
static const std::string receivedDataFolder{"./receivedData/"};

std::string makeGetRequestToUrl(const std::string url) {
  try {

    curlpp::Cleanup myCleanup;
    std::ostringstream os;
    os << curlpp::options::Url(url);
    return os.str();

  } catch (curlpp::RuntimeError &e) {
    std::cout << e.what() << std::endl;
  } catch (curlpp::LogicError &e) {
    std::cout << e.what() << std::endl;
  }

  return "";
}

void printWStringValues(const std::vector<std::uint32_t> &values) {
  for (const auto value : values) {
    std::wcout << value << " ";
  }

  std::cout << "\n";
}

std::wstring toWstring(const std::vector<std::uint32_t> &vec) {
  std::wstring result;
  result.reserve(vec.size());
  std::transform(vec.cbegin(), vec.cend(), std::back_inserter(result),
                 [](const auto &ch) { return ch; });
  return result;
}

int main() {
  Settings settings("settings.yaml");
  const auto &nodes = settings.getNodesIp();
  for (const auto &node : nodes) {
    std::string receivedData = makeGetRequestToUrl(protocol + node);
    auto arr = boost::json::value_to<std::vector<std::uint8_t>>(
        utils::toBoostValue(receivedData));

    // std::wstring result;
    // std::transform(receivedDataArr.begin(), receivedDataArr.end(),
    //                std::back_inserter(result),
    //                [](const auto &ch) { return ch; });
    // std::wstring wstringText =
    // boost::json::value_to<std::wstring>(receivedDataObj.);

    // std::wcout << "\nReceived data:\n";
    // printWStringValues(wstringText);

    // std::wstring decryptedText = blowfish::dencrypt(encryptedText, KEY);
    // auto something = utils::to_wstring(encryptedText);
    auto something = utils::toVecUint32(arr);
    printWStringValues(something);

    auto encryptedText = toWstring(something);
    std::wcout << blowfish::dencrypt(encryptedText, KEY);
    // utils::writeToFile(receivedDataFolder + node + ".txt",
    //                    blowfish::dencrypt(wstringText, KEY));
  }
  return 0;
}
