#include "Service.h"

void Service::getDataEvent(const std::shared_ptr<restbed::Session> session) {
  const std::string message{"Ana are mere"};
  sendResponseAndCloseSession(session, message);
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
