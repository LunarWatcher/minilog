#pragma once

namespace minilog {

enum class Level : short {
    // Reserved for future use
    // Trace = 10,
    Debug = 20,
    Info = 30,
    Warning = 40,
    Error = 50,
    Critical = 60,
    Off = 100,
};

}
