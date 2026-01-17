#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <exception>
#include <string>

class Exception : public std::exception {
    std::string msg_;
public:
    explicit Exception(std::string msg) noexcept : msg_(std::move(msg)) {}
    const char* what() const noexcept override {
        return msg_.c_str();
    }
};

#endif