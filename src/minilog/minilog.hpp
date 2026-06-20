#pragma once

#include "minilog/logger/Logger.hpp"
#include "minilog/logger/ConsoleLogger.hpp"

namespace minilog {

namespace _detail {

inline ConsoleLogger& getGlobalLogger() {
    static ConsoleLogger logger("");
    return logger;
}

}

template<class... Args>
inline constexpr void debug(
    const FormatStringWithSourceLocation& format,
    Args&&... args
) {
    _detail::getGlobalLogger().debug<Args...>(
        format,
        std::forward<Args>(args)...
    );
}

template<class... Args>
inline constexpr void info(
    const FormatStringWithSourceLocation& format,
    Args&&... args
) {
    _detail::getGlobalLogger().info<Args...>(
        format,
        std::forward<Args>(args)...
    );
}

template<class... Args>
inline constexpr void warn(
    const FormatStringWithSourceLocation& format,
    Args&&... args
) {
    _detail::getGlobalLogger().warn<Args...>(
        format,
        std::forward<Args>(args)...
    );
}

template<class... Args>
inline constexpr void error(
    const FormatStringWithSourceLocation& format,
    Args&&... args
) {
    _detail::getGlobalLogger().error<Args...>(
        format,
        std::forward<Args>(args)...
    );
}

template<class... Args>
inline constexpr void critical(
    const FormatStringWithSourceLocation& format,
    Args&&... args
) {
    _detail::getGlobalLogger().critical<Args...>(
        format,
        std::forward<Args>(args)...
    );
}

inline void setLevel(Level level) {
    _detail::getGlobalLogger().setLevel(level);
}

inline Level getLevel() {
    return _detail::getGlobalLogger().getLevel();
}

inline void setErrorsAsStderr(bool errorsAreStderr) {
    _detail::getGlobalLogger().setErrorsAreStderr(errorsAreStderr);
}

}
