#include "Service.h"
#include "BlowFish.h"
#include "Utilities.h"
#include <iostream>
#include <string>
#include <utility>
#include <vector>

static const std::string dataFolder{"./data/test.txt"};

static const std::wstring KEY = L"Ana are mere.";

void Service::getDataEvent(const std::shared_ptr<restbed::Session> session) {
  std::wstring text = utils::readFile("./data/test.txt");
  const auto encryptedText = blowfish::encrypt(text, KEY);
  std::string stringText = utils::to_string(encryptedText);
  sendResponseAndCloseSession(session, stringText);
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