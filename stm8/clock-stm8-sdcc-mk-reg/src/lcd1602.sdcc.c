#include "delay.h"
#include "lcd1602.sdcc.h"
#include "common.sdcc.h"
#include "uart_sdcc.h"

#define LCD_DB_PORT PC_ODR

#define LCD_RS_PIN PB_ODR_ODR5
#define LCD_EN_PIN PC_ODR_ODR1
#define LCD_RW_PIN PE_ODR_ODR5
#define CLR_EN() LCD_EN_PIN = 0
#define SET_EN() LCD_EN_PIN = 1
#define CLR_RS() LCD_RS_PIN = 0
#define SET_RS() LCD_RS_PIN = 1

extern unsigned char dht11_data[5];//湿度十位，湿度个位，温度十位，温度个位，是否更新显示的标志

/* void lcd_check_busy() */
/* { */
/*     unsigned char bit_status; */

/*     GPIO_Init(LCD_DB_PORT, LCD_DB7_PIN, GPIO_MODE_IN_PU_NO_IT); */
/*     GPIO_WriteLow(LCD_RS_PORT, LCD_RS_PIN); */
/*     GPIO_WriteHigh(LCD_RW_PORT, LCD_RW_PIN); */

/*     do */
/*     { */
/*         GPIO_WriteHigh(LCD_EN_PORT, LCD_EN_PIN); */
/*         bit_status = GPIO_ReadInputPin(LCD_DB_PORT, LCD_DB7_PIN); */
/*         GPIO_WriteLow(LCD_EN_PORT, LCD_EN_PIN); */
/*     } while (bit_status); */
/*     GPIO_Init(LCD_DB_PORT, LCD_DB7_PIN, GPIO_MODE_OUT_PP_LOW_FAST); */
/* } */

void lcdWriteCmd(unsigned char cmd)
{
    /* lcd_check_busy(); */
    delay_ms(2);
    CLR_EN();
    CLR_RS();
    /* GPIO_WriteLow(LCD_RW_PORT, LCD_RW_PIN); */
    /* LCD_RW = 0; */
    LCD_DB_PORT = (LCD_DB_PORT & 0x0F) | (cmd & 0xF0);
    SET_EN();
    CLR_EN();
    LCD_DB_PORT = (LCD_DB_PORT & 0x0F) | (cmd << 4);
    SET_EN();
    CLR_EN();
}

void lcdWriteDat(unsigned char dat)
{
    /* lcd_check_busy(); */
    delay_ms(2);
    CLR_EN();
    SET_RS();
    /* GPIO_WriteLow(LCD_RW_PORT, LCD_RW_PIN); */
    /* LCD_RW = 0; */
    LCD_DB_PORT = (LCD_DB_PORT & 0x0F) | (dat & 0xF0);
    SET_EN();
    CLR_EN();
    LCD_DB_PORT = (LCD_DB_PORT & 0x0F) | (dat << 4);
    SET_EN();
    CLR_EN();
}

void lcdSetCursor(unsigned char x, unsigned char y)
{
    unsigned char addr;

    if (x == 0)
        addr = 0x80 + y;
    else
        addr = 0xC0 + y;
    lcdWriteCmd(addr);
}

/**/
void lcdShowStr(unsigned char x, unsigned char y, unsigned char *str, unsigned char len)
{
    lcdSetCursor(x, y);

    while (len--)
        lcdWriteDat(*str++);
}

void write_str(unsigned char addr_start, unsigned char* str)
{
    lcdWriteCmd(addr_start);
    while (*str != '\0')
    {
        lcdWriteDat(*str++);
    }
}

void write_char(unsigned char x, unsigned char y, unsigned char dat)
{
    lcdSetCursor(x, y);
    lcdWriteDat(dat);
}

void lcd1602_init()
{
    //RST
    PB_DDR_DDR5 = 1;
    PB_CR1_C15 = 1;
    PB_CR2_C25 = 0;
    PB_ODR_ODR5 = 0;

    //RW
    PE_DDR_DDR5 = 1;
    PE_CR1_C15 = 1;
    PE_CR2_C25 = 0;
    PE_ODR_ODR5 = 0;

    PC_DDR |= (MASK_PC_DDR_DDR1 | MASK_PC_DDR_DDR2 | MASK_PC_DDR_DDR4 | MASK_PC_DDR_DDR5 | MASK_PC_DDR_DDR6 | MASK_PC_DDR_DDR7);
    PC_CR1 |= (MASK_PC_CR1_C11 | MASK_PC_CR1_C12 | MASK_PC_CR1_C14 | MASK_PC_CR1_C15 | MASK_PC_CR1_C16 | MASK_PC_CR1_C17);
    PC_CR2 &= ~(MASK_PC_CR2_C21 | MASK_PC_CR2_C22 | MASK_PC_CR2_C24 | MASK_PC_CR2_C25 | MASK_PC_CR2_C26 | MASK_PC_CR2_C27);

    LCD_BK_PIN = 0;  //初始化打开背光
    //下面的3个delay函数不能少,少了不显示
    lcdWriteCmd(0x33);
    delay_ms(4);
    lcdWriteCmd(0x32);
    delay_ms(4);
    lcdWriteCmd(0x28);    //16*2,5*7点阵，4位数据接口
    lcdWriteCmd(0x0c);    //显示器开，光标关闭
    lcdWriteCmd(0x06);    //文字不动，地址自动+1
    lcdWriteCmd(0x01);    //清屏（显示和地址指针）
    delay_ms(200);
}

void wait_for_dht11()
{
    unsigned char i;
    for (i = 0; i < 16; ++i) {
        write_char(0, i, '>');
        delay_ms(50);
    }

    i = 15;
    while (i--) {
        write_char(1, i, '<');
        delay_ms(50);
    }

    delay_ms(300);

    /* for (i = 15; i >= 0; --i) { */
    /*     write_char(1, i, '<'); */
    /*     delay_ms(50); */
    /* } */
}

//--------------------------------------------------------------------------
void display_sec(unsigned char x)
{
    unsigned char i, j;
    i = x / 10;//取十位
    j = x % 10;//取个位
    write_char(1, 6, i + '0');
    write_char(1, 7, j + '0');
}

void display_min(unsigned char x)
{
    unsigned char i, j;
    i = x / 10;//取十位
    j = x % 10;//取个位
    write_char(1, 3, i + '0');
    write_char(1, 4, j + '0');
}

void flicker_minute(unsigned char x)
{
    write_char(1, 3, ' ');
    write_char(1, 4, ' ');
    delay_ms(500);
    display_min(((x & 0x70) >> 4) * 10 + (x & 0x0F));
    delay_ms(500);
}

void display_hour(unsigned char x)
{
    unsigned char i, j;
    i = x / 10;//取十位
    j = x % 10;//取个位
    write_char(1, 0, i + '0');
    write_char(1, 1, j + '0');
}

void flicker_hour(unsigned char x)
{
    write_char(1, 0, ' ');
    write_char(1, 1, ' ');
    delay_ms(500);
    display_hour(((x & 0x30) >> 4) * 10 + (x & 0x0F));
    delay_ms(500);
}

void display_day(unsigned char x)
{
    unsigned char i, j;
    i = x / 10;//取十位
    j = x % 10;//取个位
    write_char(0, 8, i + '0');
    write_char(0, 9, j + '0');
}

void flicker_day(unsigned char x)
{
    write_char(0, 8, ' ');
    write_char(0, 9, ' ');
    delay_ms(500);
    display_day(((x & 0x30) >> 4) * 10 + (x & 0x0F));
    delay_ms(500);
}

void display_month(unsigned char x)
{
    unsigned char i, j;
    i = x / 10;//取十位
    j = x % 10;//取个位
    write_char(0, 5, i + '0');
    write_char(0, 6, j + '0');
}

void flicker_month(unsigned char x)
{
    write_char(0, 5, ' ');
    write_char(0, 6, ' ');
    delay_ms(500);
    display_month(((x & 0x10) >> 4) * 10 + (x & 0x0F));
    delay_ms(500);
}

void display_year(unsigned char x)
{
    unsigned char i, j;
    i = x / 10;//取十位
    j = x % 10;//取个位
    write_char(0, 2, i + '0');
    write_char(0, 3, j + '0');
}

void flicker_year(unsigned char x)
{
    write_char(0, 0, ' ');
    write_char(0, 1, ' ');
    write_char(0, 2, ' ');
    write_char(0, 3, ' ');
    delay_ms(500);
    write_char(0, 0, '2');
    write_char(0, 1, '0');
    display_year((x >> 4) * 10 + (x & 0x0F));
    delay_ms(500);
}

void display_week(unsigned char x)
{
    unsigned char i, j;
    i = x / 10;//取十位
    j = x % 10;//取个位
    write_char(0, 11, i + '0');
    write_char(0, 12, j + '0');
}

void flicker_week(unsigned char x)
{
    write_char(0, 11, ' ');
    write_char(0, 12, ' ');
    delay_ms(500);
    display_week(x & 0x07);
    delay_ms(500);
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
    display_hour(((time->hour & 0x30) >> 4) * 10 + (time->hour & 0x0F));
    display_day(((time->day & 0x30) >> 4) * 10 + (time->day & 0x0F));
    display_month(((time->month & 0x10) >> 4) * 10 + (time->month & 0x0F));
    display_week(time->week & 0x07);
    display_year((time->year >> 4) * 10 + (time->year & 0x0F));
}

void display_dht11()
{
    unsigned char i, j;
    /* UART_send_byte(dht11_data[4]); */
    //dht11因为2秒钟才读一次，所以只需要2秒钟更新下显示就行
    if (dht11_data[4]) {
        dht11_data[4] = 0;//清除dht11显示标志

        i = dht11_data[0] / 10;//湿度十位
        j = dht11_data[0] % 10;//湿度个位
        write_char(1, 9, i + '0');
        write_char(1, 10, j + '0');
        write_char(1, 11, '%');
        write_char(1, 12, ' ');
        /* uart_send_string("wendu:"); */
        /* uart_send_hex(dht11_data[0]); */
    
        i = dht11_data[2] / 10;//温度十位
        j = dht11_data[2] % 10;//温度个位
        write_char(1, 13, i + '0');
        write_char(1, 14, j + '0');
        write_char(1, 15, 'C');
        /* uart_send_string("shidu:"); */
        /* uart_send_hex(dht11_data[2]); */
    }
}
