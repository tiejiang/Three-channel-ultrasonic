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
//定时器 驱动代码	  		  
//////////////////////////////////////////////////////////////////////////////////   	 

//通用定时器中断初始化
//这里时钟选择为APB1的2倍，而APB1为36M
//arr：自动重装值。
//psc：时钟预分频数
//这里使用的是定时器2
void Timerx_Init2(u16 arr,u16 psc)
{
	/*TIM2 INIT*/
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE); //时钟使能

	TIM_TimeBaseStructure.TIM_Period =arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到5000为500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
  //TIM_ClearFlag(TIM2, TIM_FLAG_Update);							    		/* 清除溢出中断标志 */
	TIM_ITConfig(  //使能或者失能指定的TIM中断
		TIM2, //TIM2
		TIM_IT_Update  |  //TIM 中断源
		TIM_IT_Trigger,   //TIM 触发中断源 
		ENABLE  //使能
		);
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM2中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

	//TIM_Cmd(TIM2, ENABLE);  //使能TIMx外设
	
}

void Timer3_Init(u16 arr, u16 psc){
		/*TIM3 INIT*/						 
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE); //时钟使能

	TIM_TimeBaseStructure.TIM_Period =arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到5000为500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
  //TIM_ClearFlag(TIM2, TIM_FLAG_Update);							    		/* 清除溢出中断标志 */
	TIM_ITConfig(  //使能或者失能指定的TIM中断
		TIM3, //TIM3
		TIM_IT_Update  |  //TIM 中断源
		TIM_IT_Trigger,   //TIM 触发中断源 
		ENABLE  //使能
		);
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

	//TIM_Cmd(TIM3, ENABLE);  //使能TIMx外设
}

//void TIM2_IRQHandler(void)   //TIM2中断
//{
//	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
//		{
//			TIM_ClearITPendingBit(TIM2, TIM_IT_Update);  //清除TIMx的中断待处理位:TIM 中断源 
//			//LCD5110ShowNum(40,5,Distance0);
//			ir2 ++;
//		}
//}

//定时器3中断服务程序
//void TIM3_IRQHandler(void)   //TIM3中断
//{
//	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //检查TIM3更新中断发生与否
//		{
//		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //清除TIMx更新中断标志 
//				ir3 ++;
//		}
//}
/*
 * 函数名：UltrasonicWave_StartMeasure
 * 描述  ：开始测距，发送一个>10us的脉冲，然后测量返回的高电平时间
 * 输入  ：无
 * 输出  ：无	
 */
void UltrasonicWave_StartMeasure(void)
{
	TRIG_PIN=1; 		  					//送>10US的高电平RIG_PORT,TRIG_PIN
  delay_us(25);		                      //延时20US
	TRIG_PIN=0;
//	delay_ms(10);
//	if(ir2 == 1){
//		ir2 = 0;
		while(GPIO_ReadInputDataBit(GPIOB, ECHO_PIN) == RESET){  //等待高电平以退出循环
			Indicator_Light_TIM2 = 1;  //code debug
		}
//		Working_Light = 0;   //code debug
		TIM_SetCounter(TIM2,0);
		TIM_Cmd(TIM2, ENABLE);                                     //开启时钟
		while(GPIO_ReadInputDataBit(GPIOB,ECHO_PIN));	             //等待低电平(低电平才能退出循环)
		TIM_Cmd(TIM2, DISABLE);			                               //定时器2失能
		Distance0	=(TIM_GetCounter(TIM2) + ir2*1000)/58.0;									 //计算距离&&UltrasonicWave_Distance<150		
		ir2 = 0;
//	}
}

void UltrasonicWave_StartMeasure2(void)
{
	TRIG_PIN_2=1; 		  					//送>10US的高电平RIG_PORT,TRIG_PIN
  delay_us(25);		                      //延时20US
	TRIG_PIN_2=0;
//	delay_ms(10);
//	if(ir3 == 1){
//		ir3 = 0;
		while(GPIO_ReadInputDataBit(GPIOB, ECHO_PIN_2) == RESET){
//				Working_Light = 1;  //code debug
		}
//		Working_Light = 0;   //code debug
		TIM_SetCounter(TIM3,0);
		TIM_Cmd(TIM3, ENABLE);           //开启时钟
		while(GPIO_ReadInputDataBit(GPIOB,ECHO_PIN_2));	             //等待低电平(低电平才能退出循环)
		TIM_Cmd(TIM3, DISABLE);			                               //定时器2失能
		Distance1	= (TIM_GetCounter(TIM3) + ir2*1000)/58.0;									 //计算距离&&UltrasonicWave_Distance<150		
		ir3 = 0;
//	}
	
}


