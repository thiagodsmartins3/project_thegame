#ifndef DEBUGPRINT_HPP
#define DEBUGPRINT_HPP

#include <string>

class DebugPrint {
    public:
        DebugPrint(const DebugPrint&) = delete;
        void operator=(const DebugPrint&) = delete;

        static DebugPrint& getInstance() {
            static DebugPrint instance;
            return instance;
        }

        void print(std::string message);

    private: 
        DebugPrint() { }
        void sendToLogger(std::string message);
};

#endif