//LCD1602.h
#define uchar unsigned char
#define uint unsigned int
#define DataPort P0

sbit RS = P1^1;						   /*RS=0 R/W=0 写命令 RS=1 R/W=0 写数据 RS=0 R/W=1 读状态 */
sbit RW = P1^2;							         
sbit EN = P1^3;	//使能端						 

#define RS_CLR RS=0 
#define RS_SET RS=1

#define RW_CLR RW=0 
#define RW_SET RW=1 

#define EN_CLR EN=0
#define EN_SET EN=1

void LCD1602_Init();	   		/*初始化LCD1602*/
void LCD1602_BusyCheck();	    /*判忙函数*/
void LCD1602_Write_DAT(uchar dat);		    /*写入数据函数*/
void LCD1602_Write_CMD(uchar cmd);			/*写入命令函数*/
void LCD1602_Position(uchar x,uchar y);		/*调节光标位置函数*/
void LCD1602_Clear(void);					/*清屏函数*/
void LCD1602_Write_String(uchar x,uchar y,uchar *s);	/*写入字符串函数*/

void LCD1602_Position(uchar x,uchar y)			        /*调节光标位置函数*/
{
    uchar position;
	if(x==0)
		position = 0x80 + y;	   //0x80是第一行的第一个字符的地址
	else
		position = 0xC0 + y;	   //0xc0是第二行的第一个字符的地址
	LCD1602_Write_CMD(position);
}


void LCD1602_BusyCheck()		/*判忙函数*/
{
	uchar sta;
	DataPort = 0xff;
	RS_CLR;
	RW_SET;
	do{
		EN_SET;
		sta = DataPort;
		EN_CLR;
	}while((sta & 0x80) == 0x80);  //状态位信息
}

void LCD1602_Write_DAT(uchar dat)		  /*写入数据函数*/
{
	LCD1602_BusyCheck();		 //忙则等待
	RS_SET;
	RW_CLR;
	EN_CLR;
	DataPort = dat;
	EN_SET;
	EN_CLR;
}

void LCD1602_Write_CMD(uchar cmd)		   /*写入命令函数*/
{
	LCD1602_BusyCheck();		 //忙则等待
 	RS_CLR; 
	RW_CLR; 
 	EN_SET; 
 	DataPort=cmd; 
	EN_CLR;
}

void LCD1602_Clear() 			/*清屏函数*/
{ 
	LCD1602_Write_CMD(0x01);
	LCD1602_Position(0,0);	
}

void LCD1602_Write_String(uchar x,uchar y,uchar *s) 		   /*写入字符串函数*/
 {  
	if(x==0) LCD1602_Write_CMD(0x80+y); 
	else LCD1602_Write_CMD(0xc0+y);    	
	while (*s)    
 		LCD1602_Write_DAT(*s++);     
}
	
void LCD1602_Init()
{
	LCD1602_Write_CMD(0x38);/* 设置显示模式 */
	LCD1602_Write_CMD(0X0F);/* 打开显示和设置光标 */
	LCD1602_Position(0,0);
}

