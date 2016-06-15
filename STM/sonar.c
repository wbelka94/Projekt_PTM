#include "sonar.h"



void sonar_init(){
	//Triger
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	GPIO_InitTypeDef  GPIO_InitStructure2;
	GPIO_InitStructure2.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure2.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure2.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStructure2);


	//TIM3
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_TimeBaseStructure.TIM_Period = 4;            //200kHz
	TIM_TimeBaseStructure.TIM_Prescaler = 71;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up ;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	//NVIC
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x00;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x00;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
}

void pomiar_stop(){
	int cm  = t /58;
	if(cm<30){
		GPIO_SetBits(GPIOE,GPIO_Pin_15);
		sonar = 1;
	}
	else{
		GPIO_ResetBits(GPIOE,GPIO_Pin_15);
		sonar = 0;
	}
	//pomiar_wyslij(cm);
}

void pomiar_start(){
	t=0;
	GPIO_SetBits(GPIOD,GPIO_Pin_4);
	Delay_us(10);
	GPIO_ResetBits(GPIOD,GPIO_Pin_4);
	while(ECHO==0);
	TIM_Cmd(TIM3, ENABLE);
}

void pomiar_wyslij(double cm){
	usartSendChar(cm);
}

