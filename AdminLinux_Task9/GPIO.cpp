#include "GPIO.h"

#ifdef __cplusplus
namespace GPIO_Driver {
#endif

uint8_t GPIO_Init(GPIO_PinConfig_t config){
    GPIO_TypeDef_t *port = (GPIO_TypeDef_t *)config.port;
    GPIO_Pin_t pin = config.pin;
    uint32_t temp = 0;

    if (port == NULL_PTR || pin>GPIO_PIN15 || pin<GPIO_PIN0){
        return 0;
    }

    /* configure pin mode */
    temp = port->MODER;
    temp &= ~(GPIO_MODE_MASK << (pin*2));
    temp |= config.mode << (pin*2);
    port->MODER = temp;

        /* Configure Output Type */
    temp = port->OTYPER;
    temp &= ~(1U << pin);
    temp |= (config.output_type << pin);
    port->OTYPER = temp;

    /* Configure Output Speed */
    temp = port->OSPEEDR;
    temp &= ~(GPIO_SPEED_MASK << (pin * 2));
    temp |= (config.speed << (pin * 2));
    port->OSPEEDR = temp;

    /* Configure Pull-up/Pull-down */
    temp = port->PUPDR;
    temp &= ~(GPIO_PUPD_MASK << (pin * 2));
    temp |= (config.pull << (pin * 2));
    port->PUPDR = temp;

    /* Configure Alternate Function */
    if (config.mode == GPIO_MODE_ALTERNATE)
    {
        if (pin < 8)
        {
            temp = port->AFRL;
            temp &= ~(GPIO_AF_MASK << (pin * 4));
            temp |= (config.alternate_function << (pin * 4));
            port->AFRL = temp;
        }
        else
        {
            temp = port->AFRH;
            temp &= ~(GPIO_AF_MASK << ((pin - 8) * 4));
            temp |= (config.alternate_function << ((pin - 8) * 4));
            port->AFRH = temp;
        }
    }
    return 1;

}

uint8_t GPIO_WritePin(GPIO_PinConfig_t config, GPIO_PinState_t state){
    GPIO_TypeDef_t *port = (GPIO_TypeDef_t *)config.port;
    GPIO_Pin_t pin = config.pin;

    if (port == NULL_PTR || pin>GPIO_PIN15 || pin<GPIO_PIN0){
        return 0;
    }

    if (state == GPIO_PIN_HIGH){
        port-> BSRR = (1U << pin);
    }else{
        port ->BSRR = (1U << (pin+16));
    }
    return 1;
}

uint8_t GPIO_ReadPin(GPIO_PinConfig_t config, GPIO_PinState_t *state){
    GPIO_TypeDef_t *port = (GPIO_TypeDef_t *)config.port;   
    GPIO_Pin_t pin = config.pin;

    if (port == NULL_PTR || pin>GPIO_PIN15 || pin<GPIO_PIN0){
        return 0;
    }

    if (port->IDR & (1U<<pin)){
        *state = GPIO_PIN_HIGH;
    }else{
        *state = GPIO_PIN_LOW;
    }
    return 1;
}

uint8_t GPIO_TogglePin(GPIO_PinConfig_t config)
{
    GPIO_TypeDef_t *port = (GPIO_TypeDef_t *)config.port;
    GPIO_Pin_t pin = config.pin;
    if (port == NULL_PTR || pin>GPIO_PIN15 || pin<GPIO_PIN0){
        return 0;
    }

    port->ODR ^= (1U << pin);
    return 1;
}

uint8_t GPIO_WritePort(void *port, uint16_t value)
{
    GPIO_TypeDef_t *gpio_port = (GPIO_TypeDef_t *)port;
    if (port == NULL_PTR){
        return 0;
    }

    gpio_port->ODR = value;
    return 1;
}

uint8_t GPIO_ReadPort(void *port, uint16_t *value)
{
    GPIO_TypeDef_t *gpio_port = (GPIO_TypeDef_t *)port;
    if (gpio_port == NULL_PTR || value == NULL_PTR){
        return 0;
    }

    *value = (uint16_t)(gpio_port->IDR);
    return 1;
}

#ifdef __cplusplus
} // namespace GPIO_Driver
#endif