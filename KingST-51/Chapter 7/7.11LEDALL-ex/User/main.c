/*
*******************************************************************************
*                     《手把手教你学51单片机(C语言版)》
* 文件名：main.c
* 描  述：第7章 课后练习
* 版本号：v1.0.0
* 备  注：点亮所有LED包括LED小灯，数码管和点阵LED
*******************************************************************************
*/
#include <reg52.h>

sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;
sbit ENLED = P1^4;

//数码管
unsigned char code LedChar[10] = {
	0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8,
	0x80, 0x90
};

//点阵
unsigned char code image[10][8] = {
	{0xC3, 0x81, 0x99, 0x99, 0x99, 0x99, 0x81, 0xC3},  //数字0
	{0xEF, 0xE7, 0xE3, 0xE7, 0xE7, 0xE7, 0xE7, 0xC3},  //数字1
	{0xC3, 0x81, 0x9D, 0x87, 0xC3, 0xF9, 0xC1, 0x81},  //数字2
	{0xC3, 0x81, 0x9D, 0xC7, 0xC7, 0x9D, 0x81, 0xC3},  //数字3
	{0xCF, 0xC7, 0xC3, 0xC9, 0xC9, 0x81, 0xCF, 0xCF},  //数字4
	{0x81, 0xC1, 0xF9, 0xC3, 0x87, 0x9D, 0x81, 0xC3},  //数字5
	{0xC3, 0x81, 0xF9, 0xC1, 0x81, 0x99, 0x81, 0xC3},  //数字6
	{0x81, 0x81, 0x9F, 0xCF, 0xCF, 0xE7, 0xE7, 0xE7},  //数字7
	{0xC3, 0x81, 0x99, 0xC3, 0xC3, 0x99, 0x81, 0xC3},  //数字8
	{0xC3, 0x81, 0x99, 0x81, 0x83, 0x9F, 0x83, 0xC1},  //数字9
};

void main()
{
	//声明语句
	//执行语句
	//LED部分
	ENLED = 0;
	//中断部分
	EA = 1;		//使能总中断
	ET0 = 1;	//使能定时器T0中断
	//定时器部分
	TMOD = 0x01;	//定时器T0模式1
	TH0 = 0xFC;		//赋初值延时1ms
	TL0 = 0x67;
	TR0 = 1;		//开始定时器
	//循环体
	while(1)
	{
		
	}
}

//中断函数
void InterruptTimer0() interrupt 1
{
	//声明语句
	static unsigned char i = 0;	//动态刷新索引
	static unsigned int sec = 0;	//记录秒数
	static unsigned char index = 0;	//记录秒数显示画面的索引
	static unsigned char LED = 0xFF;	//控制点亮流水灯
	//执行语句
	TH0 = 0xFC;
	TL0 = 0x67;
	
	//动态刷新
	P0 = 0xFF;	//消影
	switch(i)
	{
		//数码管部分
		case 0: ADDR3 = 1; ADDR2 = 0; ADDR1 = 0; ADDR0 = 0; i++; P0 = LedChar[index]; break;
		case 1: ADDR3 = 1; ADDR2 = 0; ADDR1 = 0; ADDR0 = 1; i++; P0 = LedChar[index]; break;
		case 2: ADDR3 = 1; ADDR2 = 0; ADDR1 = 1; ADDR0 = 0; i++; P0 = LedChar[index]; break;
		case 3: ADDR3 = 1; ADDR2 = 0; ADDR1 = 1; ADDR0 = 1; i++; P0 = LedChar[index]; break;
		case 4: ADDR3 = 1; ADDR2 = 1; ADDR1 = 0; ADDR0 = 0; i++; P0 = LedChar[index]; break;
		case 5: ADDR3 = 1; ADDR2 = 1; ADDR1 = 0; ADDR0 = 1; i++; P0 = LedChar[index]; break;
		//点阵部分
		case 6: ADDR3 = 0; ADDR2 = 0; ADDR1 = 0; ADDR0 = 0; i++; P0 = image[index][0]; break;
		case 7: ADDR3 = 0; ADDR2 = 0; ADDR1 = 0; ADDR0 = 1; i++; P0 = image[index][1]; break;
		case 8: ADDR3 = 0; ADDR2 = 0; ADDR1 = 1; ADDR0 = 0; i++; P0 = image[index][2]; break;
		case 9: ADDR3 = 0; ADDR2 = 0; ADDR1 = 1; ADDR0 = 1; i++; P0 = image[index][3]; break;
		case 10: ADDR3 = 0; ADDR2 = 1; ADDR1 = 0; ADDR0 = 0; i++; P0 = image[index][4]; break;
		case 11: ADDR3 = 0; ADDR2 = 1; ADDR1 = 0; ADDR0 = 1; i++; P0 = image[index][5]; break;
		case 12: ADDR3 = 0; ADDR2 = 1; ADDR1 = 1; ADDR0 = 0; i++; P0 = image[index][6]; break;
		case 13: ADDR3 = 0; ADDR2 = 1; ADDR1 = 1; ADDR0 = 1; i++; P0 = image[index][7]; break;
		//LED部分
		case 14: ADDR3 = 1; ADDR2 = 1; ADDR1 = 1; ADDR0 = 0; i = 0; P0 = LED; break;
		default: break;
	}
	//记录数码管和点阵的秒数
	sec++;
	if(sec >= 1000)	//达到1s
	{
		sec = 0;
		index++;
		if(index == 0)
		{
			LED = 0xFF;
		}
		else if(index == 9)
		{
			LED = 0x00;
		}
		else
		{
			LED = ~(0x01 << (index - 1));
		}
		if(index >= 10)	//经过了所有显示的数字
		{
			index = 0;
		}
	}
}