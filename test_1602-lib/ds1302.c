#include "ds1302.h"

void ds1302_init()
{
    GPIO_Init(DS1302_CTL, DS1302_CLK_PIN, GPIO_MODE_OUT_PP_LOW_FAST);

    /*PB_DDR_DDR2 = 1;*/
    /*PB_CR1_C12 = 1;*/
    /*PB_CR2_C22 = 1;*/
    GPIO_Init(DS1302_CTL, DS1302_RST_PIN, GPIO_MODE_OUT_PP_LOW_FAST);

    /*PB_DDR_DDR1 = 0;*/
    /*PB_CR1_C11 = 0;*/
    /*PB_CR2_C21 = 0;*/


    /*DS1302_RST_PIN = 0;*/
    /*DS1302_CLK_PIN = 0;*/

}

void read_IO()
{
    GPIO_Init(DS1302_CTL, DS1302_IO_PIN, GPIO_MODE_IN_FL_NO_IT);
    /*PB_DDR_DDR1 = 0;*/
    /*PB_CR1_C11 = 0;*/
    /*PB_CR2_C21 = 0;*/
}

void write_IO()
{ 
    GPIO_Init(DS1302_CTL, DS1302_IO_PIN, GPIO_MODE_OUT_PP_LOW_FAST);
    /*PB_DDR_DDR1 = 1;*/
    /*PB_CR1_C11 = 1;*/
    /*PB_CR2_C21 = 1;*/
}

void ds1302_write_byte(unsigned char dat) 
{
    unsigned char i;
    for (i=0;i<8;i++)     
    { 
        GPIO_WriteLow(DS1302_CTL,DS1302_CLK_PIN);//DS1302_CLK_PIN = 0;
        if(dat&0x01) {
            GPIO_WriteHigh(DS1302_CTL,DS1302_IO_PIN);//DS1302_IO_PIN_OUT = 1;
        }else {
            GPIO_WriteLow(DS1302_CTL,DS1302_IO_PIN);//DS1302_IO_PIN_OUT = 0;
        }           
        dat>>=1; 
        GPIO_WriteHigh(DS1302_CTL,DS1302_CLK_PIN);//DS1302_CLK_PIN = 1;
    }
}  

unsigned char ds1302_read_byte(void)
{
    unsigned char i,ret=0;
    for (i=0;i<8;i++)
    {
        GPIO_WriteLow(DS1302_CTL,DS1302_CLK_PIN);//DS1302_CLK_PIN = 0;
        ret>>=1;
        if(GPIO_ReadInputPin(DS1302_CTL,DS1302_IO_PIN))
        /*if(DS1302_IO_PIN_IN)*/
        {
            ret|=0x80;
        }
        GPIO_WriteHigh(DS1302_CTL,DS1302_CLK_PIN);//DS1302_CLK_PIN = 1;
    } 
    return ret;
} 

void ds1302_write( unsigned char address,unsigned char dat )     
{
    write_IO();
    GPIO_WriteLow(DS1302_CTL,DS1302_RST_PIN);   //写地址，写数据 RST保持高电平*///DS1302_RST_PIN = 0;
    GPIO_WriteLow(DS1302_CTL,DS1302_CLK_PIN);//DS1302_CLK_PIN = 0;
    GPIO_WriteHigh(DS1302_CTL,DS1302_RST_PIN);//DS1302_RST_PIN = 1;
    ds1302_write_byte(address);
    ds1302_write_byte(dat);
    GPIO_WriteLow(DS1302_CTL,DS1302_RST_PIN);//DS1302_RST_PIN = 0;
}

/****************************************************************************/
unsigned char ds1302_read( unsigned char address )
{
    unsigned char ret;
    write_IO();
    GPIO_WriteLow(DS1302_CTL,DS1302_RST_PIN);//DS1302_RST_PIN = 0;
    GPIO_WriteLow(DS1302_CTL,DS1302_CLK_PIN);//DS1302_CLK_PIN = 0;
    GPIO_WriteHigh(DS1302_CTL,DS1302_RST_PIN);//DS1302_RST_PIN = 1;
    ds1302_write_byte(address|0x01);  //读标志：地址最后一位为1
    read_IO();
    ret = ds1302_read_byte();
    GPIO_WriteLow(DS1302_CTL,DS1302_RST_PIN);//DS1302_RST_PIN = 0;
    return ret;
}

unsigned char ds1302_check() 
{ 
    unsigned char ret;
    ds1302_write(DS1302_CONTROL_REG,0x80); 
    ret = ds1302_read(DS1302_CONTROL_REG);
    if(ret==0x80)
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
    time->year=ds1302_read(DS1302_YEAR_REG); //年 
    time->month=ds1302_read(DS1302_MONTH_REG);//月 
    time->day=ds1302_read(DS1302_DATE_REG); //日 
    time->week=ds1302_read(DS1302_DAY_REG); //周 
    time->hour=ds1302_read(DS1302_HR_REG); //时 
    time->minute=ds1302_read(DS1302_MIN_REG); //分 
    time->second=ds1302_read(DS1302_SEC_REG); //秒 
}

//将10进制转成bcd码
void ds1302_write_convert(unsigned char addr, unsigned char dat)
{
    ds1302_write(addr, (dat / 10) << 4 | dat % 10);
}

void ds1302_write_time(DS1302_TIME* time) 
{ 
    ds1302_write(DS1302_CONTROL_REG,0x00); //关闭写保护 
    ds1302_write(DS1302_SEC_REG,0x80); //暂停 
    ds1302_write(DS1302_CHARGER_REG,0xa9); //涓流充电 
    ds1302_write_convert(DS1302_YEAR_REG,time->year); //年 
    ds1302_write_convert(DS1302_MONTH_REG,time->month); //月 
    ds1302_write_convert(DS1302_DATE_REG,time->day); //日 
    ds1302_write_convert(DS1302_DAY_REG,time->week); //周 
    ds1302_write_convert(DS1302_HR_REG,time->hour); //时 
    ds1302_write_convert(DS1302_MIN_REG,time->minute); //分 
    ds1302_write_convert(DS1302_SEC_REG,time->second); //秒 
    ds1302_write(DS1302_CONTROL_REG,0x80); //打开写保护 
}

void ds1302_write_ram(unsigned char ram_num,unsigned char dat) 
{ 
    ds1302_write(DS1302_CONTROL_REG,0x00); //关闭写保护 
    ds1302_write((DS1302_RAM_REG|(ram_num<<2)),dat);
    ds1302_write(DS1302_CONTROL_REG,0x80);
}

unsigned char  ds1302_read_ram(unsigned char ram_num) 
{ 
    unsigned char ret;
    ret = ds1302_read((DS1302_RAM_REG|(ram_num<<2)));
    return ret;
}
