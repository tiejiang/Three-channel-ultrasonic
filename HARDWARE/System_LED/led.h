#ifndef _LED_H
#define _LED_H

//#define Working_Light								   			PBout(8)// PF1	����һ���ڵ㡢���һ�����̵�ָʾ��
#define Indicator_Light_TIM2 								PBout(9)// PF2	TIM1��ʱ������ָʾ��
#define Indicator_Light_Node_Detection			PBout(10)// PF4	�ڵ���ָʾ��
#define Indicator_Light_Tracking						PBout(11)// PF5	ѭ��ָʾ��
#define Indicator_Light_Obstacle_Detection	PBout(12)// PF6	�ϰ�̽��ָʾ��

void LED_Init(void);
void LED_TEST(void);
#endif
