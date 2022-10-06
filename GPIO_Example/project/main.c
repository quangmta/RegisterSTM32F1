#include "stm32f10x.h"
GPIO_InitTypeDef 					GPIO_InitStructure;
void GPIO_Configuration(void);
void Delay_ms(uint16_t time);

int main(void)
{
	// goi chuong trinh con da khai bao
	GPIO_Configuration();                                 
  while (1)
  {
		// dung ham xor  dao trang thai led
		GPIO_WriteBit(GPIOB,GPIO_Pin_9,(BitAction)(1^GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9)));	
		// goi ham delay tuong doi
		Delay_ms(1000);																																					
  }
}

void GPIO_Configuration(void)
{
	// cap clock cho Port B, Port C
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); 
	// cau hinh chan I/O su dung la PC13,toc do input,mode input la Input pull-up
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 ;						
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;			
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;			
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	// cau hinh chan I/O su dung la PB9,toc do output,mode output la Output push-pull 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 ;						
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;			
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}
// ham delay tuong doi dung vong lap while
void Delay_ms(uint16_t time)														
{
	// tang bien dem len 12000 lan
	uint32_t time_n=time*12000;		
	// cho den khi biem time_n giam =0 thi thoat	
	while(time_n!=0){time_n--;}													

}
