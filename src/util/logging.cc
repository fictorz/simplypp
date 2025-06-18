#include "logging.h"

namespace util {
void Logging::init(char *argv[]) {
  // Initialize Google’s logging library.
  google::InitGoogleLogging(argv[0]);
  FLAGS_logtostderr = 1;
}
} // namespace util
