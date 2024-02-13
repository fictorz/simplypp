#include "message_handler.h"


namespace proto {
std::string MyMessageHandler::getName() {
  myproto::MyMessage myMessage;
  myMessage.set_id(2);
  myMessage.set_name("test");

  return myMessage.name();
}
} // namespace util
