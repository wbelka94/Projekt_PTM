#include "stm32f30x_rcc.h"
#include "stm32f30x.h"

__IO uint32_t TimingDelay = 0;
RCC_ClocksTypeDef RCC_Clocks;

void Delay_init();

void SysTick_Handler(void);

void Delay_ms(__IO uint32_t nTime);

void TimingDelay_Decrement(void);
