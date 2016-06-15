#include "stm32f30x_usart.h"
#include "stm32f30x_gpio.h"
#include "stm32f30x_rcc.h"


void init_USART();

uint8_t usartGetChar(void);

uint8_t usartSendChar(char a);
