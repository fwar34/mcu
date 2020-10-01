#include "ds1302.h"
#include "delay.h"

void ds1302_init()
{
    PC_DDR_DDR3 = 1;
    PC_CR1_C13 = 1;
    PC_CR2_C23 = 1;

    PC_DDR_DDR2 = 1;
    PC_CR1_C12 = 1;
    PC_CR2_C22 = 1;

    DS1302_RST_PIN = 0;
    DS1302_CLK_PIN = 0;
}

/*void ds1302_init()*/
/*{*/
    /*PB_DDR_DDR4 = 1;*/
    /*PB_CR1_C14 = 1;*/
    /*PB_CR2_C24 = 1;*/

    /*PB_DDR_DDR6 = 1;*/
    /*PB_CR1_C16 = 1;*/
    /*PB_CR2_C26 = 1;*/

    /*DS1302_RST_PIN = 0;*/
    /*DS1302_CLK_PIN = 0;*/

/*}*/

void read_IO()
{
    PD_DDR_DDR0 = 0;
    PD_CR1_C10 = 0;
    PD_CR2_C20 = 0;
}

void write_IO()
{ 
    PD_DDR_DDR0 = 1;
    PD_CR1_C10 = 1;
    PD_CR2_C20 = 1;
}

/*void read_IO()*/
/*{*/
    /*PB_DDR_DDR5 = 0;*/
    /*PB_CR1_C15 = 0;*/
    /*PB_CR2_C25 = 0;*/
/*}*/

/*void write_IO()*/
/*{ */
    /*PB_DDR_DDR5 = 1;*/
    /*PB_CR1_C15 = 1;*/
    /*PB_CR2_C25 = 1;*/
/*}*/

void ds1302_write_byte(unsigned char dat) 
{
    unsigned char i;
    for (i=0;i<8;i++)     
    { 
        DS1302_CLK_PIN = 0;/*GPIO_LOW(DS1302_PORT,DS1302_CLK_PIN);*/
        if(dat&0x01) {
            DS1302_IO_PIN_OUT = 1;/*GPIO_HIGH(DS1302_PORT,DS1302_IO_PIN); */
        }else {
            DS1302_IO_PIN_OUT = 0;/*GPIO_LOW(DS1302_PORT,DS1302_IO_PIN);*/
        }           
        dat>>=1; 
        DS1302_CLK_PIN = 1;/*GPIO_HIGH(DS1302_PORT,DS1302_CLK_PIN); */
    }
}  

unsigned char ds1302_read_byte(void)
{
    unsigned char i,ret=0;
    for (i=0;i<8;i++)
    {
        DS1302_CLK_PIN = 0;/*GPIO_LOW(DS1302_PORT,DS1302_CLK_PIN);*/
        ret>>=1;
        /*if(GPIO_ReadInputDataBit(DS1302_PORT,DS1302_IO_PIN))*/
        if(DS1302_IO_PIN_IN)
        {
            ret|=0x80;
        }
        DS1302_CLK_PIN = 1;/*GPIO_HIGH(DS1302_PORT,DS1302_CLK_PIN); */
    } 
    return ret;
} 

void ds1302_write( unsigned char address,unsigned char dat )     
{
    write_IO();
    DS1302_RST_PIN = 0;/*GPIO_LOW(DS1302_PORT_RST,DS1302_RST_PIN);   //写地址，写数据 RST保持高电平*/
    DS1302_CLK_PIN = 0;/*GPIO_LOW(DS1302_PORT,DS1302_CLK_PIN);*/
    DS1302_RST_PIN = 1;/*GPIO_HIGH(DS1302_PORT_RST,DS1302_RST_PIN);*/
    ds1302_write_byte(address);
    ds1302_write_byte(dat);
    DS1302_RST_PIN = 0;/*GPIO_LOW(DS1302_PORT_RST,DS1302_RST_PIN);*/
}

/****************************************************************************/
unsigned char ds1302_read( unsigned char address )
{
    unsigned char ret;
    write_IO();
    DS1302_RST_PIN = 0;/*GPIO_LOW(DS1302_PORT_RST,DS1302_RST_PIN);*/
    DS1302_CLK_PIN = 0;/*GPIO_LOW(DS1302_PORT,DS1302_CLK_PIN);*/
    DS1302_RST_PIN = 1;/*GPIO_HIGH(DS1302_PORT_RST,DS1302_RST_PIN);*/
    ds1302_write_byte(address|0x01);  //读标志：地址最后一位为1
    read_IO();
    ret = ds1302_read_byte();
    DS1302_RST_PIN = 0;/*GPIO_LOW(DS1302_PORT_RST,DS1302_RST_PIN);*/
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
