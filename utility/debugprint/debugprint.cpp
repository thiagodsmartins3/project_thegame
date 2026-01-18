#include <iostream>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "debugprint.hpp"

void DebugPrint::sendToLogger(std::string message) {
    std::string fifo = "/tmp/debug_log";
    int fd = open(fifo.c_str(), O_WRONLY); 
    write(fd, message.c_str(), message.size());
    close(fd);
}

void DebugPrint::print(std::string message) {
    sendToLogger(message);
}