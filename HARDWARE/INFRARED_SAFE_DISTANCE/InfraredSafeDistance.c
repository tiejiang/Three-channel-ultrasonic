#include "InfraredSafeDistance.h"
#include "stm32f10x.h"
#include "usart.h"
#include "led.h"
#include "delay.h"

/*************************
����С�����������ϰ�ȫ����˿����Ŷ��� PA5(���)PA6���Ҳࣩ

**********************************/
void InfraredSafeDistance_Init(void){
		/*GPIO�˿����ýṹ���������*/
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//��GPIOAʱ��	
	GPIO_InitStructure.GPIO_Pin	= GPIO_Pin_4|GPIO_Pin_5;//��������˿�����---PA5.6
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //����Ϊ��������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}
//���Ҳ������ϰ�ȫ���봦��
void Safe_DistanceSensor(){		
		if(!LeftSafeDistanceSensor){
			printf("%d, %d\n",1,000);
//			Working_Light=!Working_Light;//��˸LED,��ʾϵͳ��������.
			delay_ms(1000);
		}else if(!RightSafeDistanceSensor){
			printf("%d, %d\n",3,000);
//			Working_Light=!Working_Light;//��˸LED,��ʾϵͳ��������.
			delay_ms(1000);
		}
}


