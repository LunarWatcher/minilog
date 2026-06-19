#pragma once

#include "Level.hpp"
#include <string_view>

namespace minilog::magic {

template <Level level>
consteval std::string_view levelToString() {
    if constexpr (level == Level::Debug) {
        return "debug";
    } else if constexpr (level == Level::Info) {
        return "info";
    } else if constexpr (level == Level::Warning) {
        return "warning";
    } else if constexpr (level == Level::Error) {
        return "error";
    } else if constexpr (level == Level::Critical) {
        return "critical";
    }
}

}
