#include <memory>
#include <iostream>
#include <cstdio>
#include <sys/stat.h>
#include "logger.hpp"

void Logger::messageLog() {
    bool isRunning = true;
    std::string fifo = "/tmp/debug_log";
    std::unique_ptr<char[]> message = std::make_unique<char[]>(2048);

    while(isRunning) {
        int fd = open(fifo.c_str(), O_RDONLY);
        read(fd, message.get(), 2048);
        std::cout << message << std::endl;
        close(fd);
    }
}

void Logger::log() {
    messageLog();
}


