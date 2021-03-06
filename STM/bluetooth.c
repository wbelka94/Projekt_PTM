#include "bluetooth.h"


void init_USART()
{
	// wlaczenie taktowania wybranego portu
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	// wlaczenie taktowania wybranego uk�adu USART
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	// konfiguracja linii Tx
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_7);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	// konfiguracja linii Rx
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_7);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	USART_InitTypeDef USART_InitStructure;
	// predkosc transmisji (mozliwe standardowe opcje: 9600, 19200, 38400, 57600, 115200, ...)
	USART_InitStructure.USART_BaudRate = 9600;
	// d�ugo�� s�owa (USART_WordLength_8b lub USART_WordLength_9b)
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	// liczba bit�w stopu (USART_StopBits_1, USART_StopBits_0_5, USART_StopBits_2, USART_StopBits_1_5)
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	// sprawdzanie parzysto�ci (USART_Parity_No, USART_Parity_Even, USART_Parity_Odd)
	USART_InitStructure.USART_Parity = USART_Parity_No;
	// sprz�towa kontrola przep�ywu (USART_HardwareFlowControl_None, USART_HardwareFlowControl_RTS, USART_HardwareFlowControl_CTS, USART_HardwareFlowControl_RTS_CTS)
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	// tryb nadawania/odbierania (USART_Mode_Rx, USART_Mode_Rx )
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	// konfiguracja
	USART_Init(USART2, &USART_InitStructure);
}

uint8_t usartGetChar(void)
{
	// czekaj na odebranie danych
	while (USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == RESET);
	return USART_ReceiveData(USART2);
}

uint8_t usartSendChar(char a)
{
	while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
	USART_SendData(USART2, a);
	while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
}
