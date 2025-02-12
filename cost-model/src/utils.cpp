#include "utils.h"

const size_t calculateMaxLength(const std::string &time,
                                const std::string &file,
                                const std::string &line,
                                const std::string &func,
                                const std::string &message) {
  size_t maxLength = 0;
  maxLength = std::max(maxLength, time.length());
  maxLength = std::max(maxLength, file.length());
  maxLength = std::max(maxLength, line.length());
  maxLength = std::max(maxLength, func.length());
  maxLength = std::max(maxLength, message.length());
  return maxLength;
}
