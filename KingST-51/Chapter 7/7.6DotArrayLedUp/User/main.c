/*
*******************************************************************************
*                     《手把手教你学51单片机(C语言版)》
* 文件名：main.c
* 描  述：第7章 例程代码
* 版本号：v1.0.0
* 备  注：向上点亮点阵LED
*******************************************************************************
*/
#include <reg52.h>

sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;
sbit ENLED = P1^4;

unsigned char code image[] = {  //图片的字模表，电路图为行扫描，所有纵向移动可以一维数组连续读取
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x7D, 0x01, 0x01, 0x7D, 0xFF, 0xFF, 0xE3, 0xC1,
    0x81, 0x03, 0x03, 0x81, 0xC1, 0xE3, 0xFF, 0xFF,
    0x81, 0x01, 0x3F, 0x3F, 0x3F, 0x01, 0x81, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
};

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
    static unsigned char tmr = 0;   //切换图片的软件计时
    static unsigned char index = 0; //图片的索引

    TH0 = 0xFC; //重新加载初值
    TL0 = 0x67;

    //以下为动态刷新
    P0 = 0xFF;  //消隐
    switch(i)
    {
        case 0 :ADDR2 = 0;ADDR1 = 0;ADDR0 = 0;i++;P0 = image[index];break;
        case 1 :ADDR2 = 0;ADDR1 = 0;ADDR0 = 1;i++;P0 = image[index + 1];break;
        case 2 :ADDR2 = 0;ADDR1 = 1;ADDR0 = 0;i++;P0 = image[index + 2];break;
        case 3 :ADDR2 = 0;ADDR1 = 1;ADDR0 = 1;i++;P0 = image[index + 3];break;
        case 4 :ADDR2 = 1;ADDR1 = 0;ADDR0 = 0;i++;P0 = image[index + 4];break;
        case 5 :ADDR2 = 1;ADDR1 = 0;ADDR0 = 1;i++;P0 = image[index + 5];break;
        case 6 :ADDR2 = 1;ADDR1 = 1;ADDR0 = 0;i++;P0 = image[index + 6];break;
        case 7 :ADDR2 = 1;ADDR1 = 1;ADDR0 = 1;i = 0;P0 = image[index + 7];break;
        default :break;
    }
    //切换图片
    tmr++;
    if(tmr >= 250)  //达到250ms就切换图片
    {
        tmr = 0;
        index++;
        if (index >= 32)
        {
            index = 0;
        }
        

    }
}