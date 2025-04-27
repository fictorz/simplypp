#ifndef _UTIL_LOGGING_H_
#define _UTIL_LOGGING_H_

#pragma once

#include <string>

namespace util {

class Logging {
public:
  static void init(char *argv[]);
};
} // namespace util

#endif // _UTIL_LOGGING_H_
