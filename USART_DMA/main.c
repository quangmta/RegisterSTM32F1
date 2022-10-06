#include "stm32f10x.h"
#include "USART.h"
#include "Delay_F103.h"

#define RXSIZE 20
uint8_t RxBuf[20];
uint8_t MainBuf[50];
uint8_t indx=0;

void DMA1_Channel6_IRQHandler(void)
{
	if((DMA1->ISR)&(DMA_ISR_HTIF6))//If the Half Transfer Complete Interrupt is set
	{
		memcpy(&MainBuf[indx], &RxBuf[0], RXSIZE/2);
		DMA1->IFCR |= DMA_IFCR_CHTIF6;
		indx += RXSIZE/2;
		if(indx>49) indx=0;		
	}
	if((DMA1->ISR)&(DMA_ISR_HTIF6))//If the Transfer Coplete Interrupt is set
	{
		memcpy(&MainBuf[indx], &RxBuf[RXSIZE/2], RXSIZE/2);
		DMA1->IFCR |= DMA_IFCR_CTCIF6;
		indx += RXSIZE/2;
		if(indx>49) indx=0;		
	}
	
}
int main(void)
{
	SystemInit();
	USART2_Config();
	DMA_Init();
	
	NVIC_SetPriority(DMA1_Channel6_IRQn,0);
	NVIC_EnableIRQ(DMA1_Channel6_IRQn);
	
	DMA_Config((uint32_t) &USART2->DR, (uint32_t)RxBuf,RXSIZE);
	
	while(1)
	{}
}