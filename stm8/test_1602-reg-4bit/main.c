#include "iostm8s105k4.h"
#include "ds1302.h"
#include "dht11.h"
#include "uart.h"
#include "delay.h"

typedef unsigned char u8;
typedef unsigned char uint8_t;

#define LCD_DB PC_ODR

/*#define LCD_RS PA_ODR_ODR1*/
/*#define LCD_RW PE_ODR_ODR5*/
/*#define LCD_EN PA_ODR_ODR2*/
/*#define LCD_STA7 PC_IDR_IDR7*/

#define LCD_RS PB_ODR_ODR5
#define LCD_RW PE_ODR_ODR5
#define LCD_EN PC_ODR_ODR1
#define LCD_STA7 PC_IDR_IDR7

unsigned char* error_msg = "11 error";
unsigned char* clear_msg = "        ";

void db7_set_write()
{
    PC_DDR |= 0x80;
    PC_CR1 |= 0x80;
    PC_CR2 |= 0x80;
}

void db7_set_read()
{
    PC_DDR &= 0x7F;
    PC_CR1 &= 0x7F;
    PC_CR2 &= 0x7F;
}

void lcd_check_busy()
{
    unsigned char bit_status;

    db7_set_read();
    LCD_RS = 0;/*GPIO_WriteLow(LCD_CTL, LCD_RS);*/
    LCD_RW = 1;/*GPIO_WriteHigh(LCD_CTL, LCD_RW);*/

    do
    {
        LCD_EN = 1;/*GPIO_WriteHigh(LCD_CTL, LCD_EN);*/
        bit_status = LCD_STA7;/*bit_status = GPIO_ReadInputPin(LCD_DB, LCD_STA7);*/
        LCD_EN = 0;/*GPIO_WriteLow(LCD_CTL, LCD_EN);*/
    } while (bit_status);
    db7_set_write();
}

/**
 *  名称：
 *  功能：向LCD写入命令
 *  参数：
 **/
void lcdWriteCmd(unsigned char cmd)
{
    //lcd_check_busy();
    delay_ms(1);
    LCD_EN = 0;/*GPIO_WriteLow(LCD_CTL, LCD_EN);//LCD1602_E=0;*/
    /*LCD_DB = cmd;[>GPIO_Write(LCD_DB, cmd);//LCD1602_DB=cmd;<]*/
    LCD_RS = 0;/*GPIO_WriteLow(LCD_CTL, LCD_RS);//LCD1602_RS=0;*/
    LCD_RW = 0;/*GPIO_WriteLow(LCD_CTL, LCD_RW);//LCD1602_RW=0;*/
    LCD_DB = (LCD_DB & 0x0F) | (cmd & 0xF0);
    LCD_EN = 1;
    LCD_EN = 0;
    LCD_DB = (LCD_DB & 0x0F) | ((cmd << 4) & 0xF0);
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
    /*lcd_check_busy();*/
    delay_ms(1);
    LCD_EN = 0;/*GPIO_WriteLow(LCD_CTL, LCD_EN);//LCD1602_E=0;*/
    LCD_RS = 1;/*GPIO_WriteHigh(LCD_CTL, LCD_RS);//LCD1602_RS=1;*/
    LCD_RW = 0;/*GPIO_WriteLow(LCD_CTL, LCD_RW);//LCD1602_RW=0;*/
    /*LCD_DB = dat;[>GPIO_Write(LCD_DB, dat);//LCD1602_DB=dat;<]*/
    LCD_DB = (LCD_DB & 0x0F) | (dat & 0xF0);
    LCD_EN = 1;
    LCD_EN = 0;
    LCD_DB = (LCD_DB & 0x0F) | ((dat << 4) & 0xF0);
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

/**/
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
    PC_DDR |= 0xFF;                                                                                         ;
    PC_CR1 |= 0xFF;
    PC_CR2 |= 0xFF;
    PC_ODR &= 0xFF;
    
    PB_DDR |= 1 << 5;
    PB_CR1 |= 1 << 5;
    PB_CR2 &= ~(1 << 5);
    
    PE_DDR |= 1 << 5;
    PE_CR1 |= 1 << 5;
    PE_CR2 &= ~(1 << 5);

    /*PC_DDR |= 0xF0;
    PC_CR1 |= 0xF0;
    PC_CR2 |= 0xF0;
    PC_ODR &= 0x0F;*/

    //下面的3个delay函数不能少,少了不显示
    lcdWriteCmd(0x33); 	
    delay_ms(4);
    lcdWriteCmd(0x32); 
    delay_ms(4);
    lcdWriteCmd(0x28); 	//16*2,5*7点阵，4位数据接口
    lcdWriteCmd(0x0c);	//显示器开，光标关闭
    lcdWriteCmd(0x06);	//文字不动，地址自动+1
    lcdWriteCmd(0x01);	//清屏（显示和地址指针）
    delay_ms(200);
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

void display_dht11()
{
    u8 i, j;
    i = dht11_data[0] / 10; //湿度十位
    j = dht11_data[0] % 10; //湿度个位
    write_char(1, 9, i + '0');
    write_char(1, 10, j + '0');
    
    i = dht11_data[2] / 10; //温度十位
    j = dht11_data[2] % 10; //温度个位
    write_char(1, 12, i + '0');
    write_char(1, 13, j + '0');
}

void main(void)
{
    CLK_CKDIVR = 0x00;//HSI 不分频，主时钟 16M
    delay_init(16);

    initLcd1602();
    /*ds1302_init();*/
    
    write_char(0, 10, 'a');

    //初始时间20年8月9号14点16分55秒星期天 
    //年 月 日 星期 时 分 秒
    /*DS1302_TIME start_time;*/
    /*start_time.year = 0x20;*/
    /*start_time.month = 0x08;*/
    /*start_time.day = 0x09;*/
    /*start_time.week = 0x07;*/
    /*start_time.hour = 0x14;*/
    /*start_time.minute = 0x16;*/
    /*start_time.second = 0x55;*/

    //if (!ds1302_is_running()) {

       // DS1302_TIME start_time = {20, 8, 11, 2, 16, 53, 10};
        /*start_time.year = 20;*/
        /*start_time.month = 8;*/
        /*start_time.day = 9;*/
        /*start_time.week = 7;*/
        /*start_time.hour = 8;*/
        /*start_time.minute = 3;*/
        /*start_time.second = 30;*/
       // ds1302_write_time(&start_time);
    //}

    //init TIM4
    /*TIM4_PSCR = 0x07; //128分频 16Mhz/128 = 125k*/
    /*TIM4_IER = 0x01; //更新中断使能*/
    /*TIM4_CNTR = 255; //计数器初值， 255 * （1 / 125) = 0.00204s*/
    /*TIM4_ARR = 255; //自动重装的值*/
    /*asm("rim");*/
    /*TIM4_CR1 |= 0x01;*/

    //DS1302_TIME current_time;

    while (1)
    {
        write_char(1, 11, 'b');
        //ds1302_read_time(&current_time);
        //display(&current_time);
        /*dht11_start();*/
        /*display_dht11();*/
        /*uart_sendhex(dht11_data[0]);*/
        /*uart_sendhex(dht11_data[2]);*/
    }
}

/*#pragma vector=TIM4_OVR_UIF_vector*/
/*__interrupt void TIM4_OVR_UIF_IRQHandler()*/
/*{*/
    /*static unsigned int count = 0;*/
    /*count++;*/
    /*TIM4_SR = 0x00;*/
    /*if (count == 490 * 2)  //2秒*/
    /*{*/
        /*count = 0;*/
        /*dht11_start();*/
        /*if (dht11_check_sum())*/
        /*{*/
            
        /*}*/
        /*else*/
        /*{*/
        /*}*/
        /*display_dht11();*/
    /*}*/
/*}*/
