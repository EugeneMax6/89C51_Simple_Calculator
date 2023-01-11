#include "reg52.h"
#define uchar unsigned char
#define uint unsigned int
void delay_ms(uint i){ //延时函数
	uint j=0;
	uint n=0;
	for(j=0;j<i;j++)
		for(n=0;n<=118;n++);
}
int keyscan()  /*矩阵键盘扫描函数*/
{	
	uchar row,col;			//定义行列变量
	static int value=0; 	//定义按键值
	
	P2 = 0xF0;		//将高四位电平拉高
	if(P2 != 0xF0) 	//当不全为高电平，说明有按键按下
	{ 	
		delay_ms(10);	//延时去抖动
		if(P2 != 0xF0)	  //再次检测
		{	
			P2=0xFF;P2 = 0xF0; row = P2; //采用行列扫描法，将行值赋给row
			P2=0xFF;P2 = 0x0F; col = P2; //再将列值赋给col
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
	return value; //返回最终的键值
}