#include "led.h"
#include "stm32f10x.h"
#include "delay.h"

void LED_Init(void){
		/*GPIO�˿����ýṹ���������*/
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//��GPIOʱ��
	//��LED��4�����ŷֱ�����Ϊ�������
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

