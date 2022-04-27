/*
*******************************************************************************
*                     《手把手教你学51单片机(C语言版)》
* 文件名：main.c
* 描  述：第6章 课后练习
* 版本号：v1.0.0
* 备  注：动态数码管只显示有效位
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
	unsigned long sec = 0;	//经过的秒数
	unsigned char buff[6] = {	//用于存取余后的数字，比较确定是否赋值给LEDBuff
	0, 0, 0, 0, 0, 0
	};
	char j = 5;	//用于循环比较的数组脚标用
	//执行语句
	//数码管部分
	ENLED = 0;	//使能U3
	ADDR3 = 1;	//ADDR0-2不需要初始化，因为需要动态改变以达到点亮不同数码管的要求
	
	//中断部分
	EA = 1;	//使能总中断
	ET0 = 1;	//使能定时器T0中断
	
	//定时器部分
	TMOD = 0x01;	//定时器T0设置为模式1
	TH0 = 0xFC;		//0xFC67为定时1ms
	TL0 = 0x67;
	TR0 = 1;		//启动T0
	
	while(1){
		if(flag1s == 1)	//T0溢出达到定时1ms
		{
			flag1s = 0;
			sec++;
			//将sec按十进制从低到高一次提取
			buff[0] = sec % 10;
			buff[1] = sec / 10 % 10;
			buff[2] = sec / 100 % 10;
			buff[3] = sec / 1000 % 10;
			buff[4] = sec / 10000 % 10;
			buff[5] = sec / 100000 % 10;
			
			//循环比较，如果不为0就赋值给数码管显示字符
			for(j = 5;j >= 0;j--)
			{
				if(buff[j] == 0)
				{
					LEDBuff[j] = 0xFF;
					
				}
				else
					break;	//检测到第一个非0的数值就跳出循环
			}
			for(;j >= 0;j--)
			{
				LEDBuff[j] = LEDChar[buff[j]];
			}
		}
	}
}

/*定时器T0的中断服务函数*/
void InterruptTimer0() interrupt 1
{
	TH0 = 0xFC;	//定时器重新赋值
	TL0 = 0x67;
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