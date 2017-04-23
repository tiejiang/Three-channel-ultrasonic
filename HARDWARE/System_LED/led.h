#ifndef _LED_H
#define _LED_H

//#define Working_Light								   			PBout(8)// PF1	经过一个节点、完成一个过程的指示灯
#define Indicator_Light_TIM2 								PBout(9)// PF2	TIM1定时器工作指示灯
#define Indicator_Light_Node_Detection			PBout(10)// PF4	节点检测指示灯
#define Indicator_Light_Tracking						PBout(11)// PF5	循迹指示灯
#define Indicator_Light_Obstacle_Detection	PBout(12)// PF6	障碍探测指示灯

void LED_Init(void);
void LED_TEST(void);
#endif
