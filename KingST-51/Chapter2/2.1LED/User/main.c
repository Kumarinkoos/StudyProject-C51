#include <reg52.h>	//包含特殊功能寄存器定义的头文件

sbit LED = P0^0;	//位地址声明
sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;
sbit ENLED = P1^4;

void main()
{
	ENLED = 0;
	ADDR3 = 1;
	ADDR2 = 1;
	ADDR1 = 1;
	ADDR0 = 0;
	
	LED = 0;	//点亮小灯
	while(1);	// 程序停在这里
}