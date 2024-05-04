#ifndef _PROTO_MYMESSAGE_H_
#define _PROTO_MYMESSAGE_H_

#include <iostream>
#include "../../build/src/example.pb.h"  // Generated protobuf header file

namespace proto {
class MyMessageHandler {
public:
  std::string getName();
};
} // namespace util

#endif // _PROTO_MYMESSAGE_H_
