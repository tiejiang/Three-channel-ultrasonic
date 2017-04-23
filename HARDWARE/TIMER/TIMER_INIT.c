#include "timer.h"
#include "sys.h"
#include "stm32f10x_tim.h"
#include "InfraredSafeDistance.h"
#include "led.h"
#include "TIM5_Obstacle_Detect.h"
#include "LCD5110.h"
#include "ultrasonic.h"
#include "delay.h"
// TIM4
u8  TIM4CH1_CAPTURE_STA=0;	//���벶��״̬		    				
u16	TIM4CH1_CAPTURE_VAL;	//���벶��ֵ
u8  TIM4CH2_CAPTURE_STA=0;	//���벶��״̬		    				
u16	TIM4CH2_CAPTURE_VAL;	//���벶��ֵ
u8  TIM4CH3_CAPTURE_STA=0;	//���벶��״̬		    				
u16	TIM4CH3_CAPTURE_VAL;	//���벶��ֵ
// TIM3
u8  TIM3CH1_CAPTURE_STA=0;	//���벶��״̬		    				
u16	TIM3CH1_CAPTURE_VAL;	//���벶��ֵ
// TIM2
u8  TIM2CH1_CAPTURE_STA=0;	//���벶��״̬		    				
u16	TIM2CH1_CAPTURE_VAL;	//���벶��ֵ
float value=0;
float value2=0;
float value3=0;

void Ultrasonic_TIM4_Init(u16 arr, u16 psc)
{
        TIM_ICInitTypeDef TIM_ICInitStruct;
        GPIO_InitTypeDef GPIO_InitStruct;
        NVIC_InitTypeDef NVIC_InitStruct;
        TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
        //
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
				RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
        
        TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
        TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
        TIM_TimeBaseInitStruct.TIM_Period = arr;
        TIM_TimeBaseInitStruct.TIM_Prescaler = psc;
        TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStruct);
        //TIM4 CH1 INIT
        TIM_ICInitStruct.TIM_Channel = TIM_Channel_1;
        TIM_ICInitStruct.TIM_ICFilter = 0x00;
        TIM_ICInitStruct.TIM_ICPolarity = TIM_ICPolarity_Rising;  //��ʼ״̬����Ϊ�����ز���
        TIM_ICInitStruct.TIM_ICPrescaler = TIM_ICPSC_DIV1;
        TIM_ICInitStruct.TIM_ICSelection = TIM_ICSelection_DirectTI;
        TIM_ICInit(TIM4, &TIM_ICInitStruct);
				//TIM4 CH2 INIT
//	      TIM_ICInitStruct.TIM_Channel = TIM_Channel_2;
//        TIM_ICInitStruct.TIM_ICFilter = 0x00;
//        TIM_ICInitStruct.TIM_ICPolarity = TIM_ICPolarity_Rising;
//        TIM_ICInitStruct.TIM_ICPrescaler = TIM_ICPSC_DIV1;
//        TIM_ICInitStruct.TIM_ICSelection = TIM_ICSelection_DirectTI;
//        TIM_ICInit(TIM4, &TIM_ICInitStruct);
//				//TIM4 CH3 INIT
//	      TIM_ICInitStruct.TIM_Channel = TIM_Channel_3;
//        TIM_ICInitStruct.TIM_ICFilter = 0x00;
//        TIM_ICInitStruct.TIM_ICPolarity = TIM_ICPolarity_Rising;
//        TIM_ICInitStruct.TIM_ICPrescaler = TIM_ICPSC_DIV1;
//        TIM_ICInitStruct.TIM_ICSelection = TIM_ICSelection_DirectTI;
//        TIM_ICInit(TIM4, &TIM_ICInitStruct);
        //CH1---PB6 CH2---PB7  CH3---PB8
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;
        GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6; 
//        GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOB, &GPIO_InitStruct);
				GPIO_ResetBits(GPIOB,GPIO_Pin_6);
        //TRIG PIN INIT  PB0 PB1 PB2
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;
        GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOB, &GPIO_InitStruct);
        GPIO_ResetBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2);
        //
        NVIC_InitStruct.NVIC_IRQChannel = TIM4_IRQn;
        NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
        NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
        NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
        NVIC_Init(&NVIC_InitStruct);
        //
        TIM_ITConfig(TIM4, TIM_IT_Update | TIM_IT_CC1, ENABLE);
//				TIM_ITConfig(TIM4, TIM_IT_Update | TIM_IT_CC2, ENABLE);
//				TIM_ITConfig(TIM4, TIM_IT_Update | TIM_IT_CC3, ENABLE);
        TIM_Cmd(TIM4, ENABLE);
//				Working_Light = 1;  //code debug
}
//TIM3 INIT
void Ultrasonic_TIM3_Init(u16 arr, u16 psc)
{
        TIM_ICInitTypeDef TIM_ICInitStruct;
        GPIO_InitTypeDef GPIO_InitStruct;
        NVIC_InitTypeDef NVIC_InitStruct;
        TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
        //
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
				RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
        
        TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
        TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
        TIM_TimeBaseInitStruct.TIM_Period = arr;
        TIM_TimeBaseInitStruct.TIM_Prescaler = psc;
        TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);
        //TIM3 CH1 INIT
        TIM_ICInitStruct.TIM_Channel = TIM_Channel_1;
        TIM_ICInitStruct.TIM_ICFilter = 0x00;
        TIM_ICInitStruct.TIM_ICPolarity = TIM_ICPolarity_Rising;  //��ʼ״̬����Ϊ�����ز���
        TIM_ICInitStruct.TIM_ICPrescaler = TIM_ICPSC_DIV1;
        TIM_ICInitStruct.TIM_ICSelection = TIM_ICSelection_DirectTI;
        TIM_ICInit(TIM3, &TIM_ICInitStruct);
        //CH1---PA6
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;
        GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
//        GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOA, &GPIO_InitStruct);
				GPIO_ResetBits(GPIOA,GPIO_Pin_6);
        
        //
        NVIC_InitStruct.NVIC_IRQChannel = TIM3_IRQn;
        NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
        NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
        NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
        NVIC_Init(&NVIC_InitStruct);
        //
        TIM_ITConfig(TIM3, TIM_IT_Update | TIM_IT_CC1, ENABLE);
        TIM_Cmd(TIM3, ENABLE);
//				Working_Light = 1;  //code debug
}
//TIM2 INIT 
void Ultrasonic_TIM2_Init(u16 arr, u16 psc)
{
        TIM_ICInitTypeDef TIM_ICInitStruct;
        GPIO_InitTypeDef GPIO_InitStruct;
        NVIC_InitTypeDef NVIC_InitStruct;
        TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	
        //
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
				RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
        
        TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
        TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
        TIM_TimeBaseInitStruct.TIM_Period = arr;
        TIM_TimeBaseInitStruct.TIM_Prescaler = psc;
        TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
        //TIM2 CH1 INIT
        TIM_ICInitStruct.TIM_Channel = TIM_Channel_1;
        TIM_ICInitStruct.TIM_ICFilter = 0x00;
        TIM_ICInitStruct.TIM_ICPolarity = TIM_ICPolarity_Rising;  //��ʼ״̬����Ϊ�����ز���
        TIM_ICInitStruct.TIM_ICPrescaler = TIM_ICPSC_DIV1;
        TIM_ICInitStruct.TIM_ICSelection = TIM_ICSelection_DirectTI;
        TIM_ICInit(TIM2, &TIM_ICInitStruct);
        //CH1---PA0
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;
        GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
//        GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOA, &GPIO_InitStruct);
				GPIO_ResetBits(GPIOA,GPIO_Pin_0);	        
        //
        NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn;
        NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
        NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
        NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
        NVIC_Init(&NVIC_InitStruct);
        //
        TIM_ITConfig(TIM2, TIM_IT_Update | TIM_IT_CC1, ENABLE);
        TIM_Cmd(TIM2, ENABLE);
//				Working_Light = 1;  //code debug
}

void TIM4_IRQHandler(void)
{
				//CH1
        if((TIM4CH1_CAPTURE_STA & 0x80) == 0)
        {
                if(TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
                {											
                        if(TIM4CH1_CAPTURE_STA & 0x40)
                        {
                                if((TIM4CH1_CAPTURE_STA & 0x3F) == 0x3F)
                                {
                                        TIM4CH1_CAPTURE_STA |= 0x80;
                                        TIM4CH1_CAPTURE_VAL = 0xFFFF;
//																				Working_Light = 0;  //code debug
                                }
                                else
                                {
                                        TIM4CH1_CAPTURE_STA++;
//																				Indicator_Light_TIM2 = 0;   //code debug
                                }
                        }
                }
                if(TIM_GetITStatus(TIM4, TIM_IT_CC1) != RESET)
                {
                        if(TIM4CH1_CAPTURE_STA & 0x40)
                        {
                                TIM4CH1_CAPTURE_STA |= 0x80;
                                TIM4CH1_CAPTURE_VAL = TIM_GetCapture1(TIM4);
                                TIM_OC1PolarityConfig(TIM4, TIM_ICPolarity_Rising);
//																Indicator_Light_TIM2 = 1;   //code debug
                        }
                        else
                        {
                                TIM4CH1_CAPTURE_STA = 0;
                                TIM4CH1_CAPTURE_VAL = 0;
																TIM_SetCounter(TIM4, 0);
                                TIM4CH1_CAPTURE_STA |= 0x40;                                
                                TIM_OC1PolarityConfig(TIM4, TIM_ICPolarity_Falling);
//																Working_Light = 1;  //code debug
                        }
												
                }
        }
				//CH2 
//				if((TIM4CH2_CAPTURE_STA & 0x80) == 0)//��δ�ɹ�����
//        {
//                if(TIM_GetITStatus(TIM4, TIM_IT_Update)  != RESET)  //�����ж�Դ �жϷ�������ʱ���жϷ�����
//                {								
//												//CH2
//												if(TIM4CH2_CAPTURE_STA & 0x40)  //�Ѿ����񵽸ߵ�ƽ��
//                        {
//                                if((TIM4CH2_CAPTURE_STA & 0x3F) == 0x3F)   //�ߵ�ƽ״̬
//                                {
//                                        TIM4CH2_CAPTURE_STA |= 0x80; //��ǳɹ�������һ��
//                                        TIM4CH2_CAPTURE_VAL = 0xFFFF;
////																				Working_Light = 0;  //code debug
//                                }
//                                else
//                                {
//                                        TIM4CH2_CAPTURE_STA++;
////																				Indicator_Light_TIM2 = 0;   //code debug
//                                }
//                        }
//                }
//								
//								if(TIM_GetITStatus(TIM4, TIM_IT_CC2) != RESET){  //ͨ��2���������¼�
//                        if(TIM4CH2_CAPTURE_STA & 0x40)  // �����½���
//                        {
//                                TIM4CH2_CAPTURE_STA |= 0x80;	//��ǳɹ�����һ��������
//                                TIM4CH2_CAPTURE_VAL = TIM_GetCapture2(TIM4);
//                                TIM_OC2PolarityConfig(TIM4, TIM_ICPolarity_Rising);//����Ϊ�����ز���
////																Indicator_Light_TIM2 = 1;   //code debug
//                        }
//                        else
//                        {
//                                TIM4CH2_CAPTURE_STA = 0;  //���
//                                TIM4CH2_CAPTURE_VAL = 0;
////																TIM_SetCounter(TIM4, 0);
//                                TIM4CH2_CAPTURE_STA |= 0x40;  //��ǲ�����������                                
//                                TIM_OC2PolarityConfig(TIM4, TIM_ICPolarity_Falling); //����Ϊ�½��ز���
////																Working_Light = 1;  //code debug
//                        }
//								}
//        }
				//CH3
//				if((TIM4CH3_CAPTURE_STA & 0x80) == 0)
//        {
//                if(TIM_GetITStatus(TIM4, TIM_IT_Update) == 1)
//                {
//                        if(TIM4CH3_CAPTURE_STA & 0x40)
//                        {
//                                if((TIM4CH3_CAPTURE_STA & 0x3F) == 0x3F)
//                                {
//                                        TIM4CH3_CAPTURE_STA |= 0x80;
//                                        TIM4CH3_CAPTURE_VAL = 0xFFFF;
////																				Working_Light = 0;  //code debug
//                                }
//                                else
//                                {
//                                        TIM4CH3_CAPTURE_STA++;
////																				Indicator_Light_TIM2 = 0;   //code debug
//                                }
//                        }
//                }
//                if(TIM_GetITStatus(TIM4, TIM_IT_CC3) == 1)
//                {
//                        if(TIM4CH3_CAPTURE_STA & 0x40)
//                        {
//                                TIM4CH3_CAPTURE_STA |= 0x80;
//                                TIM4CH3_CAPTURE_VAL = TIM_GetCapture3(TIM4);
//                                TIM_OC3PolarityConfig(TIM4, TIM_ICPolarity_Rising);
////																Indicator_Light_TIM2 = 1;   //code debug
//                        }
//                        else
//                        {
//                                TIM4CH3_CAPTURE_STA = 0;
//                                TIM4CH3_CAPTURE_VAL = 0;
//                                TIM4CH3_CAPTURE_STA |= 0x40;
//                                TIM_SetCounter(TIM4, 0);
//                                TIM_OC3PolarityConfig(TIM4, TIM_ICPolarity_Falling);
////																Working_Light = 1;  //code debug
//                        }
//												
//                }
//        }
//				TIM_SetCounter(TIM4, 0);
        TIM_ClearITPendingBit(TIM4, TIM_IT_CC1 | TIM_IT_Update ); //����ж�
}
//TIM3 IQ HANDLER
void TIM3_IRQHandler(void)
{
				//CH1
        if((TIM3CH1_CAPTURE_STA & 0x80) == 0)
        {
                if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
                {											
                        if(TIM3CH1_CAPTURE_STA & 0x40)
                        {
                                if((TIM3CH1_CAPTURE_STA & 0x3F) == 0x3F)
                                {
                                        TIM3CH1_CAPTURE_STA |= 0x80;
                                        TIM3CH1_CAPTURE_VAL = 0xFFFF;
//																				Working_Light = 0;  //code debug
                                }
                                else
                                {
                                        TIM3CH1_CAPTURE_STA++;
//																				Indicator_Light_TIM2 = 0;   //code debug
                                }
                        }
                }
                if(TIM_GetITStatus(TIM3, TIM_IT_CC1) != RESET)
                {
                        if(TIM3CH1_CAPTURE_STA & 0x40)
                        {
                                TIM3CH1_CAPTURE_STA |= 0x80;
                                TIM3CH1_CAPTURE_VAL = TIM_GetCapture1(TIM3);
                                TIM_OC1PolarityConfig(TIM3, TIM_ICPolarity_Rising);
//																Indicator_Light_TIM2 = 1;   //code debug
                        }
                        else
                        {
                                TIM3CH1_CAPTURE_STA = 0;
                                TIM3CH1_CAPTURE_VAL = 0;
																TIM_SetCounter(TIM3, 0);
                                TIM3CH1_CAPTURE_STA |= 0x40;                                
                                TIM_OC1PolarityConfig(TIM3, TIM_ICPolarity_Falling);
//																Working_Light = 1;  //code debug
                        }
												
                }
        }
        TIM_ClearITPendingBit(TIM3, TIM_IT_CC1 | TIM_IT_Update); //����ж�
}
//TIM2 IQ HANDLER
void TIM2_IRQHandler(void)
{
				//CH1
        if((TIM2CH1_CAPTURE_STA & 0x80) == 0)
        {
                if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
                {											
                        if(TIM2CH1_CAPTURE_STA & 0x40)
                        {
                                if((TIM2CH1_CAPTURE_STA & 0x3F) == 0x3F)
                                {
                                        TIM2CH1_CAPTURE_STA |= 0x80;
                                        TIM2CH1_CAPTURE_VAL = 0xFFFF;
//																				Working_Light = 0;  //code debug
                                }
                                else
                                {
                                        TIM2CH1_CAPTURE_STA++;
//																				Indicator_Light_TIM2 = 0;   //code debug
                                }
                        }
                }
                if(TIM_GetITStatus(TIM2, TIM_IT_CC1) != RESET)
                {
                        if(TIM2CH1_CAPTURE_STA & 0x40)
                        {
                                TIM2CH1_CAPTURE_STA |= 0x80;
                                TIM2CH1_CAPTURE_VAL = TIM_GetCapture1(TIM2);
                                TIM_OC1PolarityConfig(TIM2, TIM_ICPolarity_Rising);
//																Indicator_Light_TIM2 = 1;   //code debug
                        }
                        else
                        {
                                TIM2CH1_CAPTURE_STA = 0;
                                TIM2CH1_CAPTURE_VAL = 0;
																TIM_SetCounter(TIM2, 0);
                                TIM2CH1_CAPTURE_STA |= 0x40;                                
                                TIM_OC1PolarityConfig(TIM2, TIM_ICPolarity_Falling);
//																Working_Light = 1;  //code debug
                        }
												
                }
        }
        TIM_ClearITPendingBit(TIM2, TIM_IT_CC1 | TIM_IT_Update); //����ж�
}

/**�������
  ************************************
  * @brief 
  * @param  arr:5999   psc:72
  * @retval None
        ************************************
*/
u16 Ultrasonic_Value()
{
				u32 temp;
        GPIO_SetBits(GPIOB, GPIO_Pin_0);
        delay_us(20);
        GPIO_ResetBits(GPIOB, GPIO_Pin_0);
//        Ultrasonic_TIM4_Init(arr, psc);
//				delay_ms(1);
//        while(TIM4CH1_CAPTURE_STA&0x80)
//        {
//                temp=TIM4CH1_CAPTURE_STA&0X3F;
//								temp*=65536;//���ʱ���ܺ�
//								temp+=TIM4CH1_CAPTURE_VAL;//�õ��ܵĸߵ�ƽʱ��
//								//value = ~~ (cm)
//								value = 340*temp/2/10000;
////                value = (TIM4CH1_CAPTURE_STA * arr + TIM4CH1_CAPTURE_VAL) / 58;  //cm=us/58   mm=cm*10
//                TIM4CH1_CAPTURE_STA = 0;
//        }
	
			// test code begin	
				if(TIM4CH1_CAPTURE_STA&0X80)//�ɹ�������һ��������
		{
			temp=TIM4CH1_CAPTURE_STA&0X3F;
			temp*=65536;//���ʱ���ܺ�
			temp+=TIM4CH1_CAPTURE_VAL;//�õ��ܵĸߵ�ƽʱ��
			value = 340*temp/2/10000;
			TIM4CH1_CAPTURE_STA=0;//������һ�β���
		}
		// test code end
        return value;
}

u16 Ultrasonic_Value2()
{
				u32 temp;
        GPIO_SetBits(GPIOB, GPIO_Pin_1);
        delay_us(20);
        GPIO_ResetBits(GPIOB, GPIO_Pin_1);
        
//				delay_ms(1);
//        while(TIM4CH2_CAPTURE_STA&0x80)
//        {
//								temp=TIM4CH2_CAPTURE_STA&0X3F;
//								temp*=65536;//���ʱ���ܺ�
//								temp+=TIM4CH2_CAPTURE_VAL;//�õ��ܵĸߵ�ƽʱ��
//                TIM4CH2_CAPTURE_STA &= 0x3f;//��3y��־λ
//								//value = ~~ (cm)
//								value2 = 340*temp/2/10000;
////                value2 = (TIM4CH2_CAPTURE_STA * arr + TIM4CH2_CAPTURE_VAL) / 58;  //cm=us/58   mm=cm*10
//                TIM4CH2_CAPTURE_STA = 0;
//        }
		if(TIM4CH2_CAPTURE_STA&0X80)//�ɹ�������һ��������
		{
			temp=TIM4CH2_CAPTURE_STA&0X3F;
			temp*=65536;//���ʱ���ܺ�
			temp+=TIM4CH2_CAPTURE_VAL;//�õ��ܵĸߵ�ƽʱ��
			value2 = 340*temp/2/10000;
			TIM4CH2_CAPTURE_STA=0;//������һ�β���
		}
        return value2;
}

u16 Ultrasonic_Value3()
{
				u32 temp;
        GPIO_SetBits(GPIOB, GPIO_Pin_2);
        delay_us(20);
        GPIO_ResetBits(GPIOB, GPIO_Pin_2);
        
//				delay_ms(1);
        while(TIM4CH3_CAPTURE_STA&0x80)
        {
								temp=TIM4CH3_CAPTURE_STA&0X3F;
								temp*=65536;//���ʱ���ܺ�
								temp+=TIM4CH3_CAPTURE_VAL;//�õ��ܵĸߵ�ƽʱ��
                TIM4CH3_CAPTURE_STA &= 0x3f;//��3y��־λ
								//value = ~~ (cm)
								value3 = 340*temp/2/10000;
//                value2 = (TIM4CH2_CAPTURE_STA * arr + TIM4CH2_CAPTURE_VAL) / 58;  //cm=us/58   mm=cm*10
                TIM4CH3_CAPTURE_STA = 0;
        }
        return value3;
}
//get distance from TIM3 CH1
u16 Ultrasonic_Value3_from_TIM3_CH1()
{
				u32 temp;
        GPIO_SetBits(GPIOB, GPIO_Pin_2);
        delay_us(20);
        GPIO_ResetBits(GPIOB, GPIO_Pin_2);
        
//				delay_ms(1);
//        while(TIM3CH1_CAPTURE_STA&0x80)
//        {
//								temp=TIM3CH1_CAPTURE_STA&0X3F;
//								temp*=65536;//���ʱ���ܺ�
//								temp+=TIM3CH1_CAPTURE_VAL;//�õ��ܵĸߵ�ƽʱ��
//                TIM3CH1_CAPTURE_STA &= 0x3f;//��3y��־λ
//								//value = ~~ (cm)
//								value3 = 340*temp/2/10000;
////                value2 = (TIM4CH2_CAPTURE_STA * arr + TIM4CH2_CAPTURE_VAL) / 58;  //cm=us/58   mm=cm*10
//                TIM3CH1_CAPTURE_STA = 0;
//        }
			if(TIM3CH1_CAPTURE_STA&0X80)//�ɹ�������һ��������
		{
			temp=TIM3CH1_CAPTURE_STA&0X3F;
			temp*=65536;//���ʱ���ܺ�
			temp+=TIM3CH1_CAPTURE_VAL;//�õ��ܵĸߵ�ƽʱ��
			value3 = 340*temp/2/10000;
			TIM3CH1_CAPTURE_STA=0;//������һ�β���
		}
        return value3;
}
//get distance from TIM2 CH1
u16 Ultrasonic_Value2_from_TIM2_CH1()
{
				u32 temp;
        GPIO_SetBits(GPIOB, GPIO_Pin_1);
        delay_us(20);
        GPIO_ResetBits(GPIOB, GPIO_Pin_1);
        
//				delay_ms(1);
//        while(TIM2CH1_CAPTURE_STA&0x80)
//        {
//								temp=TIM2CH1_CAPTURE_STA&0X3F;
//								temp*=65536;//���ʱ���ܺ�
//								temp+=TIM2CH1_CAPTURE_VAL;//�õ��ܵĸߵ�ƽʱ��
//                TIM2CH1_CAPTURE_STA &= 0x3f;//��3y��־λ
//								//value = ~~ (cm)
//								value2 = 340*temp/2/10000;
////                value2 = (TIM4CH2_CAPTURE_STA * arr + TIM4CH2_CAPTURE_VAL) / 58;  //cm=us/58   mm=cm*10
//                TIM2CH1_CAPTURE_STA = 0;
//        }
	
		if(TIM2CH1_CAPTURE_STA&0X80)//�ɹ�������һ��������
		{
			temp=TIM2CH1_CAPTURE_STA&0X3F;
			temp*=65536;//���ʱ���ܺ�
			temp+=TIM2CH1_CAPTURE_VAL;//�õ��ܵĸߵ�ƽʱ��
			value2 = 340*temp/2/10000;
			TIM2CH1_CAPTURE_STA=0;//������һ�β���
			
//			if(Indicator_Light_TIM2 == 0){
//				Indicator_Light_TIM2 = 1;
//			}else if (Indicator_Light_TIM2 == 1){
//				Indicator_Light_TIM2 = 0;
//			}
		}
        return value2;
}

