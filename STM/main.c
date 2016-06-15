#include "stm32f30x_comp.h"
#include "stm32f30x_gpio.h"
#include "stm32f30x_rcc.h"
#include "stm32f30x_usart.h"
#include "stm32f30x_tim.h"
#include "driving.h"
#include "bluetooth.h"
#include "string.h"

uint8_t x = 0;

uint8_t l_pwm = 0;
uint8_t r_pwm = 0;


void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)!=RESET)
	{
		t+=5;
		if(ECHO==0){
			TIM_Cmd(TIM3,DISABLE);
			pomiar_stop();
			t=0;
		}
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
	}
}

void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)!=RESET)
	{
		pomiar_start();
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}
}
void sterowanie(){
	/* z suma kontrolna		SPxxLyyFzz		zz=xx+yy
	 * S-rozpoczecie
	 * P-znak poprzedzajacy wartosc dla prawego silnika
	 * L-znak poprzedzajacy wartosc dla lewego silnika
	 * F-zakonczenie, po tym znaku oczekuje na sume kontrolna*/
	int checksum;
	int koniec;
		do{
			switch(usartGetChar()){
				case 's':
					checksum = 0;
					koniec = 0;
					break;
				case 'p':
					r_pwm = usartGetChar();
					checksum += r_pwm;
					break;
				case 'l':
					l_pwm = usartGetChar();
					checksum += l_pwm;
					break;
				case 'f':
					koniec = usartGetChar();
					break;
			}
		}while(checksum != koniec);
	update_motors(l_pwm,r_pwm);
}

int main(void)
{
	SystemInit();
	init_USART();
	Delay_init();
	driving_init();
	sonar_init();

	USART_Cmd(USART2, ENABLE);

	while(1){
		sterowanie();
		pomiar_start();

	}
}
