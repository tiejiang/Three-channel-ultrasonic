#include "timer.h"
#include "sys.h"
#include "stm32f10x_tim.h"
#include "InfraredSafeDistance.h"
#include "led.h"
#include "TIM5_Obstacle_Detect.h"
#include "LCD5110.h"
#include "ultrasonic.h"
#include "delay.h"
u8 ir2 = 0;
u8 ir3 = 0;
//////////////////////////////////////////////////////////////////////////////////	 
//��ʱ�� ��������	  		  
//////////////////////////////////////////////////////////////////////////////////   	 

//ͨ�ö�ʱ���жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��2
void Timerx_Init2(u16 arr,u16 psc)
{
	/*TIM2 INIT*/
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE); //ʱ��ʹ��

	TIM_TimeBaseStructure.TIM_Period =arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
  //TIM_ClearFlag(TIM2, TIM_FLAG_Update);							    		/* �������жϱ�־ */
	TIM_ITConfig(  //ʹ�ܻ���ʧ��ָ����TIM�ж�
		TIM2, //TIM2
		TIM_IT_Update  |  //TIM �ж�Դ
		TIM_IT_Trigger,   //TIM �����ж�Դ 
		ENABLE  //ʹ��
		);
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM2�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

	//TIM_Cmd(TIM2, ENABLE);  //ʹ��TIMx����
	
}

void Timer3_Init(u16 arr, u16 psc){
		/*TIM3 INIT*/						 
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE); //ʱ��ʹ��

	TIM_TimeBaseStructure.TIM_Period =arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
  //TIM_ClearFlag(TIM2, TIM_FLAG_Update);							    		/* �������жϱ�־ */
	TIM_ITConfig(  //ʹ�ܻ���ʧ��ָ����TIM�ж�
		TIM3, //TIM3
		TIM_IT_Update  |  //TIM �ж�Դ
		TIM_IT_Trigger,   //TIM �����ж�Դ 
		ENABLE  //ʹ��
		);
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

	//TIM_Cmd(TIM3, ENABLE);  //ʹ��TIMx����
}

//void TIM2_IRQHandler(void)   //TIM2�ж�
//{
//	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
//		{
//			TIM_ClearITPendingBit(TIM2, TIM_IT_Update);  //���TIMx���жϴ�����λ:TIM �ж�Դ 
//			//LCD5110ShowNum(40,5,Distance0);
//			ir2 ++;
//		}
//}

//��ʱ��3�жϷ������
//void TIM3_IRQHandler(void)   //TIM3�ж�
//{
//	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //���TIM3�����жϷ������
//		{
//		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //���TIMx�����жϱ�־ 
//				ir3 ++;
//		}
//}
/*
 * ��������UltrasonicWave_StartMeasure
 * ����  ����ʼ��࣬����һ��>10us�����壬Ȼ��������صĸߵ�ƽʱ��
 * ����  ����
 * ���  ����	
 */
void UltrasonicWave_StartMeasure(void)
{
	TRIG_PIN=1; 		  					//��>10US�ĸߵ�ƽ�TRIG_PORT,TRIG_PIN
  delay_us(25);		                      //��ʱ20US
	TRIG_PIN=0;
//	delay_ms(10);
//	if(ir2 == 1){
//		ir2 = 0;
		while(GPIO_ReadInputDataBit(GPIOB, ECHO_PIN) == RESET){  //�ȴ��ߵ�ƽ���˳�ѭ��
			Indicator_Light_TIM2 = 1;  //code debug
		}
//		Working_Light = 0;   //code debug
		TIM_SetCounter(TIM2,0);
		TIM_Cmd(TIM2, ENABLE);                                     //����ʱ��
		while(GPIO_ReadInputDataBit(GPIOB,ECHO_PIN));	             //�ȴ��͵�ƽ(�͵�ƽ�����˳�ѭ��)
		TIM_Cmd(TIM2, DISABLE);			                               //��ʱ��2ʧ��
		Distance0	=(TIM_GetCounter(TIM2) + ir2*1000)/58.0;									 //�������&&UltrasonicWave_Distance<150		
		ir2 = 0;
//	}
}

void UltrasonicWave_StartMeasure2(void)
{
	TRIG_PIN_2=1; 		  					//��>10US�ĸߵ�ƽ�TRIG_PORT,TRIG_PIN
  delay_us(25);		                      //��ʱ20US
	TRIG_PIN_2=0;
//	delay_ms(10);
//	if(ir3 == 1){
//		ir3 = 0;
		while(GPIO_ReadInputDataBit(GPIOB, ECHO_PIN_2) == RESET){
//				Working_Light = 1;  //code debug
		}
//		Working_Light = 0;   //code debug
		TIM_SetCounter(TIM3,0);
		TIM_Cmd(TIM3, ENABLE);           //����ʱ��
		while(GPIO_ReadInputDataBit(GPIOB,ECHO_PIN_2));	             //�ȴ��͵�ƽ(�͵�ƽ�����˳�ѭ��)
		TIM_Cmd(TIM3, DISABLE);			                               //��ʱ��2ʧ��
		Distance1	= (TIM_GetCounter(TIM3) + ir2*1000)/58.0;									 //�������&&UltrasonicWave_Distance<150		
		ir3 = 0;
//	}
	
}


