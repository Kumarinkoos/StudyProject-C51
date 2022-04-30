/*
*******************************************************************************
*                     《手把手教你学51单片机(C语言版)》
* 文件名：main.c
* 描  述：第7章 课后练习
* 版本号：v1.0.0
* 备  注：点阵LED进行倒计时
*******************************************************************************
*/
#include <reg52.h>

sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;
sbit ENLED = P1^4;

unsigned char code image[10][8] = {
	{0xC3, 0x81, 0x99, 0x81, 0x83, 0x9F, 0x83, 0xC1},  //数字9
	{0xC3, 0x81, 0x99, 0xC3, 0xC3, 0x99, 0x81, 0xC3},  //数字8
	{0x81, 0x81, 0x9F, 0xCF, 0xCF, 0xE7, 0xE7, 0xE7},  //数字7
	{0xC3, 0x81, 0xF9, 0xC1, 0x81, 0x99, 0x81, 0xC3},  //数字6
	{0x81, 0xC1, 0xF9, 0xC3, 0x87, 0x9D, 0x81, 0xC3},  //数字5
	{0xCF, 0xC7, 0xC3, 0xC9, 0xC9, 0x81, 0xCF, 0xCF},  //数字4
	{0xC3, 0x81, 0x9D, 0xC7, 0xC7, 0x9D, 0x81, 0xC3},  //数字3
	{0xC3, 0x81, 0x9D, 0x87, 0xC3, 0xF9, 0xC1, 0x81},  //数字2
	{0xEF, 0xE7, 0xE3, 0xE7, 0xE7, 0xE7, 0xE7, 0xC3},  //数字1
	{0xC3, 0x81, 0x99, 0x99, 0x99, 0x99, 0x81, 0xC3},  //数字0
};

void main()
{
    //执行语句
    //LED部分
    ENLED = 0;  //使能U4的74HC138
    ADDR3 = 0;
    //中断部分
    EA = 1;     //使能总中断
    ET0 = 1;    //使能定时器0中断
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
    static unsigned int tmr = 0;   //用于累加后延时250ms
    static unsigned char index = 0; //用于图片刷新

    TH0 = 0xFC; //重新加载初值
    TL0 = 0x67;

    //以下为动态刷新
    P0 = 0xFF;  //消隐
    switch(i)
    {
        case 0 :ADDR2 = 0;ADDR1 = 0;ADDR0 = 0;i++;P0 = image[index][0];break;
        case 1 :ADDR2 = 0;ADDR1 = 0;ADDR0 = 1;i++;P0 = image[index][1];break;
        case 2 :ADDR2 = 0;ADDR1 = 1;ADDR0 = 0;i++;P0 = image[index][2];break;
        case 3 :ADDR2 = 0;ADDR1 = 1;ADDR0 = 1;i++;P0 = image[index][3];break;
        case 4 :ADDR2 = 1;ADDR1 = 0;ADDR0 = 0;i++;P0 = image[index][4];break;
        case 5 :ADDR2 = 1;ADDR1 = 0;ADDR0 = 1;i++;P0 = image[index][5];break;
        case 6 :ADDR2 = 1;ADDR1 = 1;ADDR0 = 0;i++;P0 = image[index][6];break;
        case 7 :ADDR2 = 1;ADDR1 = 1;ADDR0 = 1;i = 0;P0 = image[index][7];break;
        default :break;
    }

    //定时器1s用来切换图片
    tmr++;
    if(tmr >= 1000)  //达到250ms切换图片
    {
        tmr = 0;
        index++;    //每250ms切换下一张图片
        if(index >= 10)
        {
            index = 0;
        }
    }
}