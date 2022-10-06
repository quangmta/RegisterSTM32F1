#include "stm32f10x.h"
void GPIO_Config(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	GPIOA->CRL &= ~(0xf);
	GPIOA->CRL |= (1<<4); //moder + cnf
	GPIOA->ODR |= (1<<1);
	
}
void Interrupt_Config(void)
{
	/*** STEP ****
	1. Enable AFIO bit in RCC register
	2. Configure the EXTI configuration Register in the AFIO (IMR)
	3. Enable the EXTI using Interrupt Mask Regiter (IMR)
	4. Configure the Rising Edge/Fallin Edge Trigger
	5. Set the Interrupt Priority
	6. Enbale the interrupt
	*/
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
	
	AFIO->EXTICR[0] &= ~(0xf<<0);//PA0
	
}
int main()
{
	while(1)
	{

	}
}