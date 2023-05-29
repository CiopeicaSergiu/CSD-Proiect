#include "Server.h"
#include <boost/json/serialize.hpp>
#include <boost/json/value.hpp>
#include <boost/json/value_from.hpp>

void Server::sendResponseAndCloseSession(
    const std::shared_ptr<restbed::Session> &session,
    const boost::json::value &dataValue) {

  session->close(restbed::OK, boost::json::serialize(dataValue),
                 {{"Content-Type", "application/json"}});
}

void Server::sendUnfoundAndCloseSession(
    const std::shared_ptr<restbed::Session> &session,
    const std::wstring message) {

  session->close(restbed::UNAUTHORIZED,
                 boost::json::serialize(boost::json::value_from(message)),
                 {{"Content-Type", "application/json"}});
}

void Server::setSettings() {
  settings = std::make_shared<restbed::Settings>();
  settings->set_port(port);
  settings->set_default_header("Connection", "close");
}

Server::Server(const size_t port) { this->port = port; }

void Server::start() {
  resource = std::make_shared<restbed::Resource>();

  configureEndpoints();
  setSettings();

  restbed::Service service;
  service.publish(resource);
  service.start(settings);
}
