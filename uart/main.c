#include "stm32f10x.h"
#include "Delay_F103.h"
#include "USART.h"
#include "stdio.h"

uint8_t rx_index = 0;
char rx_buffer[50];
//interrupt receive function
void USART2_IRQHandler()
{
	if(USART2->SR &USART_SR_RXNE)
	{
		uint8_t rx_data = USART2_GetChar();
		if(rx_index==0)
		{
			for(int i=0;i<50;i++)
			{
				rx_buffer[i]='\0';
			}
		}
		if(rx_data!='\n' && rx_data!='\r')
		{
			rx_buffer[rx_index++]=rx_data;
		}
		else
		{
			USART2_SendString(rx_buffer);
			rx_index=0;
		}		
		//sprintf(str,"%.3f\n",number);
		USART2_SendChar(rx_data);
		//USART2_SendChar('G');
		
		if(!(GPIOC->IDR & (1<<13))) GPIOC->ODR |= (1<<13);
		else GPIOC->ODR &= ~(1<<13);
	}
}
void GPIO_Config(void)
{
	RCC->APB2ENR = RCC_APB2ENR_IOPCEN;
	GPIOC->CRH |= (1<<20); //10Hz Mode vs 0<<22: push-pull for PC13
}
int main(void)
{
	SystemInit();
	TIM2_Config();
	USART2_Config();
	GPIO_Config();
	 while(1)
	 {

//		 Delay_ms(1000);
		 
	 }
	
}