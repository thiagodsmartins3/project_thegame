#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <exception>
#include <string>

class Exception : public std::exception {
    public:
        explicit Exception(std::string msg) noexcept : message(std::move(msg)) {}
        const char* what() const noexcept override {
            return message.c_str();
        }

    private:
        std::string message;
};

#endif