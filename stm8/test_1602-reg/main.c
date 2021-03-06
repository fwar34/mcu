#include "iostm8s105c6.h"
#include "ds1302.h"

typedef unsigned char u8;
typedef unsigned char uint8_t;

#define LCD_DB PD_ODR
#define LCD_CTL GPIOC

#define LCD_RS PC_ODR_ODR1
#define LCD_RW PC_ODR_ODR2
#define LCD_EN PC_ODR_ODR3
#define LCD_STA7 PD_IDR_IDR7

void db_set_write()
{
    //GPIO_Init(LCD_DB, GPIO_PIN_ALL, GPIO_MODE_OUT_PP_HIGH_FAST);
    PD_DDR = 0xFF;
    PD_CR1 = 0xFF;
    PD_CR2 = 0xFF;
}

void db_set_read()
{
    /*GPIO_Init(LCD_DB, GPIO_PIN_ALL, GPIO_MODE_IN_PU_NO_IT);*/
    PD_DDR = 0x00;
    PD_CR1 = 0xFF;
    PD_CR2 = 0x00;
}

void lcd_check_busy()
{
    unsigned char bit_status;

    db_set_read();
    LCD_RS = 0;/*GPIO_WriteLow(LCD_CTL, LCD_RS);*/
    LCD_RW = 1;/*GPIO_WriteHigh(LCD_CTL, LCD_RW);*/

    do
    {
        LCD_EN = 1;/*GPIO_WriteHigh(LCD_CTL, LCD_EN);*/
        bit_status = LCD_STA7;/*bit_status = GPIO_ReadInputPin(LCD_DB, LCD_STA7);*/
        LCD_EN = 1;/*GPIO_WriteLow(LCD_CTL, LCD_EN);*/
    } while (bit_status);
}

/**
 *  名称：
 *  功能：向LCD写入命令
 *  参数：
 **/
void lcdWriteCmd(unsigned char cmd)
{
    //lcdWaitReady(); 	//此功能使得E使能端为低电平
    lcd_check_busy();
    LCD_EN = 0;/*GPIO_WriteLow(LCD_CTL, LCD_EN);//LCD1602_E=0;*/
    db_set_write();
    LCD_DB = cmd;/*GPIO_Write(LCD_DB, cmd);//LCD1602_DB=cmd;*/
    LCD_RS = 0;/*GPIO_WriteLow(LCD_CTL, LCD_RS);//LCD1602_RS=0;*/
    LCD_RW = 0;/*GPIO_WriteLow(LCD_CTL, LCD_RW);//LCD1602_RW=0;*/
    LCD_EN = 1;/*GPIO_WriteHigh(LCD_CTL, LCD_EN);//LCD1602_E=1;*/
    LCD_EN = 0;/*GPIO_WriteLow(LCD_CTL, LCD_EN);//LCD1602_E=0;*/
}

/**
 *  名称：
 *  功能：向LCD写入一个字节数据
 *  参数：dat待写入数据
 **/
void lcdWriteDat(unsigned char dat)
{
    //lcdWaitReady(); 	//此功能使得E使能端为低电平
    lcd_check_busy();
    LCD_EN = 0;/*GPIO_WriteLow(LCD_CTL, LCD_EN);//LCD1602_E=0;*/
    db_set_write();
    LCD_DB = dat;/*GPIO_Write(LCD_DB, dat);//LCD1602_DB=dat;*/
    LCD_RS = 1;/*GPIO_WriteHigh(LCD_CTL, LCD_RS);//LCD1602_RS=1;*/
    LCD_RW = 0;/*GPIO_WriteLow(LCD_CTL, LCD_RW);//LCD1602_RW=0;*/
    LCD_EN = 1;/*GPIO_WriteHigh(LCD_CTL, LCD_EN);//LCD1602_E=1;*/
    LCD_EN = 0;/*GPIO_WriteLow(LCD_CTL, LCD_EN);//LCD1602_E=0;*/
}

/**
 *  名称：
 *  功能：设置显示RAM起始地址，即光标位置
 *  参数：x--行数，y--列数
 **/
void lcdSetCursor(unsigned char x, unsigned char y)
{
    u8 addr;

    if (x == 0) //x=0, 表示在第一行显示，地址基数为 0x80 
        addr = 0x80 + y;
    else
        addr = 0xC0 + y;
    lcdWriteCmd(addr); //设置RAM地址
}

/**
 *  名称：
 *  功能：在液晶上显示字符串
 *  参数：x--列数，y--行数，*str--字符串指针
 **/
void lcdShowStr(unsigned char x, unsigned char y,
                unsigned char *str,unsigned char len)
{
    lcdSetCursor(x,y);

    while (len--)
        lcdWriteDat(*str++);  //先取*str，再str++
}	

void write_str(uint8_t addr_start, uint8_t* str)
{
    lcdWriteCmd(addr_start);
    while (*str != '\0')
    {
        lcdWriteDat(*str++);
    }
}

void write_char(uint8_t x, uint8_t y, uint8_t dat)
{
    lcdSetCursor(x, y);
    lcdWriteDat(dat);
}

/**
 *  名称：
 *  功能：初始化LCD1602
 *  参数：
 **/
void initLcd1602()
{
    lcdWriteCmd(0x38); 	//16*2,5*7点阵，8位数据接口
    lcdWriteCmd(0x0c);	//显示器开，光标关闭
    lcdWriteCmd(0x06);	//文字不动，地址自动+1
    lcdWriteCmd(0x01);	//清屏（显示和地址指针）
}

void display_sec(u8 x)
{
    u8 i, j;
    i = x / 10; //取十位
    j = x % 10; //取个位
    write_char(1, 6, i + '0');
    write_char(1, 7, j + '0');
}

void display_min(u8 x)
{
    u8 i, j;
    i = x / 10; //取十位
    j = x % 10; //取个位
    write_char(1, 3, i + '0');
    write_char(1, 4, j + '0');
}

void display_hour(u8 x)
{
    u8 i, j;
    i = x / 10; //取十位
    j = x % 10; //取个位
    write_char(1, 0, i + '0');
    write_char(1, 1, j + '0');
}

void display_day(u8 x)
{
    u8 i, j;
    i = x / 10; //取十位
    j = x % 10; //取个位
    write_char(0, 8, i + '0');
    write_char(0, 9, j + '0');
}

void display_month(u8 x)
{
    u8 i, j;
    i = x / 10; //取十位
    j = x % 10; //取个位
    write_char(0, 5, i + '0');
    write_char(0, 6, j + '0');
}

void display_year(u8 x)
{
    u8 i, j;
    i = x / 10; //取十位
    j = x % 10; //取个位
    write_char(0, 2, i + '0');
    write_char(0, 3, j + '0');
}
void display_week(u8 x)
{
    u8 i, j;
    i = x / 10; //取十位
    j = x % 10; //取个位
    write_char(0, 11, i + '0');
    write_char(0, 12, j + '0');
}

//秒，分，时，日，月，星期，年
void display(DS1302_TIME* time)
{
    write_char(0, 0, '2');
    write_char(0, 1, '0');
    write_char(0, 4, '-');
    write_char(0, 7, '-');
    write_char(0, 10, '|');
    write_char(1, 2, ':');
    write_char(1, 5, ':');

    display_sec(((time->second & 0x70) >> 4) * 10 + (time->second & 0x0F));
    display_min(((time->minute & 0x70) >> 4) * 10 + (time->minute & 0x0F));
    display_hour(((time->hour & 0x10) >> 4) * 10 + (time->hour & 0x0F));
    display_day(((time->day & 0x30) >> 4) * 10 + (time->day & 0x0F));
    display_month(((time->month & 0x10) >> 4) * 10 + (time->month & 0x0F));
    display_week(time->week & 0x07);
    display_year((time->year >> 4) * 10 + (time->year & 0x0F));
}

void main(void)
{
    PC_DDR_DDR1 = 1;
    PC_CR1_C11 = 1;
    PC_CR2_C21 = 1;

    PC_DDR_DDR2 = 1;
    PC_CR1_C12 = 1;
    PC_CR2_C22 = 1;
    
    PC_DDR_DDR3 = 1;
    PC_CR1_C13 = 1;
    PC_CR2_C23 = 1;

    initLcd1602();
    ds1302_init();

    //初始时间20年8月9号14点16分55秒星期天 
    //年 月 日 星期 时 分 秒
    DS1302_TIME start_time;
    /*start_time.year = 0x20;*/
    /*start_time.month = 0x08;*/
    /*start_time.day = 0x09;*/
    /*start_time.week = 0x07;*/
    /*start_time.hour = 0x14;*/
    /*start_time.minute = 0x16;*/
    /*start_time.second = 0x55;*/

    if (!ds1302_is_running()) {
        start_time.year = 20;
        start_time.month = 8;
        start_time.day = 9;
        start_time.week = 7;
        start_time.hour = 8;
        start_time.minute = 3;
        start_time.second = 30;
        ds1302_write_time(&start_time);
    }

    DS1302_TIME current_time;

    while (1)
    {
        ds1302_read_time(&current_time);
        display(&current_time);
    }
}
