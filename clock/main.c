#include "stm32f10x.h"
#include "Delay_F103.h"

void GPIO_Config(void)
{
	/* Steps to follow
	1. Enable the GPIOC clokc
	2. Configure the Pin as output
	*/
	RCC->APB2ENR = (1<<4);// RCC_APB2ENR_IOPCEN
	GPIOC->CRH |= (1<<20); //PC13 output 10Mhz (MODE), CNF=00
	
}
int main(void)
{
	SystemInit();	
	GPIO_Config();
	TIM2_Config();
	
	while(1)
	{
		GPIOC->ODR |= (1<<13);
		//GPIOC->BSRR |= (1<<13);
		Delay_ms(500);
		GPIOC->ODR &= ~(1<<13);
		//GPIOC->BSRR |= (1<<13)<<16;
		Delay_ms(500);		
	}
}
