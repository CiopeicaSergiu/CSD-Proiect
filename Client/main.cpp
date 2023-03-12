#include <iostream>
#include <sstream>
#include <string>

#include "Utilities.h"
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/cURLpp.hpp>

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
  std::cout << "I received: \n";
  const std::string text = makeGetRequestToUrl("http://192.168.0.105:11420");
  std::cout << text << "\n";
  utils::writeToFile("received.txt", text);
  return 0;
}
