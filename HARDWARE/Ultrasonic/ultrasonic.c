/******************** (C) 1209 Lab **************************
 * 文件名  : UltrasonicWave.c
 * 描述    ：超声波测距模块，UltrasonicWave_Configuration（）函数
             初始化超声模块，UltrasonicWave_StartMeasure（）函数
			 启动测距，并将测得的数据通过串口1打印出来         
 * 实验平台：Mini STM32开发板  STM32F103ZET6
 * 硬件连接：------------------
 *          | PC2  - TRIG      |
 *          | PC3  - ECHO      |
 *           ------------------
 * 库版本  ：ST3.5.0
 *
 * 作者    ：2617 
*********************************************************************************/
#include "stm32f10x.h"
#include "ultrasonic.h"
#include "usart.h"
#include "timer.h"
#include "delay.h"
#include "sys.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_tim.h"
#include "led.h"
#include "LCD5110.h"

float Distance0=0;
float Distance1=0;    

/*
 * 函数名：UltrasonicWave_Configuration
 * 描述  ：超声波模块的初始化
 * 输入  ：无
 * 输出  ：无	
 */
void UltrasonicWave_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;	
	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;
	
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);	//关闭jtag
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);
    
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_0;					 //PB1接TRIG
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		     //设为推挽输出模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	         
  GPIO_Init(GPIOB, &GPIO_InitStructure);	                 //初始化外设GPIO 

  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2 | GPIO_Pin_4;				     //PB2接ECH0
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;		 //设为输入
  GPIO_Init(GPIOB,&GPIO_InitStructure);						 //初始化GPIOB
	
	//GPIOB2	  中断线以及中断初始化配置
// 	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource2);//PB2

//	EXTI_InitStructure.EXTI_Line=EXTI_Line2;
//	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
//	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
//	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//	EXTI_Init(&EXTI_InitStructure);		//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
//		
//			
//	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;			//使能按键所在的外部中断通道
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =1;	//抢占优先级2 
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;					//子优先级2 
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
//	NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
//	
//	//GPIOB4	  中断线以及中断初始化配置
// 	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource4);//PB4

//	EXTI_InitStructure.EXTI_Line=EXTI_Line4;
//	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
//	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
//	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//	EXTI_Init(&EXTI_InitStructure);		//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
//		
//			
//	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;			//使能按键所在的外部中断通道
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =2;	//抢占优先级2 
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;					//子优先级2 
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
//	NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
}


//void EXTI2_IRQHandler(void)
//{
////	delay_us(10);		                      //延时10us
//  if(EXTI_GetITStatus(EXTI_Line2) != RESET)
//	{		
//		ir2 = 1;
//		EXTI_ClearITPendingBit(EXTI_Line2);  												//清除EXTI7线路挂起位
//	}

//}

//void EXTI4_IRQHandler(void)
//{
////	delay_us(10);		                      //延时10us
//  if(EXTI_GetITStatus(EXTI_Line4) != RESET)
//	{		
//		ir3 = 1;
//		EXTI_ClearITPendingBit(EXTI_Line4);  												//清除EXTI7线路挂起位
//	}

//}
/*
 * 函数名：UltrasonicWave_StartMeasure
 * 描述  ：开始测距，发送一个>10us的脉冲，然后测量返回的高电平时间
 * 输入  ：无
 * 输出  ：无	
 */
//void UltrasonicWave_StartMeasure(void)
//{
//	TRIG_PIN=1; 		  					//送>10US的高电平RIG_PORT,TRIG_PIN
//  delay_us(25);		                      //延时20US
//	TRIG_PIN=0;
////	delay_ms(10);
////	if(ir2 == 1){
////		ir2 = 0;
//		while(GPIO_ReadInputDataBit(GPIOB, ECHO_PIN) == RESET){  //等待高电平以退出循环
//			Indicator_Light_TIM2 = 1;  //code debug
//		}
//		Working_Light = 0;   //code debug
//		TIM_SetCounter(TIM2,0);
//		TIM_Cmd(TIM2, ENABLE);                                     //开启时钟
//		while(GPIO_ReadInputDataBit(GPIOB,ECHO_PIN));	             //等待低电平(低电平才能退出循环)
//		TIM_Cmd(TIM2, DISABLE);			                               //定时器2失能
//		Distance0	=TIM_GetCounter(TIM2)*5*34/100.0;									 //计算距离&&UltrasonicWave_Distance<150		
////	}
//}

//void UltrasonicWave_StartMeasure2(void)
//{
//	TRIG_PIN_2=1; 		  					//送>10US的高电平RIG_PORT,TRIG_PIN
//  delay_us(25);		                      //延时20US
//	TRIG_PIN_2=0;
////	delay_ms(10);
////	if(ir3 == 1){
////		ir3 = 0;
//		while(GPIO_ReadInputDataBit(GPIOB, ECHO_PIN_2) == RESET){
//				Working_Light = 1;  //code debug
//		}
//		Working_Light = 0;   //code debug
//		TIM_SetCounter(TIM3,0);
//		TIM_Cmd(TIM3, ENABLE);           //开启时钟
//		while(GPIO_ReadInputDataBit(GPIOB,ECHO_PIN_2));	             //等待低电平(低电平才能退出循环)
//		TIM_Cmd(TIM3, DISABLE);			                               //定时器2失能
//		Distance1	= TIM_GetCounter(TIM3)*5*34/100.0;									 //计算距离&&UltrasonicWave_Distance<150		
////	}
//	
//}

/******************* (C) 1209 Lab *****END OF FILE************/

