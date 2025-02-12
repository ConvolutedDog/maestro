#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <string>

#define EXIT_WITH_MESSAGE(code, message)                                       \
  do {                                                                         \
    std::cerr << "ERR Message: " << message << std::endl;                      \
    std::cerr << "File: " << __FILE__ << std::endl;                            \
    std::cerr << "Lineno: " << __LINE__ << std::endl;                          \
    std::cerr << "Function: " << __func__ << std::endl;                        \
    std::exit(code);                                                           \
  } while (0)

#define RED_TEXT "\033[31m"
#define GREEN_TEXT "\033[32m"
#define YELLOW_TEXT "\033[33m"
#define BLUE_TEXT "\033[34m"
#define RESET_TEXT "\033[0m"

const size_t calculateMaxLength(const std::string &time,
                                const std::string &file,
                                const std::string &line,
                                const std::string &func,
                                const std::string &message);

#define FANCY_EXIT_WITH_MESSAGE(code, message)                                 \
  do {                                                                         \
    auto now = std::chrono::system_clock::now();                               \
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);          \
    std::stringstream timeStream;                                              \
    timeStream << std::put_time(std::localtime(&now_time),                     \
                                "%Y-%m-%d %H:%M:%S");                          \
    std::string timeStr = "[Time]: " + timeStream.str();                       \
    std::string fileStr = "[File]: " + std::string(__FILE__);                  \
    std::string lineStr = "[Line]: " + std::to_string(__LINE__);               \
    std::string funcStr = "[Func]: " + std::string(__func__);                  \
    std::string messageStr = "[Detail]: " + std::string(message);              \
    const size_t maxLength =                                                   \
        calculateMaxLength(timeStr, fileStr, lineStr, funcStr, messageStr);    \
    std::string separator(maxLength, '=');                                     \
    std::cerr << "\n" << RED_TEXT << separator << RESET_TEXT << std::endl;     \
    std::cerr << RED_TEXT << "[Error]: The programe has exited." << RESET_TEXT \
              << std::endl;                                                    \
    std::cerr << RED_TEXT << separator << RESET_TEXT << std::endl;             \
    std::cerr << timeStr << std::endl;                                         \
    std::cerr << fileStr << std::endl;                                         \
    std::cerr << lineStr << std::endl;                                         \
    std::cerr << funcStr << std::endl;                                         \
    std::cerr << messageStr << std::endl;                                      \
    std::cerr << RED_TEXT << separator << RESET_TEXT << "\n" << std::endl;     \
    std::exit(code);                                                           \
  } while (0)
