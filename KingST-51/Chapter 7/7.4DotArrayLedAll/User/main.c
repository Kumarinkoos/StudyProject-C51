/*
*******************************************************************************
*                     《手把手教你学51单片机(C语言版)》
* 文件名：main.c
* 描  述：第7章 例程代码
* 版本号：v1.0.0
* 备  注：点亮所有点阵LED
*******************************************************************************
*/
#include <reg52.h>

sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;
sbit ENLED = P1^4;

//点阵LED和数码管一样，通过切换ADDR0-2来实现点亮所有点阵，所以也需要动态刷新

void main()
{
	//执行语句
	//LED相关
	ENLED = 0;	//使能U4的74HC138
	ADDR3 = 0;
	//中断相关
	EA = 1;	//使能总中断
	ET0 = 1;	//使能定时器0中断
	//定时器相关
	TMOD = 0x01;	//定时器T0选择模式1
	TH0 = 0xFC;		//延时1ms，赋初值为0xFC67
	TL0 = 0x67;
	TR0 = 1;		//开启定时器
	//循环体
	while(1);
}

//中断函数
void InterruptTimer0() interrupt 1
{
	//声明局部变量
	static unsigned char i = 0;	//动态刷新索引
	
	//中断函数的执行语句
	TH0 = 0xFC;	//定时器中断后重新赋0xFC67
	TL0 = 0x67;
	
	P0 = 0xFF;		//消影
	//动态刷新
	switch(i)
	{
		case 0:ADDR2 = 0; ADDR1 = 0; ADDR0 = 0; i++; P0 = 0x00; break;
		case 1:ADDR2 = 0; ADDR1 = 0; ADDR0 = 1; i++; P0 = 0x00; break;
		case 2:ADDR2 = 0; ADDR1 = 1; ADDR0 = 0; i++; P0 = 0x00; break;
		case 3:ADDR2 = 0; ADDR1 = 1; ADDR0 = 1; i++; P0 = 0x00; break;
		case 4:ADDR2 = 1; ADDR1 = 0; ADDR0 = 0; i++; P0 = 0x00; break;
		case 5:ADDR2 = 1; ADDR1 = 0; ADDR0 = 1; i++; P0 = 0x00; break;
		case 6:ADDR2 = 1; ADDR1 = 1; ADDR0 = 0; i++; P0 = 0x00; break;
		case 7:ADDR2 = 1; ADDR1 = 1; ADDR0 = 1; i = 0; P0 = 0x00; break;
		default: break;	
	}
}