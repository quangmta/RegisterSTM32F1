#include "stm32f10x.h"

void USART2_Config(void);
void USART2_SendChar(uint8_t c);
void USART2_SendString(char *string);
uint8_t USART2_GetChar(void);
void DMA_Config(uint32_t srcAdd, uint32_t destAdd, uint8_t size);
void DMA_Init(void);