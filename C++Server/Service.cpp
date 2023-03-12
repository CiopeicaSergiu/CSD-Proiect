#include "Service.h"
#include "Utilities.h"
#include <iostream>
#include <string>
#include <utility>
#include <vector>

void Service::getDataEvent(const std::shared_ptr<restbed::Session> session) {
  const std::string text = utils::readFromFile("./testFile.txt");
  std::cout << text << "\n";
  sendResponseAndCloseSession(session, text);
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