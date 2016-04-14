/* PE11
 * PE12
 * PE13
 * PE14
 */

#include "stm32f30x_gpio.h"
#include "stm32f30x_rcc.h"

#define LEFT_FORWARD GPIO_ResetBits(GPIOE,GPIO_Pin_12); GPIO_SetBits(GPIOE,GPIO_Pin_11);
#define RIGHT_FORWARD GPIO_ResetBits(GPIOE,GPIO_Pin_14); GPIO_SetBits(GPIOE,GPIO_Pin_13);
#define LEFT_BACKWARD GPIO_ResetBits(GPIOE,GPIO_Pin_11); GPIO_SetBits(GPIOE,GPIO_Pin_12);
#define RIGHT_BACKWARD GPIO_ResetBits(GPIOE,GPIO_Pin_13); GPIO_SetBits(GPIOE,GPIO_Pin_14);

GPIO_InitTypeDef  GPIO_InitStructure;

void driving_init();

void drive_forward();

void drive_backward();
