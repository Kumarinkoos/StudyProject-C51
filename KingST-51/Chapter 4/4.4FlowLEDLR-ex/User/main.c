/*
*******************************************************************************
*                     《手把手教你学51单片机(C语言版)》
* 文件名：main.c
* 描  述：第4章 课后练习
* 版本号：v1.0.0
* 备  注：先向左逐次点亮LED后再向右逐次点亮LED
*******************************************************************************
*/
#include <reg52.h>

sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;
sbit ENLED = P1^4;

void main()
{
	//声明语句
	unsigned char cnt = 0; //用来移位控制
	unsigned int i = 0;		//用来软件延时
	unsigned char flag = 1;	//用来决定左移还是右移的flag
	//执行语句
	ENLED = 0;				//使能U3（74HC138）的E1和E2
	ADDR3 = 1;				//使能U3（74HC138）的E3，使之能正常输出
	ADDR2 = 1;				//经U3的Y6输出来开启Q16三极管
	ADDR1 = 1;
	ADDR0 = 0;
	while(1)
	{
 		if(flag == 1)
		{
			P0 = ~(0x01 << cnt);		//左移
			for(i = 0;i < 20000;i++);	//延时
			cnt++;
			if(cnt >= 8)					//移动不能超过8
			{
				cnt = 0;
				flag = 0;					//左移结束后将flag置0，接下来将右移
			}
		}else if(flag == 0)
		{
			P0 = ~(0x80 >> cnt);	//右移
			for(i = 0;i < 20000;i++);	//延时
			cnt++;
			if(cnt >= 8)					//移动不能超过8
			{
				cnt = 0;
				flag = 1;					//右移结束后将flag置1，接下来将左移
			}
		}
	}
}