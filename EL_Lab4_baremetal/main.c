#include "BCM2837_GPIO.h"

#define GPIO26 (1 << 26)

void delay() {
    for(volatile int i = 0; i < 50000000; i++);
}

int seif(void){

    
    unsigned int reg;
    
    /* Set GPIO26 as output */
    reg = BCM2837_GET32(BCM2837_GPFSEL2); /* Function selector reg */
    reg &= ~(7 << 18);
    reg |=  (1 << 18);
    BCM2837_PUT32(BCM2837_GPFSEL2, reg);

    while(1){
        BCM2837_PUT32(BCM2837_GPSET0, GPIO26);
        delay();

        BCM2837_PUT32(BCM2837_GPCLR0, GPIO26);
        delay();
    }
}