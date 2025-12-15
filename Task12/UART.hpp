#pragma once

#include <string>
#include <cstdint>
#include <unistd.h>

class UART {
    private:
        std::string devicePath;
        int fd;

        bool configure();
    public:
        UART(const std::string& device, int baudrate);
        ~UART();

        UART(const UART&)            = delete;
        UART& operator=(const UART&) = delete;

        UART(UART&&);
        UART& operator=(UART&&);

        bool open();
        ssize_t write(const uint8_t* data, size_t len);
        ssize_t read(uint8_t* data, size_t len);

};
