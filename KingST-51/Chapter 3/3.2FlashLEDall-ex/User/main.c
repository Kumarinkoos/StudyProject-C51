#include <reg52.h>

sbit LED2 = P0^0;
sbit LED3 = P0^1;
sbit LED4 = P0^2;
sbit LED5 = P0^3;
sbit LED6 = P0^4;
sbit LED7 = P0^5;
sbit LED8 = P0^6;
sbit LED9 = P0^7;
sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;
sbit ENLED = P1^4;

void main()
{
	unsigned int i = 0; //�ɰ汾C������Ҫ�������涨�����
		
	//����Ϊִ�����
	ENLED = 0;				//ʹ��U3��74HC138����E1��E2
	ADDR3 = 1;				//ʹ��U3��74HC138����E3��ʹ֮���������
	ADDR2 = 1;				//��U3��Y6���������Q16������
	ADDR1 = 1;
	ADDR0 = 0;
	while(1)
	{
		LED2 = 0;									//��������С��
		LED3 = 0;
		LED4 = 0;
		LED5 = 0;
		LED6 = 0;
		LED7 = 0;
		LED8 = 0;
		LED9 = 0;
		for(i = 0;i < 30000;i++);	//��ʱһ��ʱ��
		
		LED2 = 1;									//Ϩ������С��
		LED3 = 1;
		LED4 = 1;
		LED5 = 1;
		LED6 = 1;
		LED7 = 1;
		LED8 = 1;
		LED9 = 1;
		for(i = 0;i < 30000;i++);	//��ʱһ��ʱ��
	}
}