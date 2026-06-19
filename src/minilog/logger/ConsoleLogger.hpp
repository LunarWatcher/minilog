#pragma once

#include "minilog/logger/Logger.hpp"
namespace minilog {

class ConsoleLogger : public Logger {
protected:
    void writeMessage(
        std::string_view msg,
        Level level
    ) override;
    bool supportsColour(
        Level level
    ) override;

    bool errorsAreStderr = true;
public:
    ConsoleLogger(
        std::string&& name
    ) : Logger(
        std::move(name)
    ) {}

    void setErrorsAreStderr(bool errorsAreStderr) {
        this->errorsAreStderr = errorsAreStderr;
    }
};
}
