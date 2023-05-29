#include "Service.h"
#include "BlowFish.h"
#include "Utilities.h"
#include <boost/json/serialize.hpp>
#include <boost/json/value_from.hpp>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
static const std::string dataFolder{"./data/test.txt"};

static const std::wstring KEY = L"123.";

namespace {
template <typename T> void printWStringValues(const T &elements) {
  for (const auto &el : elements) {
    std::wcout << el << " ";
  }
}
std::vector<std::uint32_t> toVecUint32(const std::wstring &text) {
  std::vector<std::uint32_t> result;
  result.reserve(text.size());
  std::transform(text.cbegin(), text.cend(), std::back_inserter(result),
                 [](const auto &ch) { return ch; });
  return result;
}

std::wstring toWstring(const std::vector<std::uint32_t> &vec) {
  std::wstring result;
  result.reserve(vec.size());
  std::transform(vec.cbegin(), vec.cend(), std::back_inserter(result),
                 [](const auto &ch) { return ch; });
  return result;
}
} // namespace
void Service::getDataEvent(const std::shared_ptr<restbed::Session> session) {
  std::wstring text = utils::readFile("./data/test.txt");
  auto encryptedText = blowfish::encrypt(text, KEY);
  auto decryptedText = blowfish::dencrypt(encryptedText, KEY);
  // printWStringValues(
  //     toVecUint32(text)); // std::cout <<
  // Json::serialize(Json::value_from(encryptedText));
  sendResponseAndCloseSession(
      session, Json::value_from(utils::toVecUint8(toVecUint32(encryptedText))));
}

void Service::setEndPointForGetData(
    const std::shared_ptr<restbed::Resource> &resource) {

  resource->set_path("/");
  resource->set_method_handler(
      "GET", [this](const std::shared_ptr<restbed::Session> session) {
        getDataEvent(session);
      });
}

void Service::configureEndpoints() { setEndPointForGetData(resource); }