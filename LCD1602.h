//LCD1602.h
#define uchar unsigned char
#define uint unsigned int
#define DataPort P0

sbit RS = P1^1;						   /*RS=0 R/W=0 д���� RS=1 R/W=0 д���� RS=0 R/W=1 ��״̬ */
sbit RW = P1^2;							         
sbit EN = P1^3;	//ʹ�ܶ�						 

#define RS_CLR RS=0 
#define RS_SET RS=1

#define RW_CLR RW=0 
#define RW_SET RW=1 

#define EN_CLR EN=0
#define EN_SET EN=1

void LCD1602_Init();	   		/*��ʼ��LCD1602*/
void LCD1602_BusyCheck();	    /*��æ����*/
void LCD1602_Write_DAT(uchar dat);		    /*д�����ݺ���*/
void LCD1602_Write_CMD(uchar cmd);			/*д�������*/
void LCD1602_Position(uchar x,uchar y);		/*���ڹ��λ�ú���*/
void LCD1602_Clear(void);					/*��������*/
void LCD1602_Write_String(uchar x,uchar y,uchar *s);	/*д���ַ�������*/

void LCD1602_Position(uchar x,uchar y)			        /*���ڹ��λ�ú���*/
{
    uchar position;
	if(x==0)
		position = 0x80 + y;	   //0x80�ǵ�һ�еĵ�һ���ַ��ĵ�ַ
	else
		position = 0xC0 + y;	   //0xc0�ǵڶ��еĵ�һ���ַ��ĵ�ַ
	LCD1602_Write_CMD(position);
}


void LCD1602_BusyCheck()		/*��æ����*/
{
	uchar sta;
	DataPort = 0xff;
	RS_CLR;
	RW_SET;
	do{
		EN_SET;
		sta = DataPort;
		EN_CLR;
	}while((sta & 0x80) == 0x80);  //״̬λ��Ϣ
}

void LCD1602_Write_DAT(uchar dat)		  /*д�����ݺ���*/
{
	LCD1602_BusyCheck();		 //æ��ȴ�
	RS_SET;
	RW_CLR;
	EN_CLR;
	DataPort = dat;
	EN_SET;
	EN_CLR;
}

void LCD1602_Write_CMD(uchar cmd)		   /*д�������*/
{
	LCD1602_BusyCheck();		 //æ��ȴ�
 	RS_CLR; 
	RW_CLR; 
 	EN_SET; 
 	DataPort=cmd; 
	EN_CLR;
}

void LCD1602_Clear() 			/*��������*/
{ 
	LCD1602_Write_CMD(0x01);
	LCD1602_Position(0,0);	
}

void LCD1602_Write_String(uchar x,uchar y,uchar *s) 		   /*д���ַ�������*/
 {  
	if(x==0) LCD1602_Write_CMD(0x80+y); 
	else LCD1602_Write_CMD(0xc0+y);    	
	while (*s)    
 		LCD1602_Write_DAT(*s++);     
}
	
void LCD1602_Init()
{
	LCD1602_Write_CMD(0x38);/* ������ʾģʽ */
	LCD1602_Write_CMD(0X0F);/* ����ʾ�����ù�� */
	LCD1602_Position(0,0);
}

