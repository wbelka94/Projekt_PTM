#include "stm32f30x_comp.h"
#include "stm32f30x_gpio.h"
#include "stm32f30x_rcc.h"
#include "stm32f30x_usart.h"


void init_USART()
{
	// wlaczenie taktowania wybranego portu
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	// wlaczenie taktowania wybranego uk³adu USART
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	// konfiguracja linii Tx
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_2);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	// konfiguracja linii Rx
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_2);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	USART_InitTypeDef USART_InitStructure;
	// predkosc transmisji (mozliwe standardowe opcje: 9600, 19200, 38400, 57600, 115200, ...)
	USART_InitStructure.USART_BaudRate = 115200;
	// d³ugoœæ s³owa (USART_WordLength_8b lub USART_WordLength_9b)
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	// liczba bitów stopu (USART_StopBits_1, USART_StopBits_0_5, USART_StopBits_2, USART_StopBits_1_5)
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	// sprawdzanie parzystoœci (USART_Parity_No, USART_Parity_Even, USART_Parity_Odd)
	USART_InitStructure.USART_Parity = USART_Parity_No;
	// sprzêtowa kontrola przep³ywu (USART_HardwareFlowControl_None, USART_HardwareFlowControl_RTS, USART_HardwareFlowControl_CTS, USART_HardwareFlowControl_RTS_CTS)
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	// tryb nadawania/odbierania (USART_Mode_Rx, USART_Mode_Rx )
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	// konfiguracja
	USART_Init(USART2, &USART_InitStructure);
}



int main(void)
{
	SystemInit();

		/* GPIOD Periph clock enable */
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);

		//RCC_HCLKConfig(RCC_SYSCLK_Div1);
		/******************************************************/
		Delay_init();

		/*******************************************************/

		GPIO_InitTypeDef  GPIO_InitStructure;

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11| GPIO_Pin_12| GPIO_Pin_13 |  GPIO_Pin_14;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_Init(GPIOE, &GPIO_InitStructure);

		init_USART();
		// wlaczenie ukladu USART
		USART_Cmd(USART2, ENABLE);
		unsigned int i;
		uint8_t a=0;
    while(1)
    {
    	/*
    	//for(i=0;i<5000000;i++);
    	Delay_ms(500);
    	GPIO_ResetBits(GPIOE,GPIO_Pin_12 | GPIO_Pin_13);
    	//for(i=0;i<1000000;i++);
    	Delay_ms(500);
    	GPIO_SetBits(GPIOE,GPIO_Pin_11 | GPIO_Pin_14);

    	//for(i=0;i<5000000;i++);
    	Delay_ms(500);
    	GPIO_ResetBits(GPIOE,GPIO_Pin_11 | GPIO_Pin_14);
    	//for(i=0;i<1000000;i++);
    	Delay_ms(500);
    	    	GPIO_SetBits(GPIOE,GPIO_Pin_12 | GPIO_Pin_13);
    	*/

    }
}
