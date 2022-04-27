/*
*******************************************************************************
*                     《手把手教你学51单片机(C语言版)》
* 文件名：main.c
* 描  述：第6章 课后练习
* 版本号：v1.0.0
* 备  注：动态数码管倒计时，使用T1
*******************************************************************************
*/
#include <reg52.h>

sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;
sbit ENLED = P1^4;

//数码管显示字符真值表
unsigned char code LEDChar[] = {
	0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8,
	0x80, 0x90, 0x88, 0x83, 0xC6, 0xA1, 0x86, 0x8E
};
//数码管显示缓冲区，初值0xFF确保启动时不亮
unsigned char LEDBuff[6] = {
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
};

//由于中断函数也要用到，所以需要全局变量
unsigned int cnt = 0;	//记录T0中断次数，因为计数要1000所以需要用int
unsigned char i = 0;	//动态扫描索引，也就是第i个数码管
unsigned char flag1s = 0;	//达到1s的标志

void main()
{
	//声明语句
	unsigned long sec = 999999;	//经过的秒数
	//执行语句
	//数码管部分
	ENLED = 0;	//使能U3
	ADDR3 = 1;	//ADDR0-2不需要初始化，因为需要动态改变以达到点亮不同数码管的要求
	
	//中断部分
	EA = 1;	//使能总中断
	ET1 = 1;	//使能定时器T1中断
	
	//定时器部分
	TMOD = 0x10;	//定时器T1设置为模式1
	TH1 = 0xFC;		//0xFC67为定时1ms
	TL1 = 0x67;
	TR1 = 1;		//启动T1
	
	while(1){
		if(flag1s == 1)	//T1溢出达到定时1ms
		{
			flag1s = 0;
			sec--;
			//以下代码为将sec按十进制从低到高一次提取并转换为数码管显示字符
			LEDBuff[0] = LEDChar[sec % 10];
			LEDBuff[1] = LEDChar[sec / 10 % 10];
			LEDBuff[2] = LEDChar[sec / 100 % 10];
			LEDBuff[3] = LEDChar[sec / 1000 % 10];
			LEDBuff[4] = LEDChar[sec / 10000 % 10];
			LEDBuff[5] = LEDChar[sec / 100000 % 10];
		}
	}
}

/*定时器T0的中断服务函数*/
void InterruptTimer1() interrupt 3
{
	TH1 = 0xFC;	//定时器重新赋值
	TL1 = 0x67;
	cnt++;
	if(cnt >= 1000)	//达到1秒
	{
		cnt = 0;
		flag1s = 1;
	}
	
	//每次1ms定时到了除了cnt要加1以外，还需要刷新数码管
	//以下代码为完成数码管动态扫描刷新
	P0 = 0xFF;	//消影，每次刷新前把数码管灭掉
	switch(i)
	{
		case 0 : ADDR2 = 0;ADDR1 = 0;ADDR0 = 0;i++;P0 = LEDBuff[0];break;	//刷新第一个（个位）数码管
		case 1 : ADDR2 = 0;ADDR1 = 0;ADDR0 = 1;i++;P0 = LEDBuff[1];break;	//刷新第二个（十位）数码管
		case 2 : ADDR2 = 0;ADDR1 = 1;ADDR0 = 0;i++;P0 = LEDBuff[2];break;	//刷新第三个（百位）数码管
		case 3 : ADDR2 = 0;ADDR1 = 1;ADDR0 = 1;i++;P0 = LEDBuff[3];break;	//刷新第四个（千位）数码管
		case 4 : ADDR2 = 1;ADDR1 = 0;ADDR0 = 0;i++;P0 = LEDBuff[4];break;	//刷新第五个（万位）数码管
		case 5 : ADDR2 = 1;ADDR1 = 0;ADDR0 = 1;i = 0;P0 = LEDBuff[5];break;	//刷新第六个（十万位）数码管
		default : break;
	}
}