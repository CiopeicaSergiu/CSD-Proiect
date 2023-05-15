#include <codecvt>
#include <iostream>
#include <locale>
#include <sstream>
#include <string>

#include "BlowFish.h"
#include "Settings.h"
#include "Utilities.h"
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/cURLpp.hpp>

static const std::wstring KEY = L"Ana are mere.";

static const std::string protocol{"http://"};
static const std::string receivedDataFolder{"./receivedData/"};

std::string makeGetRequestToUrl(const std::string url) {
  // try {

  curlpp::Cleanup myCleanup;
  std::ostringstream os;
  os << curlpp::options::Url(url);
  return os.str();

  // } catch (curlpp::RuntimeError &e) {
  //   std::cout << e.what() << std::endl;
  // } catch (curlpp::LogicError &e) {
  //   std::cout << e.what() << std::endl;
  // }

  return "";
}

int main() {
  Settings settings("settings.yaml");
  const auto &nodes = settings.getNodesIp();
  for (const auto &node : nodes) {
    std::string receivedData = "Ana are mere";
    // makeGetRequestToUrl(protocol + node);
    std::wstring wstringText = utils::to_wstring(receivedData);
    std::wcout << blowfish::dencrypt(wstringText, L"KEY") << "\n";
  }
  return 0;
}
