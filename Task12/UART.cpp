#include "UART.hpp"

#include <fcntl.h>
#include <termios.h>
#include <cstring>
#include <iostream>

UART::UART(const std::string& device, int baudrate)
    : devicePath(device), fd(-1) {}

UART::~UART() {
    if (fd != -1) {
        close(fd);
        fd = -1;
    }
}

// move constructor
UART::UART(UART&& other){
    devicePath = std::move(other.devicePath);
    fd = other.fd;
    other.fd = -1;
}

// move assignment
UART& UART::operator=(UART&& other){
    if (this != &other) {
        if (fd != -1)
            close(fd);

        devicePath = std::move(other.devicePath);
        fd = other.fd;
        other.fd = -1;
    }
    return *this;
}

bool UART::open() {
    fd = ::open(devicePath.c_str(), O_RDWR | O_NOCTTY | O_SYNC);
    if (fd == -1) {
        std::cout << "UART open failed\n";
        return false;
    }
    return configure();
}

bool UART::configure() {
    struct termios tty {};
    if (tcgetattr(fd, &tty) != 0) {
        std::cout << "tcgetattr failed\n";
        return false;
    }

    cfmakeraw(&tty);

    cfsetispeed(&tty, B115200);
    cfsetospeed(&tty, B115200);

    tty.c_cflag |= (CLOCAL | CREAD);
    tty.c_cflag &= ~CRTSCTS; // no HW flow control

    if (tcsetattr(fd, TCSANOW, &tty) != 0) {
        std::cout << "tcsetattr failed\n";
        return false;
    }
    return true;
}

ssize_t UART::write(const uint8_t* data, size_t len) {
    if (fd == -1) {
        std::cout << "UART not open for write\n";
        return -1;
    }
    return ::write(fd, data, len);
}

ssize_t UART::read(uint8_t* data, size_t len) {
    if (fd == -1) {
        std::cout << "UART not open for read\n";
        return -1;
    }
    return ::read(fd, data, len);
}
