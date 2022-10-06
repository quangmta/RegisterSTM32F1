#include "USART.h"
#include "Delay_F103.h"
void USART2_Config(void)
{
		/*** STEP FLOWWED ***********
	1. Enable the UART clock anh GPIO_CLOCK
	2. Configurate the UART PINS for Alternate Functions
	3. Enable the USART by writing the UE bit in USART_CR1  register to 1
	4. Program the M bit in USART_CR1 to define the word length.
	5. Select the sesired baud rate using the USART_SRR register
	6. Enable the Transmitter/Receiver by Setting the TE and RE bits in USRAT_CR1 Register.	
	*/
	//1.
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	//2.
	GPIOA->CRL = 0;
	GPIOA->CRL |= (3<<8) | (2<<10); // PA2-Tx: Alternate funtion output Push-pull and Output 50Hz
	GPIOA->CRL &= ~(3<<12); // PA3 input mode
	GPIOA->CRL |= (2<<14); //PA3-Rx: Input with pull-up/pull-down and input mode
	GPIOA->ODR |= 1<<3; // Pull up for PA3
	//3.
	USART2->CR1 = 0x00;
	USART2->CR1 |= USART_CR1_UE;
	//4.
	USART2->CR1 &= ~(1<<12);
	//5.
	//36*10^6/(16*115200)=19.53 =>DIV_Mantissa[15:11] = 19
	//0.53*16=8.5 => 8 => DIV_Fraction[3:0] = 8
	USART2->BRR |= (8<<0) | (19<<4);
	//6.
	USART2->CR1 |= USART_CR1_TE | USART_CR1_RE;
	USART2->CR1  |= USART_CR1_RXNEIE; //USART2 Receive Interrupt Enable
	//Enable interrupt from usart2(NVIC level)
	NVIC_EnableIRQ(USART2_IRQn);
}
void USART2_SendChar(uint8_t c)
{
		/*
	1. Write the data to send in the USART_DR register (this clears the TXE bit). Repeat this
		for each data to be transmitted in case of single buffer
	2. After writing the  last data in to the USART_DR register, wait iuntil TC=1. This indicates 
		that the transmission of the last frame if complete. This is required for instance when
		the USART is disabled or enters the Halt mode to avoid corrupting the last transmission.
	*/
	USART2->DR = c;
	while(!(USART2->SR & USART_SR_TC));
}
void USART2_SendString(char *string)
{
	while(*string)
	{
		USART2_SendChar(*string++);
		//Delay_ms(500);
	}
}
uint8_t USART2_GetChar(void)
{
	/* steps
	1. Wait for the RXNE bit to set. It indicates tha the data has been received and can be read.
	2. Read the data from USART_DR Register. This also clears the RXNE bit.
	*/
	uint8_t temp;
	while(!(USART2->SR & (USART_SR_RXNE))); //1<<5
	temp = USART2->DR;
	return temp;
}