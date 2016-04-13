
#include "stm32f30x_gpio.h"
#include "stm32f30x_rcc.h"
int main(void)
{
	SystemInit();

		/* GPIOD Periph clock enable */
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);

		GPIO_InitTypeDef  GPIO_InitStructure;

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11| GPIO_Pin_12| GPIO_Pin_13 |  GPIO_Pin_14;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_Init(GPIOE, &GPIO_InitStructure);
		GPIO_SetBits(GPIOE,GPIO_Pin_11 | GPIO_Pin_14);
		    	GPIO_ResetBits(GPIOE,GPIO_Pin_12 | GPIO_Pin_13);
		unsigned int i;
    while(1)
    {
    	for(i=0;i<5000000;i++);
    	GPIO_ResetBits(GPIOE,GPIO_Pin_12 | GPIO_Pin_13);
    	for(i=0;i<1000000;i++);
    	GPIO_SetBits(GPIOE,GPIO_Pin_11 | GPIO_Pin_14);

    	for(i=0;i<5000000;i++);
    	GPIO_ResetBits(GPIOE,GPIO_Pin_11 | GPIO_Pin_14);
    	for(i=0;i<1000000;i++);
    	    	GPIO_SetBits(GPIOE,GPIO_Pin_12 | GPIO_Pin_13);
    }
}
