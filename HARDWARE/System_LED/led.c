#include "led.h"
#include "stm32f10x.h"
#include "delay.h"

void LED_Init(void){
		/*GPIO端口配置结构体变量定义*/
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//打开GPIO时钟
	//将LED的4个引脚分别设置为推挽输出
	GPIO_InitStructure.GPIO_Pin	= GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOB, GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13);
}

//test code 
void LED_TEST(void){

		GPIO_SetBits(GPIOB, GPIO_Pin_9);
		delay_ms(1000);
		GPIO_ResetBits(GPIOB, GPIO_Pin_9);
		delay_ms(1000);
}


