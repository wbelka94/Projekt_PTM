#include "driving.h"

void driving_init(){
	/*PINY DO STEROWANIA SILNIKAMI*/
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11| GPIO_Pin_12| GPIO_Pin_13 |  GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	/*PWM SILNIKOW*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_TimeBaseStructure.TIM_Period = 99;				//1kHz
	TIM_TimeBaseStructure.TIM_Prescaler = 719;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up ;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC1Init(TIM4, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
	TIM_OC2Init(TIM4, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);


	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_2);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_2);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init(GPIOB,&GPIO_InitStructure);

	TIM_Cmd(TIM4,ENABLE);
}

void update_motors(uint8_t left, uint8_t right){

	int z_pwm = 10;
	if(left > 40){
		if(left >= 60  && !sonar){
			TIM4->CCR1 = left - z_pwm;
			LEFT_FORWARD;
		}
		else{
			LEFT_STOP;
		}
	}
	else{
		TIM4->CCR1 = 100 - left - z_pwm;
		LEFT_BACKWARD;
	}


	if(right > 40){
		if(right >= 60  && !sonar){
			TIM4->CCR2 = right - z_pwm;
			RIGHT_FORWARD;
		}
		else{
			RIGHT_STOP;
		}
	}
	else{
		TIM4->CCR2 = 100 - right - z_pwm;
		RIGHT_BACKWARD;
	}

}


