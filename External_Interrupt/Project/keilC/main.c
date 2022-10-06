#include "stm32f10x.h"
//#include "stm32f10x_syscfg.h"

void GPIO_Configuration(void);
void Delay_ms(uint16_t time);
int counter=0;
int up=1;
int main(void)
{
	GPIO_Configuration();
	if (SysTick_Config(SystemCoreClock / 1000)) while (1);
	while(1)
	{
		GPIO_WriteBit(GPIOC,GPIO_Pin_13,(BitAction)(1^GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13)));
		Delay_ms(500);
		counter+=up;
		if((counter>=10) || (counter<=0)) up=-up;
	}
}
void GPIO_Configuration_PB12(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	// cap clock cho port B
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	//RCC_APB2PeriphClockCmd(RCC_Apb2periph_sys)
	// set configuration I/O is P13, speed, mode
//	GPIO_StructInit(&GPIO_InitStructure);
	//PB12
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB,&GPIO_InitStructure);	
	//PB13
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB,&GPIO_InitStructure);	
}

void Delay_ms(uint16_t time)
{
	//tang bien dem len 12000 lan
	uint32_t time_n=time*12000;
	while(time_n!=0){time_n--;};
}
static __IO uint32_t TimingDelay;
void Delay(uint32_t nTime)
{
	TimingDelay=nTime;
	while(TimingDelay!=0);
}
void SysTick_Handler(void)
{
	if(TimingDelay!=0x00)
		TimingDelay--;
}
#ifdef USE_FULL_ASSERT //d�ng de go loi
void assert_failed(uint8_t* file, uint32_t line) {
/* Infinite loop */
/* Use GDB to find out why we're here */ while (1);
}
#endif

