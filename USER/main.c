#include "stm32f10x.h"
#include "led.h"
#include "sys.h"
#include "timer.h"
#include "TIM5_Obstacle_Detect.h"
#include "delay.h"
#include <stdio.h>
#include <math.h>
#include "LCD5110.h"
#include "ultrasonic.h"
#include "usart.h"
#include "InfraredSafeDistance.h"
#include "TIMER_INIT.h"

char TITLE[18] = "Car Dis Alarm";
char TIM2_Counter[8] = "T_Count:";
char Right_Dis[11] = "RIGHT_DIS:";
char Left_Dis[10] = "LEFT_DIS:";
char Back_Dis[10] = "BACK_DIS:";
double angle;
int start_Node = 0;
u16 times=0;
unsigned char count = 0;

void System_Init(void);
void Show_Init(void);
void SendBackData(float distance1, float distance2, float distance3, char left, char right);//����ʵʱ����

int main(void){	
	SystemInit();
	System_Init();
	
//	Working_Light = 1;
	delay_ms(300);
//	Working_Light = 0;
	while(1){	
		Ultrasonic_Value();
//		Ultrasonic_Value2();
		Ultrasonic_Value2_from_TIM2_CH1();
		Ultrasonic_Value3_from_TIM3_CH1();
//		switch (count){
//			case 0:
//					Ultrasonic_Value();
//					count = 1;
//			break;
//			case 1:
////					Ultrasonic_Value2();
//						Ultrasonic_Value2_from_TIM2_CH1();
//					count = 2;
//			break;
//			case 2:
////				Ultrasonic_Value3();
//					Ultrasonic_Value3_from_TIM3_CH1();
//				count = 0;
//			break;
//		}			
		LCD5110ClearPart(60,4,80,4);			//������Ϊ��ʾ��׼��
		//��ʾ��������
		LCD5110ShowNum(65,3,value);
		LCD5110ShowNum(65,4,value2);
		LCD5110ShowNum(65,5,value3);
//		SendBackData(value, value2, value3, 'H', 'N');
		if(LeftSafeDistanceSensor == 0){  //���ﵽ���޾��룬���⴫������Ӧ
			SendBackData(value, value2, value3, 'H', 'N');
		}else if(RightSafeDistanceSensor == 0){
			SendBackData(value, value2, value3, 'N', 'H');
		}else{
			SendBackData(value, value2, value3, 'N', 'N');
		}
		delay_ms(1000);	
	}	
}

void System_Init(void)
{
	delay_init();	    	 //��ʱ������ʼ��
	NVIC_Configuration(); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(9600);  //���ڳ�ʼ�� ��ʼ�����ض˿ڵ�
//	LED_Init();	//ϵͳ����ģ��ָʾ�� ���ų�ʼ��		
//	UltrasonicWave_Configuration();               //�Գ�����ģ���ʼ��
	InfraredSafeDistance_Init();
	LCD5110_GPIOInit();
	Show_Init();	//Nokia5110��ʼ��ʾ����	
	Ultrasonic_TIM4_Init(0XFFFF,72-1);
	Ultrasonic_TIM3_Init(0XFFFF,72-1);
	Ultrasonic_TIM2_Init(0XFFFF,72-1);
}
//Nokia5110��ʾ����ʼ��
void Show_Init(void)
{
	LCD5110Clear();
	LCD5110WriteEnStr(0, 1, (u8 *)TITLE);
	LCD5110WriteEnStr(0, 3, (u8 *)Right_Dis);//"Right_DIS"	
	LCD5110WriteEnStr(0, 4,(u8 *)Left_Dis);
	LCD5110WriteEnStr(0, 5,(u8 *)Back_Dis);
}
//����λ����������
void SendBackData(float distance1, float distance2, float distance3, char left, char right){
	printf("%c, %d, %d, %d, %c, %c\n", 'D',(int)distance1,(int)distance2,(int)distance3, left, right);
//	Working_Light=!Working_Light;//��˸LED,��ʾϵͳ��������.

}

