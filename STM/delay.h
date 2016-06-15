#include "stm32f30x_rcc.h"
#include "stm32f30x.h"



void Delay_init();

void SysTick_Handler(void);

void Delay_us(__IO uint32_t nTime);

void Delay_ms(__IO uint32_t nTime);

void TimingDelay_Decrement(void);
