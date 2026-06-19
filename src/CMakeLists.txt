add_library(minilog
    minilog/logger/ConsoleLogger.cpp
)

target_include_directories(minilog PUBLIC ./)
