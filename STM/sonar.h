#include "stm32f30x_comp.h"
#include "stm32f30x_gpio.h"
#include "stm32f30x_rcc.h"
#include "stm32f30x_tim.h"
#include "stm32f30x_misc.h"
#include "delay.h"

#define ECHO GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_3)
uint8_t sonar;
uint32_t t;

void sonar_init();

void start_pomiar();

void stop_pomiar();
