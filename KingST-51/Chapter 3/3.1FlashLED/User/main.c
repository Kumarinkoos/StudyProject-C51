#include <reg52.h>

sbit LED = P0^0;
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
		LED = 0;									//����С��
		for(i = 0;i < 30000;i++);	//��ʱһ��ʱ��
		LED = 1;									//Ϩ��С��
		for(i = 0;i < 30000;i++);	//��ʱһ��ʱ��
	}
}