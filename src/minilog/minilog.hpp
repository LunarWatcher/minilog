#pragma once

#include "minilog/logger/Logger.hpp"
#include "minilog/logger/ConsoleLogger.hpp"
#include <source_location>

namespace minilog {

namespace _detail {

inline ConsoleLogger& getGlobalLogger() {
    static ConsoleLogger logger("");
    return logger;
}

}

template <class... Args>
inline constexpr void debug(
    const std::format_string<Args...>& format,
    Args&&... args,
    const std::source_location& loc = std::source_location::current()
) {
    _detail::getGlobalLogger().debug<Args...>(
        format,
        std::forward<Args>(args)...,
        loc
    );
}

template <class... Args>
inline constexpr void info(
    const std::format_string<Args...>& format,
    Args&&... args,
    const std::source_location& loc = std::source_location::current()
) {
    _detail::getGlobalLogger().info<Args...>(
        format,
        std::forward<Args>(args)...,
        loc
    );
}

template <class... Args>
inline constexpr void warn(
    const std::format_string<Args...>& format,
    Args&&... args,
    const std::source_location& loc = std::source_location::current()
) {
    _detail::getGlobalLogger().warn<Args...>(
        format,
        std::forward<Args>(args)...,
        loc
    );
}

template <class... Args>
inline constexpr void error(
    const std::format_string<Args...>& format,
    Args&&... args,
    const std::source_location& loc = std::source_location::current()
) {
    _detail::getGlobalLogger().error<Args...>(
        format,
        std::forward<Args>(args)...,
        loc
    );
}

template <class... Args>
inline constexpr void critical(
    const std::format_string<Args...>& format,
    Args&&... args,
    const std::source_location& loc = std::source_location::current()
) {
    _detail::getGlobalLogger().critical<Args...>(
        format,
        std::forward<Args>(args)...,
        loc
    );
}

inline void setLevel(Level level) {
    _detail::getGlobalLogger().setLevel(level);
}

inline void setErrorsAsStderr(bool errorsAreStderr) {
    _detail::getGlobalLogger().setErrorsAreStderr(errorsAreStderr);
}

}
