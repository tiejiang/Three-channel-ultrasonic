#ifndef _TIMER_INIT_H
#define _TIMER_INIT_H
#include "sys.h"
extern float value; 
extern float value2;
extern float value3;

//#define	TRIG_PIN       PCout(2)  //TRIG       
//#define	ECHO_PIN       PCin(3)	 //ECHO

#define	TRIG_PIN       PBout(1)  //TRIG       
#define	ECHO_PIN       PBin(2)	 //ECHO
#define TRIG_PIN_2     PBout(0)  //TRIG       
#define ECHO_PIN_2     PBin(4)	 //ECHO


void Ultrasonic_TIM4_Init(u16 arr,u16 psc);               //�Գ�����ģ���ʼ��
void Ultrasonic_TIM3_Init(u16 arr,u16 psc);
void Ultrasonic_TIM2_Init(u16 arr,u16 psc);
u16 Ultrasonic_Value();                //��ʼ��࣬����һ��>10us�����壬Ȼ��������صĸߵ�ƽʱ��
u16 Ultrasonic_Value2();
u16 Ultrasonic_Value3();

u16 Ultrasonic_Value3_from_TIM3_CH1();
u16 Ultrasonic_Value2_from_TIM2_CH1();

#endif /* __UltrasonicWave_H */
