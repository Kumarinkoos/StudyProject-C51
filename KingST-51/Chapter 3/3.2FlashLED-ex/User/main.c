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
		LED2 = 0;									//����LED2С��
		for(i = 0;i < 30000;i++);	//��ʱһ��ʱ��
		LED2 = 1;									//Ϩ��LED2С��
		for(i = 0;i < 30000;i++);	//��ʱһ��ʱ��
		
		LED3 = 0;									//����LED3С��
		for(i = 0;i < 30000;i++);	//��ʱһ��ʱ��
		LED3 = 1;									//Ϩ��LED3С��
		for(i = 0;i < 30000;i++);	//��ʱһ��ʱ��
		
		LED4 = 0;									//����LED4С��
		for(i = 0;i < 30000;i++);	//��ʱһ��ʱ��
		LED4 = 1;									//Ϩ��LED4С��
		for(i = 0;i < 30000;i++);	//��ʱһ��ʱ��
		
		LED5 = 0;									//����LED5С��
		for(i = 0;i < 30000;i++);	//��ʱһ��ʱ��
		LED5 = 1;									//Ϩ��LED5С��
		for(i = 0;i < 30000;i++);	//��ʱһ��ʱ��
		
		LED6 = 0;									//����LED6С��
		for(i = 0;i < 30000;i++);	//��ʱһ��ʱ��
		LED6 = 1;									//Ϩ��LED6С��
		for(i = 0;i < 30000;i++);	//��ʱһ��ʱ��
		
		LED7 = 0;									//����LED7С��
		for(i = 0;i < 30000;i++);	//��ʱһ��ʱ��
		LED7 = 1;									//Ϩ��LED7С��
		for(i = 0;i < 30000;i++);	//��ʱһ��ʱ��
		
		LED8 = 0;									//����LED8С��
		for(i = 0;i < 30000;i++);	//��ʱһ��ʱ��
		LED8 = 1;									//Ϩ��LED8С��
		for(i = 0;i < 30000;i++);	//��ʱһ��ʱ��
		
		LED9 = 0;									//����LED9С��
		for(i = 0;i < 30000;i++);	//��ʱһ��ʱ��
		LED9 = 1;									//Ϩ��LED9С��
		for(i = 0;i < 30000;i++);	//��ʱһ��ʱ��
	}
}