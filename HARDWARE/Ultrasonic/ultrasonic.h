#ifndef _ultrasonic_H
#define _ultrasonic_H

extern float Distance0,Distance1;  

//#define	TRIG_PIN       PCout(2)  //TRIG       
//#define	ECHO_PIN       PCin(3)	 //ECHO

#define	TRIG_PIN       PBout(1)  //TRIG       
#define	ECHO_PIN       PBin(2)	 //ECHO
#define TRIG_PIN_2     PBout(0)  //TRIG       
#define ECHO_PIN_2     PBin(4)	 //ECHO

void UltrasonicWave_Configuration(void);               //�Գ�����ģ���ʼ��
void UltrasonicWave_StartMeasure(void);                //��ʼ��࣬����һ��>10us�����壬Ȼ��������صĸߵ�ƽʱ��
void UltrasonicWave_StartMeasure2(void);
#endif /* __UltrasonicWave_H */


