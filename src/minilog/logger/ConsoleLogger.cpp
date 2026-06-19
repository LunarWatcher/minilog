#include "ConsoleLogger.hpp"

#ifdef _WIN32

#else
#include <unistd.h>
#endif

#include <cstdio>
#include <iostream>

/**
 * The contents of this anonymous namespace are sourced from stc, also under the MIT license:
 * https://codeberg.org/LunarWatcher/stc/src/commit/f905a5d33fadfb3403e3d5d35d43aa4a01bfccdf/src/stc/Environment.hpp
 *
 * This has been copied for now since we're operating on std::cout and std::cerr, but still want to handle redirects of
 * std::cout differently.
 */
namespace {

enum class StreamType {
    Stdout,
    Stderr,
    Other
};

template <typename CharT>
static constexpr StreamType getOutputStreamType(std::basic_ostream<CharT>& ss) {
    if constexpr(std::is_same_v<CharT, char>) {
        if (&ss == &std::cout) {
            return StreamType::Stdout;
        } else if (&ss == &std::cerr) {
            return StreamType::Stderr;
        }
    } else if constexpr (std::is_same_v<CharT, wchar_t>){
        if (&ss == &std::wcout) {
            return StreamType::Stdout;
        } else if (&ss == &std::wcerr) {
            return StreamType::Stderr;
        }
    }
    return StreamType::Other;
}

template <typename CharT>
inline constexpr bool isStreamTTY(StreamType type) {
    if (type == StreamType::Other) {
        return false;
    }
    auto streamDescriptor = type == StreamType::Stdout ? stdout : stderr;

#ifdef _WIN32
    return _isatty(_fileno(streamDescriptor));
#else
    return isatty(fileno(streamDescriptor));
#endif
}

}

namespace minilog {

void ConsoleLogger::writeMessage(
    std::string_view msg,
    Level level
) {
    // TODO: std::cout is sync across <<, which makes it an excellent choice to avoid implementing sync primitives or
    // the likes. But it's not great for performance, and I don't know how it deals with multithreaded performance. It's
    // good enough for now though
    (level >= Level::Error && errorsAreStderr ? std::cerr : std::cout) << msg;
}

bool ConsoleLogger::supportsColour(
    Level level
) {
    return isStreamTTY<char>(
        getOutputStreamType(
            level >= Level::Error && errorsAreStderr ? std::cerr : std::cout
        )
    );
}

}
