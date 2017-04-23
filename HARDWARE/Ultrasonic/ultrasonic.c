/******************** (C) 1209 Lab **************************
 * �ļ���  : UltrasonicWave.c
 * ����    �����������ģ�飬UltrasonicWave_Configuration��������
             ��ʼ������ģ�飬UltrasonicWave_StartMeasure��������
			 ������࣬������õ�����ͨ������1��ӡ����         
 * ʵ��ƽ̨��Mini STM32������  STM32F103ZET6
 * Ӳ�����ӣ�------------------
 *          | PC2  - TRIG      |
 *          | PC3  - ECHO      |
 *           ------------------
 * ��汾  ��ST3.5.0
 *
 * ����    ��2617 
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
 * ��������UltrasonicWave_Configuration
 * ����  ��������ģ��ĳ�ʼ��
 * ����  ����
 * ���  ����	
 */
void UltrasonicWave_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;	
	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;
	
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);	//�ر�jtag
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);
    
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_0;					 //PB1��TRIG
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		     //��Ϊ�������ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	         
  GPIO_Init(GPIOB, &GPIO_InitStructure);	                 //��ʼ������GPIO 

  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2 | GPIO_Pin_4;				     //PB2��ECH0
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;		 //��Ϊ����
  GPIO_Init(GPIOB,&GPIO_InitStructure);						 //��ʼ��GPIOB
	
	//GPIOB2	  �ж����Լ��жϳ�ʼ������
// 	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource2);//PB2

//	EXTI_InitStructure.EXTI_Line=EXTI_Line2;
//	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
//	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
//	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//	EXTI_Init(&EXTI_InitStructure);		//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
//		
//			
//	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;			//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =1;	//��ռ���ȼ�2 
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;					//�����ȼ�2 
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
//	NVIC_Init(&NVIC_InitStructure);  	  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
//	
//	//GPIOB4	  �ж����Լ��жϳ�ʼ������
// 	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource4);//PB4

//	EXTI_InitStructure.EXTI_Line=EXTI_Line4;
//	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
//	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
//	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//	EXTI_Init(&EXTI_InitStructure);		//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
//		
//			
//	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;			//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =2;	//��ռ���ȼ�2 
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;					//�����ȼ�2 
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
//	NVIC_Init(&NVIC_InitStructure);  	  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
}


//void EXTI2_IRQHandler(void)
//{
////	delay_us(10);		                      //��ʱ10us
//  if(EXTI_GetITStatus(EXTI_Line2) != RESET)
//	{		
//		ir2 = 1;
//		EXTI_ClearITPendingBit(EXTI_Line2);  												//���EXTI7��·����λ
//	}

//}

//void EXTI4_IRQHandler(void)
//{
////	delay_us(10);		                      //��ʱ10us
//  if(EXTI_GetITStatus(EXTI_Line4) != RESET)
//	{		
//		ir3 = 1;
//		EXTI_ClearITPendingBit(EXTI_Line4);  												//���EXTI7��·����λ
//	}

//}
/*
 * ��������UltrasonicWave_StartMeasure
 * ����  ����ʼ��࣬����һ��>10us�����壬Ȼ��������صĸߵ�ƽʱ��
 * ����  ����
 * ���  ����	
 */
//void UltrasonicWave_StartMeasure(void)
//{
//	TRIG_PIN=1; 		  					//��>10US�ĸߵ�ƽ�TRIG_PORT,TRIG_PIN
//  delay_us(25);		                      //��ʱ20US
//	TRIG_PIN=0;
////	delay_ms(10);
////	if(ir2 == 1){
////		ir2 = 0;
//		while(GPIO_ReadInputDataBit(GPIOB, ECHO_PIN) == RESET){  //�ȴ��ߵ�ƽ���˳�ѭ��
//			Indicator_Light_TIM2 = 1;  //code debug
//		}
//		Working_Light = 0;   //code debug
//		TIM_SetCounter(TIM2,0);
//		TIM_Cmd(TIM2, ENABLE);                                     //����ʱ��
//		while(GPIO_ReadInputDataBit(GPIOB,ECHO_PIN));	             //�ȴ��͵�ƽ(�͵�ƽ�����˳�ѭ��)
//		TIM_Cmd(TIM2, DISABLE);			                               //��ʱ��2ʧ��
//		Distance0	=TIM_GetCounter(TIM2)*5*34/100.0;									 //�������&&UltrasonicWave_Distance<150		
////	}
//}

//void UltrasonicWave_StartMeasure2(void)
//{
//	TRIG_PIN_2=1; 		  					//��>10US�ĸߵ�ƽ�TRIG_PORT,TRIG_PIN
//  delay_us(25);		                      //��ʱ20US
//	TRIG_PIN_2=0;
////	delay_ms(10);
////	if(ir3 == 1){
////		ir3 = 0;
//		while(GPIO_ReadInputDataBit(GPIOB, ECHO_PIN_2) == RESET){
//				Working_Light = 1;  //code debug
//		}
//		Working_Light = 0;   //code debug
//		TIM_SetCounter(TIM3,0);
//		TIM_Cmd(TIM3, ENABLE);           //����ʱ��
//		while(GPIO_ReadInputDataBit(GPIOB,ECHO_PIN_2));	             //�ȴ��͵�ƽ(�͵�ƽ�����˳�ѭ��)
//		TIM_Cmd(TIM3, DISABLE);			                               //��ʱ��2ʧ��
//		Distance1	= TIM_GetCounter(TIM3)*5*34/100.0;									 //�������&&UltrasonicWave_Distance<150		
////	}
//	
//}

/******************* (C) 1209 Lab *****END OF FILE************/

