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
	//执行语句
	ENLED = 0;				//使能U3（74HC138）的E1和E2
	ADDR3 = 1;				//使能U3（74HC138）的E3，使之能正常输出
	ADDR2 = 1;				//经U3的Y6输出来开启Q16三极管
	ADDR1 = 1;
	ADDR0 = 0;
	while(1)
	{
		P0 = ~(0x01 << cnt);	//进行左移cnt位后取反即为点亮LED
		for(i = 0;i < 20000;i++);	//延时一段时间
		cnt++;							//下次循环时，移动的位数加1即为点亮下一个LED
		if(cnt >= 8)
		{
				cnt = 0;		//如果移动位数超过7以后需要重新计数
		}
	}
}