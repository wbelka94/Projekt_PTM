#include "delay.h"

__IO uint32_t TimingDelay = 0;
RCC_ClocksTypeDef RCC_Clocks;

void Delay_init(){
	RCC_GetClocksFreq(&RCC_Clocks);
	SysTick_Config(RCC_Clocks.HCLK_Frequency/1000000);
}

void SysTick_Handler(void){
	TimingDelay_Decrement();
}

void Delay_us(__IO uint32_t nTime){
	TimingDelay = nTime;
	while(TimingDelay != 0);
}

void Delay_ms(__IO uint32_t nTime){
	TimingDelay = nTime*1000;
	while(TimingDelay != 0);
}

void TimingDelay_Decrement(void){
	if (TimingDelay != 0x00){
		TimingDelay--;
	}
}
