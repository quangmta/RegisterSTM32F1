#include "stm32f10x.h"

GPIO_InitTypeDef 					GPIO_InitStructure;

uint32_t Timingdelay;

void GPIO_Configuration(void);
void Delay_ms(uint16_t time);
void Delay_ms_sys(uint16_t time);

int main(void)
{
	SysTick_Config(SystemCoreClock/1000);			// cau hinh systick ngat moi 1ms
	GPIO_Configuration();
  while (1)
  {
		GPIO_WriteBit(GPIOB,GPIO_Pin_9,(BitAction)(1^GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9)));
		Delay_ms_sys(1000);
  }
}

void GPIO_Configuration(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}
void Delay_ms(uint16_t time)
{
uint32_t time_n=time*12000;
	while(time_n!=0){time_n--;}
}
void Delay_ms_sys(uint16_t time)
	{
	Timingdelay = time;						// gan bien dem bang tham so truyen vao
	while(Timingdelay!=0);				// ham cho doi bien dem bang 0.
	
	}
