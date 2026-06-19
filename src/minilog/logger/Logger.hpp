#pragma once

#include "Level.hpp"
#include "Magic.hpp"

#include <filesystem>
#include <source_location>
#include <string>
#include <string_view>
#include <format>
#include <chrono>

namespace minilog {

class Logger {
private:
    const std::string loggerName;

    Level level = Level::Info;

protected:
    virtual bool supportsColour(
        Level level
    ) = 0;
    virtual void writeMessage(
        std::string_view msg,
        Level level
    ) = 0;

    template <Level level>
    constexpr std::string_view getColour() {
        if constexpr(level == Level::Debug) {
            return "\033[90m";
        } else if constexpr (level == Level::Info) {
            return "\033[34m";
        } else if constexpr (level == Level::Warning) {
            return "\033[93m";
        } else if constexpr (level == Level::Error) {
            return "\033[91m";
        } else if constexpr (level == Level::Critical) {
            return "\033[31m";
        }
    }

    constexpr std::string_view getReset() {
        return "\033[0m";
    }

    template <Level level, class... Args>
    inline constexpr void log(
        const std::format_string<Args...>& fmt,
        Args&&... args,
        const std::source_location& loc
    ) {
        if (this->level > level) {
            return;
        }

        if (loggerName != "") {
            writeMessage(
                std::format(
                    "{}{:%T} | {:<8} | {:>32}:{} | {:<16} | {}{}\n",
                    this->supportsColour(level) ? getColour<level>() : "",
                    std::chrono::floor<std::chrono::milliseconds>(
                        std::chrono::system_clock::now()
                    ),
                    magic::levelToString<level>(),
                    // TODO: this isn't optimal, but avoids abs paths
                    // GCC has -ffile-prefix-map that may or may not help, but this is just the lazy way to make the
                    // abspath a filename
                    // -ffile-prefix-map seems to mainly be useful for converting a full path to a project-local path
                    // and not to a filename directly.
                    // https://www.reddit.com/r/cpp/comments/1odzc93/source_locationfile_name_is_a_misleading_name/
                    // Could potentially make a thin alternate wrapper that uses __FILE_NAME__, but that won't be
                    // portable I imagine? Not sure if it builds on windows anyway, and that's an abstraction I can't be
                    // bothered dealing with
                    std::filesystem::path(
                        loc.file_name()
                    ).filename().string(),
                    loc.line(),
                    loggerName,
                    std::format<Args...>(fmt, std::forward<Args>(args)...),
                    this->supportsColour(level) ? getReset() : ""
                ),
                level
            );
        } else {
            writeMessage(
                std::format(
                    "{}{:%T} | {:<8} | {:>32}:{} | {}{}\n",
                    this->supportsColour(level) ? getColour<level>() : "",
                    std::chrono::floor<std::chrono::milliseconds>(
                        std::chrono::system_clock::now()
                    ),
                    magic::levelToString<level>(),
                    std::filesystem::path(
                        loc.file_name()
                    ).filename().string(),
                    loc.line(),
                    std::format<Args...>(fmt, std::forward<Args>(args)...),
                    this->supportsColour(level) ? getReset() : ""
                ),
                level
            );
        }
    }
public:
    Logger(
        std::string&& loggerName
    ) : loggerName(std::move(loggerName)) {}
    virtual ~Logger() = default;

    template <class... Args>
    inline constexpr void debug(
        const std::format_string<Args...>& format,
        Args&&... args,
        const std::source_location& loc = std::source_location::current()
    ) {
        log<Level::Debug, Args...>(format, std::forward<Args>(args)..., loc);
    }

    template <class... Args>
    inline constexpr void info(
        const std::format_string<Args...>& format,
        Args&&... args,
        const std::source_location& loc = std::source_location::current()
    ) {
        log<Level::Info, Args...>(format, std::forward<Args>(args)..., loc);
    }

    template <class... Args>
    inline constexpr void warn(
        const std::format_string<Args...>& format,
        Args&&... args,
        const std::source_location& loc = std::source_location::current()
    ) {
        log<Level::Warning, Args...>(format, std::forward<Args>(args)..., loc);
    }

    template <class... Args>
    inline constexpr void error(
        const std::format_string<Args...>& format,
        Args&&... args,
        const std::source_location& loc = std::source_location::current()
    ) {
        log<Level::Error, Args...>(format, std::forward<Args>(args)..., loc);
    }

    template <class... Args>
    inline constexpr void critical(
        const std::format_string<Args...>& format,
        Args&&... args,
        const std::source_location& loc = std::source_location::current()
    ) {
        log<Level::Critical, Args...>(format, std::forward<Args>(args)..., loc);
    }

    void setLevel(Level level) {
        this->level = level;
    }
};

}
