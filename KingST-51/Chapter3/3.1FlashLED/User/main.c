#include <reg52.h>

sbit LED = P0^0;
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
		LED = 0;									//点亮小灯
		for(i = 0;i < 30000;i++);	//延时一段时间
		LED = 1;									//熄灭小灯
		for(i = 0;i < 30000;i++);	//延时一段时间
	}
}