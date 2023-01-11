//main.c 
#include "reg52.h"
#include "LCD1602.h"
#define uchar unsigned char
#define uint unsigned int

sbit LED=P1^7;
sbit sw=P1^6;

uchar button;
uint op;			  //���μ����
int keyscan();		  //����ɨ�躯��
int key_value;		  //��������ֵ
uchar kk,pre_P2,state;		//state�����������
long  NUMA,NUMB;			//����������
uchar table[16]={'0'};			   //��������ַ�������룬�������
long result;					   //long���͵Ľ�������ڸ�����ֵ�ļ���
void Int_to_Table(long dat)		   //������ֵ�ĸ���λ���뿪�����浽�ַ�������
{
	uint i=0,m=0,temp[16]={0};
	if(dat<0)	  //�������Ǹ����������һλΪ����
	{
		table[m]='-';
		dat= -dat;
		m++;
	}
	do			  //ÿһλ���ִ�����ʱ����temp
	{
		temp[i]=dat%10;			//�����10ȡ��õ�ÿλ��
		dat=dat/10;
		i++;
	}while(dat);
	while(i)
	{
		i--;
		table[m]=temp[i]+'0';  		//table������uchar��temp��int���������͵��ַ��͵�ת��
		m++;
	}
	table[m]='\0';
}

void start()
{
	op=0;
	result=0;			  //��ʼ��������Ϊ0
	while(button)		   //������ذ���
	{
		key_value = keyscan();
		if(P2 != 0xF0) //�����ɿ�
		{
			if(key_value>=0 && key_value<=9)  //������µİ�����0~9�����и�ֵ����ʾ��Ӧ����
			{
				result=result*10+key_value;	  //��ɨ�赽�����ֽ��и�ֵ
				LCD1602_Write_DAT(key_value+'0');		 //LCD1602��ʾ��Ӧ����
			}
			else if(key_value>=12 && key_value<=15)	  //������µİ����ǼӼ��˳�����ʾ��Ӧ�������
			{
				if(op==0)
				{
					op=1;
					NUMA = result;	 //����һ����������ֵ
					if(op==1)
					{
						LCD1602_Clear();
						Int_to_Table(result);
						LCD1602_Write_String(0,0,table);
					}
					if(key_value==12)		  //������¼Ӻ�
					{	
						state = '+';		  //���Ÿ�ֵ+
						LCD1602_Write_DAT('+');			 //��ʾ�Ӻ�
					}
					else if(key_value==13)		  //������¼���
					{
						state = '-';			 //���Ÿ�ֵ-
						LCD1602_Write_DAT('-');			 //��ʾ����
					}
					else if(key_value==14)		   //������³˺�
					{
						state = '*';		   //���Ÿ�ֵ�˺�
						LCD1602_Write_DAT('*');				 //��ʾ�˺�
					}
					else if(key_value==15)				 //������³���
					{
						state = '/';					//���Ÿ�ֵ����
						LCD1602_Write_DAT('/');			//��ʾ����
					}
					result=0;		  //����result��Ϊ�ڶ�����������ֵ׼��
				}	
			}
			else if(key_value==11) 	//������µȺ�
			{
				uint flag=1;				  //������־��Ĭ��Ϊ1
				NUMB = result;
				if(state == '+')
					result = NUMA + NUMB;	  //�������
				else if(state == '-')
					result = NUMA - NUMB;	  //�������
				else if(state == '*')
					result = NUMA * NUMB;	  //�������
				else if(state == '/')
				{	
					if(NUMB==0) flag=0;		   //�������Ϊ0��flag��Ϊ0
					else result = NUMA / NUMB;			 //�������
				}
				if(flag==1)					  //�������������
				{
					LCD1602_Position (1,0);	   // ���ù����ʾ����
					LCD1602_Write_DAT('=');
					Int_to_Table(result);	  		 //result�������飬�����λ���ֵ����
					LCD1602_Write_String(1,1,table);   //��ʾ���
				}
				else 
				{
				 	LCD1602_Write_String(0,0,"Mistake!!!");		 	//����Ϊ0�����������Ϣ
					LCD1602_Write_String(1,0,"Divisor is Zero");	
				}
				state = 0;	//����������ű���
				op=0;
			}
			else if(key_value==10)	//����������
			{
				NUMA = 0;			//������ȫ������
				NUMB = 0;
				result = 0;
				op = 0;
				LCD1602_Clear();	//LCD1602����
			}
		
		}
		kk = 200;
		while(kk--);		
	}
}
void main()
{	button=0;
	IE=0x85;    //EA��1��EX1��EX0��1
	TCON=0x05;	//IT1��IT0��1�������ش���
	PX1=1;		//INT1���ȼ���
	LED=0;
	while(1);
}
void int0() interrupt 0{			//INT0�ж�  ��
	button=1;
	LED=1;			  //����ʱ�Զ���LED��
	LCD1602_Init();	  		//LCD1602��ʼ��
	start();		  //��������������
}
void int1() interrupt 2{			//INT1�ж�	�ر�
	LCD1602_Clear();	 
	LCD1602_Write_CMD(0X08);  //LCD1602�ر���ʾ
	button=0;
	LED=0;

}


