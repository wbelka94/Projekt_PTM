/* PE11
 * PE12
 * PE13
 * PE14
 */

#include "stm32f30x_gpio.h"
#include "stm32f30x_rcc.h"
#include "stm32f30x_tim.h"
#include "sonar.h"

#define LEFT_FORWARD GPIO_ResetBits(GPIOE,GPIO_Pin_12); GPIO_SetBits(GPIOE,GPIO_Pin_11);
#define RIGHT_BACKWARD GPIO_ResetBits(GPIOE,GPIO_Pin_14); GPIO_SetBits(GPIOE,GPIO_Pin_13);
#define LEFT_BACKWARD GPIO_ResetBits(GPIOE,GPIO_Pin_11); GPIO_SetBits(GPIOE,GPIO_Pin_12);
#define RIGHT_FORWARD GPIO_ResetBits(GPIOE,GPIO_Pin_13); GPIO_SetBits(GPIOE,GPIO_Pin_14);
#define LEFT_STOP GPIO_ResetBits(GPIOE,GPIO_Pin_11 | GPIO_Pin_12);
#define RIGHT_STOP GPIO_ResetBits(GPIOE,GPIO_Pin_13 | GPIO_Pin_14);
#define STOP_MOTORS LEFT_STOP; RIGHT_STOP;

void driving_init();

void update_motors(uint8_t left, uint8_t right);
