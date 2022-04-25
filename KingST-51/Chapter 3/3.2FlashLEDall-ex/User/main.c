/*
*******************************************************************************
*                     《手把手教你学51单片机(C语言版)》
* 文件名：main.c
* 描  述：第3章 课后练习
* 版本号：v1.0.0
* 备  注：闪烁所有LED
*******************************************************************************
*/
#include <reg52.h>

sbit LED2 = P0^0;
sbit LED3 = P0^1;
sbit LED4 = P0^2;
sbit LED5 = P0^3;
sbit LED6 = P0^4;
sbit LED7 = P0^5;
sbit LED8 = P0^6;
sbit LED9 = P0^7;
sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;
sbit ENLED = P1^4;

void main()
{
	unsigned int i = 0; //旧版本C语言需要在最上面定义变量
		
	//以下为执行语句
	ENLED = 0;				//使能U3（74HC138）的E1和E2
	ADDR3 = 1;				//使能U3（74HC138）的E3，使之能正常输出
	ADDR2 = 1;				//经U3的Y6输出来开启Q16三极管
	ADDR1 = 1;
	ADDR0 = 0;
	while(1)
	{
		LED2 = 0;									//点亮所有小灯
		LED3 = 0;
		LED4 = 0;
		LED5 = 0;
		LED6 = 0;
		LED7 = 0;
		LED8 = 0;
		LED9 = 0;
		for(i = 0;i < 30000;i++);	//延时一段时间
		
		LED2 = 1;									//熄灭所有小灯
		LED3 = 1;
		LED4 = 1;
		LED5 = 1;
		LED6 = 1;
		LED7 = 1;
		LED8 = 1;
		LED9 = 1;
		for(i = 0;i < 30000;i++);	//延时一段时间
	}
}