#include "GPIO.h"
#include <unistd.h>

int main() {
    Gpio led(538);   
    led.setDirection("out");
    __uint8_t counter = 15;
    while (counter--) {
        led.setValue(1);
        usleep(500000);
        led.setValue(0);
        usleep(500000);
    }
}