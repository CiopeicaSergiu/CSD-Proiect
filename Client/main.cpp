#include <iostream>
#include <sstream>
#include <string>

#include "Settings.h"
#include "Utilities.h"
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/cURLpp.hpp>

static const std::string protocol{"http://"};
static const std::string receivedDataFolder{"./receivedData/"};
using namespace curlpp::options;

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

int main() {
  Settings settings("settings.yaml");
  const auto &nodes = settings.getNodesIp();
  for (const auto &node : nodes) {
    std::cout << "I received from " << node << ":\n";
    const std::string text = makeGetRequestToUrl(protocol + node);
    std::cout << text << "\n";
    utils::writeToFile(receivedDataFolder + node, text);
  }
  return 0;
}
