#include "driving.h"

void driving_init(){
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11| GPIO_Pin_12| GPIO_Pin_13 |  GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	GPIO_SetBits(GPIOE,GPIO_Pin_11 | GPIO_Pin_14);
	GPIO_ResetBits(GPIOE,GPIO_Pin_12 | GPIO_Pin_13);
}

void drive_forward(){
	stop_drive();
    GPIO_ResetBits(GPIOE,GPIO_Pin_12 | GPIO_Pin_13);
    GPIO_SetBits(GPIOE,GPIO_Pin_11 | GPIO_Pin_14);
}

void drive_backward(){
	stop_drive();
    GPIO_ResetBits(GPIOE,GPIO_Pin_11 | GPIO_Pin_14);
    GPIO_SetBits(GPIOE,GPIO_Pin_12 | GPIO_Pin_13);
}

void stop_drive(){
	GPIO_ResetBits(GPIOE,GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14);
}
