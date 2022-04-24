#include <reg52.h>

sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;
sbit ENLED = P1^4;

void main()
{
	//�������
	unsigned char cnt = 0; //������λ����
	unsigned int i = 0;		//���������ʱ
	//ִ�����
	ENLED = 0;				//ʹ��U3��74HC138����E1��E2
	ADDR3 = 1;				//ʹ��U3��74HC138����E3��ʹ֮���������
	ADDR2 = 1;				//��U3��Y6���������Q16������
	ADDR1 = 1;
	ADDR0 = 0;
	while(1)
	{
		P0 = ~(0x80 >> cnt);	//�������Ʋ�ȡ����Ϊ�������һ��LED
		for(i = 0;i < 20000;i++);
		cnt++;
		if(cnt >= 8)
		{
			cnt = 0;
		}
	}
}