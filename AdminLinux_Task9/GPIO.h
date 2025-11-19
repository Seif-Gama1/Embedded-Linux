#ifndef GPIO_H
#define GPIO_H

#include "std_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/* GPIO Port Base Addresses */
#define GPIOA (void *)0x40020000
#define GPIOB (void *)0x40020400
#define GPIOC (void *)0x40020800
#define GPIOD (void *)0x40020C00
#define GPIOE (void *)0x40021000
#define GPIOH (void *)0x40021C00

/* GPIO Register Structure */
typedef struct
{
    uint32_t MODER;      /* Mode Register */
    uint32_t OTYPER;     /* Output Type Register */
    uint32_t OSPEEDR;    /* Output Speed Register */
    uint32_t PUPDR;      /* Pull-up/Pull-down Register */
    uint32_t IDR;        /* Input Data Register */
    uint32_t ODR;        /* Output Data Register */
    uint32_t BSRR;       /* Bit Set/Reset Register */
    uint32_t LCKR;       /* Lock Register */
    uint32_t AFRL;       /* Alternate Function Low Register */
    uint32_t AFRH;       /* Alternate Function High Register */
} GPIO_TypeDef_t;

/* GPIO Pin Numbers */
typedef enum
{
    GPIO_PIN0 = 0,
    GPIO_PIN1,
    GPIO_PIN2,
    GPIO_PIN3,
    GPIO_PIN4,
    GPIO_PIN5,
    GPIO_PIN6,
    GPIO_PIN7,
    GPIO_PIN8,
    GPIO_PIN9,
    GPIO_PIN10,
    GPIO_PIN11,
    GPIO_PIN12,
    GPIO_PIN13,
    GPIO_PIN14,
    GPIO_PIN15
} GPIO_Pin_t;

/* GPIO Pin Modes */
typedef enum
{
    GPIO_MODE_INPUT = 0,
    GPIO_MODE_OUTPUT,
    GPIO_MODE_ALTERNATE,
    GPIO_MODE_ANALOG
} GPIO_Mode_t;

/* GPIO Output Types */
typedef enum
{
    GPIO_OUTPUT_PUSHPULL = 0,
    GPIO_OUTPUT_OPENDRAIN
} GPIO_OutputType_t;

/* GPIO Output Speed */
typedef enum
{
    GPIO_SPEED_LOW = 0,
    GPIO_SPEED_MEDIUM,
    GPIO_SPEED_HIGH,
    GPIO_SPEED_VERY_HIGH
} GPIO_Speed_t;

/* GPIO Pull-up/Pull-down */
typedef enum
{
    GPIO_PUPD_NONE = 0,
    GPIO_PUPD_PULLUP,
    GPIO_PUPD_PULLDOWN
} GPIO_PuPd_t;

/* GPIO Pin State */
typedef enum
{
    GPIO_PIN_LOW = 0,
    GPIO_PIN_HIGH
} GPIO_PinState_t;

/* GPIO Alternate Function */
typedef enum
{
    GPIO_AF0_SYS = 0,
    GPIO_AF1_TIM1,
    GPIO_AF2_TIM3,
    GPIO_AF3_TIM9,
    GPIO_AF4_I2C1,
    GPIO_AF5_SPI1,
    GPIO_AF6_SPI3,
    GPIO_AF7_USART1,
    GPIO_AF8_USART6,
    GPIO_AF9_I2C2,
    GPIO_AF10_OTG_FS,
    GPIO_AF11,
    GPIO_AF12_SDIO,
    GPIO_AF13,
    GPIO_AF14,
    GPIO_AF15_EVENTOUT
} GPIO_AF_t;

/* GPIO Pin Configuration Structure */
typedef struct
{
    void *port;
    GPIO_Pin_t pin;
    GPIO_Mode_t mode;
    GPIO_OutputType_t output_type;
    GPIO_Speed_t speed;
    GPIO_PuPd_t pull;
    GPIO_AF_t alternate_function;
} GPIO_PinConfig_t;

/* GPIO Register Masks */
#define GPIO_MODE_MASK 0x03U
#define GPIO_SPEED_MASK 0x03U
#define GPIO_PUPD_MASK 0x03U
#define GPIO_AF_MASK 0x0FU

uint8_t GPIO_Init(GPIO_PinConfig_t config);

uint8_t GPIO_WritePin(GPIO_PinConfig_t config, GPIO_PinState_t state);

uint8_t GPIO_ReadPin(GPIO_PinConfig_t config, GPIO_PinState_t *state);

uint8_t GPIO_TogglePin(GPIO_PinConfig_t config);

uint8_t GPIO_WritePort(void *port, uint16_t value);

uint8_t GPIO_ReadPort(void *port, uint16_t *value);

#ifdef __cplusplus
} 
#endif

#ifdef __cplusplus
// C++ namespace API
namespace GPIO_Driver {
    uint8_t GPIO_Init(GPIO_PinConfig_t config);
    uint8_t GPIO_WritePin(GPIO_PinConfig_t config, GPIO_PinState_t state);
    uint8_t GPIO_ReadPin(GPIO_PinConfig_t config, GPIO_PinState_t *state);
    uint8_t GPIO_TogglePin(GPIO_PinConfig_t config);
    uint8_t GPIO_WritePort(void *port, uint16_t value);
    uint8_t GPIO_ReadPort(void *port, uint16_t *value);
}
#endif

#endif
