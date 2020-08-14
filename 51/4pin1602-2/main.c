
//四总线，只写方式
//2014.03.11
//6M晶振,STC12C5604AD(225);
//
#include <reg51.h>
/************自定义字符*********************/
//汉字字符，12x16点阵，前两列为空，占用4个字符，
unsigned char code font12x16[][8]=
{
    {0x00,0x00,0x00,0x07,0x01,0x02,0x04,0x07},//左上 //
    {0x00,0x10,0x08,0x1f,0x00,0x00,0x04,0x1e},//右上  //
    {0x01,0x01,0x01,0x01,0x01,0x02,0x04,0x00},//左下 //
    {0x08,0x08,0x08,0x08,0x08,0x09,0x07,0x00},//右下 // 充
    {0x00,0x00,0x00,0x07,0x04,0x04,0x04,0x07},//左上 //
    {0x00,0x10,0x10,0x1e,0x12,0x12,0x12,0x3e},//右上  //
    {0x04,0x04,0x07,0x00,0x00,0x00,0x00,0x00},//左下 //
    {0x12,0x12,0x1e,0x10,0x10,0x11,0x0f,0x00},//右下 // 电
    {0x00,0x07,0x05,0x05,0x07,0x00,0x00,0x07},//左上 //
    {0x00,0x0e,0x0a,0x0a,0x0e,0x00,0x12,0x1f},//右上  //
    {0x01,0x02,0x04,0x07,0x05,0x05,0x07,0x00},//左下 //
    {0x08,0x07,0x00,0x07,0x05,0x05,0x07,0x00},//右下 // 器
}
;

//#define  LCDdata     P1  //数据输入端口
sbit LCD1602_RS=P3^2;   // 命令或数据状态
sbit LCD1602_EN=P3^3;   //使能端
//sbit led =P3^0;   //背光控制
sbit io7 = P0^7;
sbit io6 = P0^6;
sbit io5 = P0^5;
sbit io4 = P0^4;
sbit ACC7 = ACC^7;      //累加器第7位
sbit ACC6 = ACC^6;      //累加器第6位
sbit ACC5 = ACC^5;      //累加器第5位
sbit ACC4 = ACC^4;      //累加器第4位
sbit ACC3 = ACC^3;      //累加器第3位
sbit ACC2 = ACC^2;      //累加器第2位
sbit ACC1 = ACC^1;      //累加器第1位
sbit ACC0 = ACC^0;      //累加器第0位

#define   LINE1        0
#define   LINE2        1
#define   LINE1_HEAD       0x80
#define   LINE2_HEAD       0xC0
/*****************************1MS延时***************************************/
void delay_nms(unsigned int n)
{
    unsigned int u;
    while (n--)
    {
        for(u=0;u<123;u++) //12M晶振,89C51(123);6M晶振,STC12C5604AD(299);
        {}
    }
}
/***************用LCD1602高4位数据线写命令**********************/
void LCD_com(unsigned char command)
{
    LCD1602_RS = 0;    //写命令
    delay_nms(1);
    LCD1602_EN = 1; //
    ACC=command;
    io7=ACC7;
    io6=ACC6;
    io5=ACC5;
    io4=ACC4;
    LCD1602_EN = 0;//下降沿将数据写入LCD1602
    delay_nms(1);
    LCD1602_EN = 1; //
    ACC=command;
    io7=ACC3;
    io6=ACC2;
    io5=ACC1;
    io4=ACC0;
    LCD1602_EN = 0;//下降沿将数据写入LCD1602
}
/************用LCD1602高4位数据线写数据*********************/
void LCD_dat(unsigned char dat)
{
    LCD1602_RS = 1; //写数据
    delay_nms(1);
    LCD1602_EN = 1; //
    ACC=dat;
    io7=ACC7;
    io6=ACC6;
    io5=ACC5;
    io4=ACC4;
    LCD1602_EN = 0;//下降沿将数据写入LCD1602
    delay_nms(1);
    LCD1602_EN = 1; //
    ACC=dat;
    io7=ACC3;
    io6=ACC2;
    io5=ACC1;
    io4=ACC0;
    LCD1602_EN = 0;//下降沿将数据写入LCD1602

}

/****************设置显示地址******************************/
void LCD_set_xy(unsigned char x,unsigned char y)
{            
    unsigned char address;
    if(y == LINE1)
        address = LINE1_HEAD + x;
    else    
        address = LINE2_HEAD + x;
    LCD_com(address);
}
/********************写一个字符的数据********************************************/
void LCD_write_char( unsigned char x,unsigned char y,unsigned char dat)
{
    LCD_set_xy(x,y);
    LCD_dat(dat);
}

/**********************写一个字符串***********************************************/
void LCD_write_string(unsigned char x,unsigned char y,unsigned char *s)
{
    LCD_set_xy(x,y);
    while(*s)  
    {
        //LCDdata = *s;
        LCD_dat(*s);  
        s++;
    }
}
/*******************/
void LCD_init(void)
{
    LCD_com(0x02);//设置4位数据接口set 4 bit data transmission mode
    LCD_com(0x28);//设置4位数据接口，两行显示，5x7点阵字符set 8 bit data transmission mode
    LCD_com(0x0C);//开显示，不显示光标，字符不闪烁open display (enable lcd display)
    //LCD_com(0x80);//set lcd first display address
    LCD_com(0x01);//清屏clear screen
    delay_nms(2); //
}
void main(void)
{
    unsigned char a,cg,cg1;
    LCD_init();
    delay_nms(2);
    LCD_write_string(0,LINE1,"ABCDEFGHIJKLMNOP");
    LCD_write_string(0,LINE2,"QRSTUVWXYZ012345");
    delay_nms(1000);
    LCD_com(0x01);
    delay_nms(2);
    LCD_write_string(0,LINE1,"text");
    LCD_write_string(0,LINE2,"zj97czb");
    //***********************显示汉字**************
    LCD_com(0x60);
    for(cg1=0;cg1<8;cg1++)
    {
        for(cg=0;cg<8;cg++)
        {
            LCD_dat(font12x16[cg1][cg]);
        }
    }

    //****************************************************
    LCD_write_char(12,LINE1,4);
    LCD_write_char(13,LINE1,5);  //充
    LCD_write_char(12,LINE2,6);
    LCD_write_char(13,LINE2,7);
    //****************************************************
    //****************************************************
    LCD_write_char(14,LINE1,0);
    LCD_write_char(15,LINE1,1);  //电
    LCD_write_char(14,LINE2,2);
    LCD_write_char(15,LINE2,3);
    //****************************************************/
    while(1 )    
    {  
        LCD_write_char(5,LINE1,a/100+48);
        LCD_write_char(6,LINE1,a/10%10+48);
        LCD_write_char(7,LINE1,a%10+48);
        delay_nms(100);    
        a++;    
    }
}
