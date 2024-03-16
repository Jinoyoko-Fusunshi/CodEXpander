#pragma once

class Exception : std::exception {
private:
    std::string message;

public:
    Exception(std::string message) {
        this->message = std::move(message);
    }

    const char* what() const noexcept override  {
        return message.c_str();
    }

    std::string& GetMessage() {
        return message;
    }
};
