#include "UART.hpp"
#include <memory>
#include <iostream>

int main() {
    std::unique_ptr<UART> uart = std::make_unique<UART>("/dev/ttyS0", 115200);
    
    if (!uart->open()) {
        std::cout << "Failed to open UART\n";
        return 1;
    }

    uint8_t buf[128];

    while (true) {
        ssize_t n = uart->read(buf, sizeof(buf));
        if (n > 0) {
            std::cout.write(reinterpret_cast<char*>(buf), n);
            std::cout.flush();
        }
    }
}
