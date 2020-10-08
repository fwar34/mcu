#include "stm8s.h"
#include "lcd1602.sdcc.h"
#include "ds1302.sdcc.h"
#include "common.sdcc.h"

extern unsigned char enter_settings_flag;//进入设置的标志
extern unsigned short idle_count;//最后一次设置开始空闲计数

#define DS1302_CLK_PORT GPIOC
#define DS1302_CLK_PIN GPIO_PIN_3

#define DS1302_IO_CE_PORT GPIOD
#define DS1302_IO_PIN GPIO_PIN_0
#define DS1302_RST_PIN GPIO_PIN_2

unsigned int new_value = 0;

void ds1302_init()
{
    GPIO_Init(DS1302_CLK_PORT, DS1302_CLK_PIN, GPIO_MODE_OUT_PP_LOW_FAST);
    GPIO_Init(DS1302_IO_CE_PORT, DS1302_RST_PIN, GPIO_MODE_OUT_PP_LOW_FAST);
}

#define DS1302_CLK_CLR() GPIO_WriteLow(DS1302_CLK_PORT, DS1302_CLK_PIN)
#define DS1302_CLK_SET() GPIO_WriteHigh(DS1302_CLK_PORT, DS1302_CLK_PIN)

#define DS1302_RST_CLR() GPIO_WriteLow(DS1302_IO_CE_PORT, DS1302_RST_PIN)
#define DS1302_RST_SET() GPIO_WriteHigh(DS1302_IO_CE_PORT, DS1302_RST_PIN)

#define DS1302_IO_CLR() GPIO_WriteLow(DS1302_IO_CE_PORT, DS1302_IO_PIN)
#define DS1302_IO_SET() GPIO_WriteHigh(DS1302_IO_CE_PORT, DS1302_IO_PIN)

void ds1302_write_byte(unsigned char dat)
{
    unsigned char i;
    GPIO_Init(DS1302_IO_CE_PORT, DS1302_IO_PIN, GPIO_MODE_OUT_PP_HIGH_FAST);
    for (i = 0;i < 8;i++) {
        DS1302_CLK_CLR();
        if (dat & 0x01) {
            DS1302_IO_SET();
        } else {
            DS1302_IO_CLR();
        }
        DS1302_CLK_SET();
        dat >>= 1;
    }
}

unsigned char ds1302_read_byte()
{
    unsigned char i,ret = 0;
    GPIO_Init(DS1302_IO_CE_PORT, DS1302_IO_PIN, GPIO_MODE_IN_PU_NO_IT);
    for (i = 0;i < 8;i++) {
        DS1302_CLK_CLR();
        ret >>= 1;
        if (GPIO_ReadInputPin(DS1302_IO_CE_PORT, DS1302_IO_PIN)) {
            ret |= 0x80;
        }
        DS1302_CLK_SET();
    }
    return ret;
}

void ds1302_write(unsigned char address, unsigned char dat)
{
    DS1302_RST_CLR();
    DS1302_CLK_CLR();
    DS1302_RST_SET();
    ds1302_write_byte(address);
    ds1302_write_byte(dat);
    DS1302_RST_CLR();
}

/****************************************************************************/
unsigned char ds1302_read(unsigned char address)
{
    unsigned char ret;
    DS1302_RST_CLR();
    DS1302_CLK_CLR();
    DS1302_RST_SET();
    ds1302_write_byte(address | 0x01);//读最低位是1
    ret = ds1302_read_byte();
    DS1302_RST_CLR();
    return ret;
}

unsigned char ds1302_check()
{
    unsigned char ret;
    ds1302_write(DS1302_CONTROL_REG, 0x80);
    ret = ds1302_read(DS1302_CONTROL_REG);
    if (ret == 0x80)
        return 1;
    return 0;
}

unsigned char ds1302_is_running()
{
    unsigned char ret = ds1302_read(DS1302_SEC_REG);
    if (ret & 0x80)
        return 0;
    return 1;
}

void ds1302_read_time(DS1302_TIME* time)
{
    time->year = ds1302_read(DS1302_YEAR_REG);
    time->month = ds1302_read(DS1302_MONTH_REG);
    time->day = ds1302_read(DS1302_DATE_REG);
    time->week = ds1302_read(DS1302_DAY_REG);
    time->hour = ds1302_read(DS1302_HR_REG);
    time->minute = ds1302_read(DS1302_MIN_REG);
    time->second = ds1302_read(DS1302_SEC_REG);
}

//转换成bcd
void ds1302_write_convert(unsigned char addr, unsigned char dat)
{
    ds1302_write(addr, (dat / 10) << 4 | dat % 10);
}

void ds1302_write_time(DS1302_TIME* time)
{
    ds1302_write(DS1302_CONTROL_REG, 0x00);
    ds1302_write(DS1302_SEC_REG, 0x80);
    ds1302_write(DS1302_CHARGER_REG, 0x00);//禁止充电
    ds1302_write_convert(DS1302_YEAR_REG, time->year);
    ds1302_write_convert(DS1302_MONTH_REG, time->month);
    ds1302_write_convert(DS1302_DATE_REG, time->day);
    ds1302_write_convert(DS1302_DAY_REG, time->week);
    ds1302_write_convert(DS1302_HR_REG, time->hour);
    ds1302_write_convert(DS1302_MIN_REG, time->minute);
    ds1302_write_convert(DS1302_SEC_REG, time->second);
    ds1302_write(DS1302_CONTROL_REG, 0x80);
}

void ds1302_write_ram(unsigned char ram_num,unsigned char dat)
{
    ds1302_write(DS1302_CONTROL_REG, 0x00);
    ds1302_write((DS1302_RAM_REG | (ram_num << 2)), dat);
    ds1302_write(DS1302_CONTROL_REG, 0x80);
}

unsigned char ds1302_read_ram(unsigned char ram_num)
{
    unsigned char ret;
    ret = ds1302_read((DS1302_RAM_REG | (ram_num << 2)));
    return ret;
}

char process_time_settings(unsigned char row, unsigned char column)
{
    if (row == 1 && column == 1) {//key1 beep开关
        beep_setting = !beep_setting;
    } else if (row == 2 && column == 1) {//key3 lcd背光开关
        GPIO_WriteReverse(LCD_BK_PORT, LCD_BK_PIN);
    } else {
        return -1;//返回非0表示没有按键按下
    }

    beep_ring_1s();
    return 0;
}

void ds1302_pause(unsigned char flag)
{
    unsigned char second = 0;
    ds1302_write(DS1302_CONTROL_REG, 0x00);//关闭写保护
    second = ds1302_read(DS1302_SEC_REG);
    if (flag)
        ds1302_write(DS1302_SEC_REG, 0x80 | second); //暂停ds1302
    else
        ds1302_write(DS1302_SEC_REG, 0x7F & second); //继续ds1302
    ds1302_write(DS1302_CONTROL_REG, 0x80);//打开写保护
}

void enter_settings()
{
    //设置项闪烁
    switch (current_setting) {
    case 1://年
        flicker_year(new_value);
        break;
    case 2://月
        flicker_month(new_value);
        break;
    case 3://日
        flicker_day(new_value);
        break;
    case 4://星期
        flicker_week(new_value);
        break;
    case 5://时
        flicker_hour(new_value);
        break;
    case 6://分
        flicker_minute(new_value);
        break;
    default:
        return;
    }
}

void exit_settings()
{
    //设置项退出
    idle_count = 0;
    enter_settings_flag = 0;

    if (current_setting > 0 && current_setting < 7)
        ds1302_write(DS1302_CONTROL_REG, 0x00);//关闭写保护

    switch (current_setting) {
    case 1://年
        ds1302_write_convert(DS1302_YEAR_REG, new_value);
        break;
    case 2://月
        ds1302_write_convert(DS1302_MONTH_REG, new_value);
        break;
    case 3://日
        ds1302_write_convert(DS1302_DATE_REG, new_value);
        break;
    case 4://星期
        ds1302_write_convert(DS1302_DAY_REG, new_value);
        break;
    case 5://时
        ds1302_write_convert(DS1302_HR_REG, new_value);
        break;
    case 6://分
        ds1302_write_convert(DS1302_MIN_REG, new_value);
        break;
    default:
        return;
    }

    current_setting = 0;
    ds1302_pause(0);
    ds1302_write(DS1302_CONTROL_REG, 0x80);//打开写保护
}
