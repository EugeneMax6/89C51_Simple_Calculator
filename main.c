//main.c 
#include "reg52.h"
#include "LCD1602.h"
#define uchar unsigned char
#define uint unsigned int

sbit LED=P1^7;
sbit sw=P1^6;

uchar button;
uint op;			  //单次计算符
int keyscan();		  //按键扫描函数
int key_value;		  //按键返回值
uchar kk,pre_P2,state;		//state代表运算符号
long  NUMA,NUMB;			//两个运算数
uchar table[16]={'0'};			   //将结果以字符数组存入，方便输出
long result;					   //long类型的结果，便于更大数值的计算
void Int_to_Table(long dat)		   //将最终值的各个位分离开来，存到字符数组中
{
	uint i=0,m=0,temp[16]={0};
	if(dat<0)	  //如果结果是负数，数组第一位为负号
	{
		table[m]='-';
		dat= -dat;
		m++;
	}
	do			  //每一位数字存入临时数组temp
	{
		temp[i]=dat%10;			//结果对10取余得到每位数
		dat=dat/10;
		i++;
	}while(dat);
	while(i)
	{
		i--;
		table[m]=temp[i]+'0';  		//table数组是uchar，temp是int，进行整型到字符型的转换
		m++;
	}
	table[m]='\0';
}

void start()
{
	op=0;
	result=0;			  //初始化运算结果为0
	while(button)		   //如果开关按下
	{
		key_value = keyscan();
		if(P2 != 0xF0) //按键松开
		{
			if(key_value>=0 && key_value<=9)  //如果按下的按键是0~9，进行赋值和显示相应数字
			{
				result=result*10+key_value;	  //由扫描到的数字进行赋值
				LCD1602_Write_DAT(key_value+'0');		 //LCD1602显示相应数字
			}
			else if(key_value>=12 && key_value<=15)	  //如果按下的按键是加减乘除，显示相应运算符号
			{
				if(op==0)
				{
					op=1;
					NUMA = result;	 //给第一个运算数赋值
					if(op==1)
					{
						LCD1602_Clear();
						Int_to_Table(result);
						LCD1602_Write_String(0,0,table);
					}
					if(key_value==12)		  //如果按下加号
					{	
						state = '+';		  //符号赋值+
						LCD1602_Write_DAT('+');			 //显示加号
					}
					else if(key_value==13)		  //如果按下减号
					{
						state = '-';			 //符号赋值-
						LCD1602_Write_DAT('-');			 //显示减号
					}
					else if(key_value==14)		   //如果按下乘号
					{
						state = '*';		   //符号赋值乘号
						LCD1602_Write_DAT('*');				 //显示乘号
					}
					else if(key_value==15)				 //如果按下除号
					{
						state = '/';					//符号赋值除号
						LCD1602_Write_DAT('/');			//显示除号
					}
					result=0;		  //重置result，为第二个运算数赋值准备
				}	
			}
			else if(key_value==11) 	//如果按下等号
			{
				uint flag=1;				  //除数标志，默认为1
				NUMB = result;
				if(state == '+')
					result = NUMA + NUMB;	  //两数相加
				else if(state == '-')
					result = NUMA - NUMB;	  //两数相减
				else if(state == '*')
					result = NUMA * NUMB;	  //两数相乘
				else if(state == '/')
				{	
					if(NUMB==0) flag=0;		   //如果除数为0，flag改为0
					else result = NUMA / NUMB;			 //两数相除
				}
				if(flag==1)					  //如果正常输出结果
				{
					LCD1602_Position (1,0);	   // 设置光标显示区域
					LCD1602_Write_DAT('=');
					Int_to_Table(result);	  		 //result存入数组，方便多位数字的输出
					LCD1602_Write_String(1,1,table);   //显示结果
				}
				else 
				{
				 	LCD1602_Write_String(0,0,"Mistake!!!");		 	//除数为0，输出错误信息
					LCD1602_Write_String(1,0,"Divisor is Zero");	
				}
				state = 0;	//重置运算符号变量
				op=0;
			}
			else if(key_value==10)	//清屏、重置
			{
				NUMA = 0;			//操作数全部重置
				NUMB = 0;
				result = 0;
				op = 0;
				LCD1602_Clear();	//LCD1602清屏
			}
		
		}
		kk = 200;
		while(kk--);		
	}
}
void main()
{	button=0;
	IE=0x85;    //EA置1，EX1和EX0置1
	TCON=0x05;	//IT1和IT0置1，负边沿触发
	PX1=1;		//INT1优先级高
	LED=0;
	while(1);
}
void int0() interrupt 0{			//INT0中断  打开
	button=1;
	LED=1;			  //开机时自动打开LED灯
	LCD1602_Init();	  		//LCD1602初始化
	start();		  //计算器进入运行
}
void int1() interrupt 2{			//INT1中断	关闭
	LCD1602_Clear();	 
	LCD1602_Write_CMD(0X08);  //LCD1602关闭显示
	button=0;
	LED=0;

}


