#include "stm32f10x.h"

GPIO_InitTypeDef 					GPIO_InitStructure;

uint32_t Timingdelay;

void GPIO_Configuration(void);
void Dms_sys_noint(uint16_t time);
void SysTick_Configuration(void);

int main(void)
{
	SysTick_Configuration();
	GPIO_Configuration();
  while (1)
  {
		GPIO_WriteBit(GPIOB,GPIO_Pin_9,(BitAction)(1^GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9)));
		Dms_sys_noint(1000);
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
void Dms_sys_noint(uint16_t time)
	{
		Timingdelay = time;
		while(Timingdelay!=0)
			{
				while( (SysTick->CTRL&0x10000)==0x10000)
					{
						Timingdelay--;
					}
			}
	}
void SysTick_Configuration(void)
	{
		SysTick->CTRL = 0x00000005;
		SysTick->VAL =0;
		SysTick->LOAD = 72000-1;	

	}
