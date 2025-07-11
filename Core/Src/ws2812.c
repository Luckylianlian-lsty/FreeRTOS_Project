/*
 * ws2812.c
 *
 *  Created on: May 30, 2025
 *      Author: lsty
 */


#include "ws2812.h"

#define	Code0 		30
#define	Code1 		60
#define	CodeReset 	0



uint8_t color[LED_COUNT][3];
//存10个小灯的颜色值，每个小灯有三个颜色值，每个颜色值0—255（2的8次方，8bit，一字节存一个颜色值）

void WS2812_Set(uint8_t index,uint8_t r,uint8_t g,uint8_t b)
{//设置某个小灯的颜色
	color[index][0]=r;
	color[index][1]=g;
	color[index][2]=b;
}

void WS2812_SetAll(uint8_t r,uint8_t g,uint8_t b)//设置所有小灯的颜色
{
	for(uint8_t i=0;i<LED_COUNT;i++)
	{
		WS2812_Set(i, r, g, b);
	}
}


void WS2812_Update()//将设置的颜色给更新到小灯上
{//原理为，通过占空比，能发送0，1，reset码。
//设置8bit的01数据，可以输出对应的一个颜色。输出8*3=24bit数据，就设置完一个灯。前8位为绿色，中8位为红色，后8位为蓝色
//最后输出reset，结束设置
	static uint16_t data[LED_COUNT*3*8+1];
	for(int i=0;i<LED_COUNT;i++)//取出颜色数据，再转换为占空比数据输出
	{
		uint8_t r=color[i][0];
		uint8_t g=color[i][1];
		uint8_t b=color[i][2];
		for(int j=0;j<8;j++)//分别比较八个位是否置为一。0x80是1左移7位的数（从第0位开始）
		{//每个灯间隔24字节，j是颜色对应的位，每个颜色间隔8位
			data[24*i+j]=(g & 0x80>>j) ? Code1:Code0;
			data[24*i+j+8]=(r & 0x80>>j) ? Code1:Code0;
			data[24*i+j+16]=(b & 0x80>>j) ? Code1:Code0;
		}

	}
	data[LED_COUNT*24]=CodeReset;//最后一位设置为reset码，表示结束

	HAL_TIM_PWM_Stop_DMA(&htim3, TIM_CHANNEL_1);//由于输出期间可能会突然改变输出值重新输出。
	//为了避免错乱，要先讲输出关闭，讲计数器置0，重新计数
	__HAL_TIM_SET_COUNTER(&htim3,0);
	HAL_TIM_PWM_Start_DMA(&htim3, TIM_CHANNEL_1, (uint32_t*)data, sizeof(data)/sizeof(data[0]));

}








