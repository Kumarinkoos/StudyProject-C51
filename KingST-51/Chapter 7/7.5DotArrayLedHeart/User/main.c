/*
*******************************************************************************
*                     《手把手教你学51单片机(C语言版)》
* 文件名：main.c
* 描  述：第7章 例程代码
* 版本号：v1.0.0
* 备  注：用点阵LED点亮爱心
*******************************************************************************
*/
#include <reg52.h>

sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;
sbit ENLED = P1^4;

unsigned char code image[] = {  //图片的字模表
    0xFF, 0x99, 0x00, 0x00, 0x00, 0x81, 0xC3, 0xE7
}

void main()
{
	//执行语句
	//LED部分
	ENLED = 0;	//使能U4的74HC138
	ADDR3 = 0;
	//中断部分
	EA = 1;		//使能总中断
	ET0 = 1;	//使能定时器T0中断
	//定时器部分
	TMOD = 0x01;    //设置T0为模式1
    TH0 = 0xFC;     //T0初值赋0xFC67，定时1ms
    TL0 = 0x67;
    TR0 = 1;       //启动定时器T0
	//循环体
	while(1);
}

//中断函数
void InterruptTimer0() interrupt 1
{
    static unsigned char i = 0; //动态扫描索引

    TH0 = 0xFC; //重新加载初值
    TL0 = 0x67;

    //以下为动态刷新
    P0 = 0xFF;  //消隐
    switch(i)
    {
        case 0 :ADDR2 = 0;ADDR1 = 0;ADDR0 = 0;i++;P0 = image[0];break;
        case 1 :ADDR2 = 0;ADDR1 = 0;ADDR0 = 1;i++;P0 = image[1];break;
        case 2 :ADDR2 = 0;ADDR1 = 1;ADDR0 = 0;i++;P0 = image[2];break;
        case 3 :ADDR2 = 0;ADDR1 = 1;ADDR0 = 1;i++;P0 = image[3];break;
        case 4 :ADDR2 = 1;ADDR1 = 0;ADDR0 = 0;i++;P0 = image[4];break;
        case 5 :ADDR2 = 1;ADDR1 = 0;ADDR0 = 1;i++;P0 = image[5];break;
        case 6 :ADDR2 = 1;ADDR1 = 1;ADDR0 = 0;i++;P0 = image[6];break;
        case 7 :ADDR2 = 1;ADDR1 = 1;ADDR0 = 1;i = 0;P0 = image[7];break;
        default :break;
    }
}