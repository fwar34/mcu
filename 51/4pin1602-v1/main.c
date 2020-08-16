//程序参考：http://www.dzdiy.com/html/201305/19/LCD1602.htm
#include <reg52.h>    //包含单片机寄存器的头文件
#include <intrins.h>
#define LCD_data P0
sbit RS=P3^2;
sbit E =P3^4;

sbit STA7 = P0 ^ 7;

unsigned char code digit[ ]={"0123456789"}; //定义字符数组显示数字
//*****************延时************************
void Delay600us()		//@12.000MHz
{
	unsigned char i, j;

	_nop_();
	_nop_();
	i = 7;
	j = 253;
	do
	{
		while (--j);
	} while (--i);
}

void Delay4ms()		//@12.000MHz
{
	unsigned char i, j;

	_nop_();
	_nop_();
	i = 47;
	j = 173;
	do
	{
		while (--j);
	} while (--i);
}

void Delay200ms()		//@12.000MHz
{
	unsigned char i, j, k;

	i = 10;
	j = 31;
	k = 147;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void Delay50ms()		//@12.000MHz
{
	unsigned char i, j, k;

	i = 3;
	j = 72;
	k = 161;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}


//*************液晶屏使能****************************
void LCD_en_write(void) 
{
	E=1;
	//delay_nus(1);
	E=0;
}
//*************写命令****************************
void LCD_write_command(unsigned char command)
{
	Delay600us();
    //LCD_check_busy();
	RS=0;
	//Rw=0;
	LCD_data&=0X0f; //清高四位
	LCD_data|=command&0xf0; //写高四位
	LCD_en_write();
	command=command<<4; //低四位移到高四位
	LCD_data&=0x0f; //清高四位
	LCD_data|=command&0xf0; //写低四位
	LCD_en_write();
}
//*************写数据****************************
void LCD_write_data(unsigned char value) 
{
	Delay600us();
    //LCD_check_busy();
	RS=1;
	//Rw=0;
	LCD_data&=0X0f; //清高四位
	LCD_data|=value&0xf0; //写高四位
	LCD_en_write();
	value=value<<4; //低四位移到高四位
	LCD_data&=0X0f; //清高四位
	LCD_data|=value&0xf0; //写低四位
	LCD_en_write();
}

//**********************设置显示位置*********************************
void set_position(unsigned char x,unsigned char y)
{
	unsigned char position;
	if (y == 0)
        position = 0x80 + x;
	else 
		position = 0xc0 + x;
    LCD_write_command(position);
}
//**********************显示字符串*****************************

void display_string(unsigned char x,unsigned char y,unsigned char *s)
{ 
    set_position(x,y);
	while (*s) 
 	{     
		LCD_write_data(*s);     
		s++;     
 	}
}
//********************显示数字*******************************xs
void display_num(unsigned char x,unsigned char y,unsigned int num)
{ 
   unsigned char i,j,k,m,n;
   set_position(x,y);
    i=num/10000;
    j=num/1000%10; 
	k=num/100%10;
	m=num/10%10;
    n=num%10;
	LCD_write_data(digit[i]);    //将万位数字的字符常量写入LCD
	LCD_write_data(digit[j]);    //将千位数字的字符常量写入LCD
	LCD_write_data(digit[k]);
	LCD_write_data(digit[m]);
    LCD_write_data('.');
	LCD_write_data(digit[n]);
}
//*************液晶初始化****************************
void LCD_init(void) 
{ 
    LCD_write_command(0x33);
    Delay4ms();
    LCD_write_command(0x32);
    Delay4ms();
	LCD_write_command(0x28);
	LCD_en_write();
	LCD_write_command(0x28); //4位显示！！！！！！！！！！！！！！！！！！
	LCD_write_command(0x0c); //显示开
	LCD_write_command(0x01); //清屏
	Delay200ms();
}
//*************主函数************************
void main(void)
{
	int i;
	LCD_init();
	display_string(0,0,"Hello Today!"); //显示一段文字
	while(1)
	{
		display_num(0,1,i); 
		Delay50ms();
		i++;
	}
}
