#include "minilog/logger/ConsoleLogger.hpp"
#include <iostream>
#include <minilog/minilog.hpp>

static void printHeader(const std::string& header) {
    std::cerr << "-----------------------------" << std::endl;
    std::cerr << header << std::endl;
    std::cerr << "-----------------------------" << std::endl;
}

namespace {
struct Idk {
    long number = 69;
};
}

template <>
struct std::formatter<Idk> : std::formatter<std::string_view> {
    [[nodiscard]] auto constexpr format(const Idk& p, format_context& ctx) const noexcept
    {
        return formatter<string_view>::format(
            std::format("(hehe: {})", p.number),
            ctx
        );
    }
};



int main() {
    minilog::setLevel(minilog::Level::Debug);

    printHeader("Global logger");
    minilog::debug("Hi");
    minilog::info("Hi");
    minilog::warn("Hi");
    minilog::error("Hi");
    minilog::critical("Hi");

    printHeader("Named logger");
    // Named loggers are primarily recommended for big applications that need more control over which loggers to enable,
    // though you need to try really hard for this to scale well.
    minilog::ConsoleLogger logger("launch-codes");
    logger.debug("Hi");
    logger.info("Hi");
    logger.warn("Hi");
    logger.error("Hi");
    logger.critical("Hi");

    printHeader("Global logger without stderr split (try ./bin/basic-usage-demo > /dev/null to see the difference)");
    // By default, minilog's ConsoleLogger sends error and critical to stderr instead of stdout. If you don't want that
    // for some reason, you can disable it:
    minilog::setErrorsAsStderr(false);
    minilog::debug("Hi");
    minilog::info("Hi");
    minilog::warn("Hi");
    minilog::error("Hi");
    minilog::critical("Hi");

    printHeader("Standard format args");
    minilog::critical("This is an int: {}", 69);
    logger.critical("This is a string: {}", 69);

    minilog::info("This is a number: {}", Idk{});
}
