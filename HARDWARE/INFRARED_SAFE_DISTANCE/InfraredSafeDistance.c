#include "InfraredSafeDistance.h"
#include "stm32f10x.h"
#include "usart.h"
#include "led.h"
#include "delay.h"

/*************************
智能小车两侧红外避障安全距离端口引脚定义 PA5(左侧)PA6（右侧）

**********************************/
void InfraredSafeDistance_Init(void){
		/*GPIO端口配置结构体变量定义*/
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//打开GPIOA时钟	
	GPIO_InitStructure.GPIO_Pin	= GPIO_Pin_4|GPIO_Pin_5;//设置输入端口引脚---PA5.6
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置为上拉输入
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}
//左右侧红外避障安全距离处理
void Safe_DistanceSensor(){		
		if(!LeftSafeDistanceSensor){
			printf("%d, %d\n",1,000);
//			Working_Light=!Working_Light;//闪烁LED,提示系统正在运行.
			delay_ms(1000);
		}else if(!RightSafeDistanceSensor){
			printf("%d, %d\n",3,000);
//			Working_Light=!Working_Light;//闪烁LED,提示系统正在运行.
			delay_ms(1000);
		}
}


