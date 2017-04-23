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
void SendBackData(float distance1, float distance2, float distance3, char left, char right);//发送实时车距

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
		LCD5110ClearPart(60,4,80,4);			//清屏，为显示做准备
		//显示距离数据
		LCD5110ShowNum(65,3,value);
		LCD5110ShowNum(65,4,value2);
		LCD5110ShowNum(65,5,value3);
//		SendBackData(value, value2, value3, 'H', 'N');
		if(LeftSafeDistanceSensor == 0){  //左侧达到极限距离，红外传感器响应
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
	delay_init();	    	 //延时函数初始化
	NVIC_Configuration(); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(9600);  //串口初始化 初始化下载端口等
//	LED_Init();	//系统工作模块指示灯 引脚初始化		
//	UltrasonicWave_Configuration();               //对超声波模块初始化
	InfraredSafeDistance_Init();
	LCD5110_GPIOInit();
	Show_Init();	//Nokia5110初始显示内容	
	Ultrasonic_TIM4_Init(0XFFFF,72-1);
	Ultrasonic_TIM3_Init(0XFFFF,72-1);
	Ultrasonic_TIM2_Init(0XFFFF,72-1);
}
//Nokia5110显示屏初始化
void Show_Init(void)
{
	LCD5110Clear();
	LCD5110WriteEnStr(0, 1, (u8 *)TITLE);
	LCD5110WriteEnStr(0, 3, (u8 *)Right_Dis);//"Right_DIS"	
	LCD5110WriteEnStr(0, 4,(u8 *)Left_Dis);
	LCD5110WriteEnStr(0, 5,(u8 *)Back_Dis);
}
//向上位机发送数据
void SendBackData(float distance1, float distance2, float distance3, char left, char right){
	printf("%c, %d, %d, %d, %c, %c\n", 'D',(int)distance1,(int)distance2,(int)distance3, left, right);
//	Working_Light=!Working_Light;//闪烁LED,提示系统正在运行.

}

