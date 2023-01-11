#include "reg52.h"
#define uchar unsigned char
#define uint unsigned int
void delay_ms(uint i){ //��ʱ����
	uint j=0;
	uint n=0;
	for(j=0;j<i;j++)
		for(n=0;n<=118;n++);
}
int keyscan()  /*�������ɨ�躯��*/
{	
	uchar row,col;			//�������б���
	static int value=0; 	//���尴��ֵ
	
	P2 = 0xF0;		//������λ��ƽ����
	if(P2 != 0xF0) 	//����ȫΪ�ߵ�ƽ��˵���а�������
	{ 	
		delay_ms(10);	//��ʱȥ����
		if(P2 != 0xF0)	  //�ٴμ��
		{	
			P2=0xFF;P2 = 0xF0; row = P2; //��������ɨ�跨������ֵ����row
			P2=0xFF;P2 = 0x0F; col = P2; //�ٽ���ֵ����col
			switch (row | col)	
			{
				case 0xeb : value = 0; break;
				case 0xd7 : value = 1; break;
				case 0xdb : value = 2; break;
				case 0xdd : value = 3; break;
				case 0xb7 : value = 4; break;
				case 0xbb : value = 5; break;
				case 0xbd : value = 6; break;
				case 0x77 : value = 7; break;
				case 0x7b : value = 8; break;
				case 0x7d : value = 9; break;
				case 0xe7 : value = 10;break;		
				case 0xed : value = 11;break;
				case 0xee : value = 12;break;
				case 0xde : value = 13;break;
				case 0xbe : value = 14;break;
				case 0x7e : value = 15;break;
				default   : value = 16;break;
			}
		}
	}
	return value; //�������յļ�ֵ
}