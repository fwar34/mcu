/* https://blog.csdn.net/qq_42012736/article/details/80555951 */
#include "lcd1602.sdcc.h"
#include "delay.sdcc.h"
#include "common.sdcc.h"
#include "ds1302.sdcc.h"
#include "uart_sdcc.h"

#define IRIN P3_3
unsigned char IrValue[4];//用于存储数据码，对应前两个是地址位，后两个是数据位和校验位
unsigned char ch_count = 0;//两次ch键进入设置的时间计数
__bit enter_settings_flag = 0;//进入设置的标志
unsigned short idle_count = 0;//最后一次设置开始空闲计数
unsigned char hex_array[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
unsigned int LowTime, HighTime; //储存高、低电平的宽度 

extern unsigned int new_value;
extern unsigned char ch_count;//两次ch键进入设置的时间计数

void display_current_setting()
{
    write_char(0, 13, current_setting + '0');
}

void display_key_code()
{
    unsigned char i = IrValue[2] / 16;
    unsigned char j = IrValue[2] % 16;
    write_char(0, 14, hex_array[i]);
    write_char(0, 15, hex_array[j]);
}

void read_current_setting()
{
    switch (current_setting) {
    case 1:
        new_value = ds1302_read(DS1302_YEAR_REG);
        return;
    case 2:
        new_value = ds1302_read(DS1302_MONTH_REG);
        return;
    case 3:
        new_value = ds1302_read(DS1302_DATE_REG);
        return;
    case 4:
        new_value = ds1302_read(DS1302_DAY_REG);
        return;
    case 5:
        new_value = ds1302_read(DS1302_HR_REG);
        return;
    case 6:
        new_value = ds1302_read(DS1302_MIN_REG);
        return;
    default:
        return;
    }
}

void process_ch_minus()
{
    if (current_setting) {
        //总共6个设置项
        if (current_setting == 1)
            current_setting = 6;
        else
            --current_setting;
        read_current_setting();
    }
}

void process_ch()
{
    if (ch_count) {
        if (ch_count <= 10) {//500ms之内点击两次ch键为进入设置
            ds1302_pause(1);
            new_value = ds1302_read(DS1302_YEAR_REG);
            ++current_setting;
            enter_settings_flag = 1;
        }
        ch_count = 0;
    } else {//第一次点击ch按钮
        ch_count = 1;//开始计数
    }
}

void process_ch_plus()
{
    if (current_setting == 6)
        current_setting = 1;
    else
        ++current_setting;
    read_current_setting();
}

void process_plus_one()
{
    switch (current_setting) {
    case 1://年
        if (new_value == 99) {
            new_value = 0;
            return;
        }
        break;
    case 2://月
        if (new_value == 12) {
            new_value = 1;
            return;
        }
        break;
    case 3://日
        if (new_value == 31) {
            new_value = 1;
            return;
        }
        break;
    case 4://星期
        if (new_value == 7) {
            new_value = 1;
            return;
        }
        break;
    case 5://时
    case 6://分
        if (new_value == 59) {
            new_value = 0;
            return;
        }
        break;
    default:
        return;
    }
    ++new_value;
}

void process_minus_one()
{
    switch (current_setting) {
    case 1://年
        if (new_value == 0) {
            new_value = 99;
            return;
        }
        break;
    case 2://月
        if (new_value == 1) {
            new_value = 12;
            return;
        }
        break;
    case 3://日
        if (new_value == 1) {
            new_value = 31;
            return;
        }
        break;
    case 4://星期
        if (new_value == 1) {
            new_value = 7;
            return;
        }
        break;
    case 5://时
    case 6://分
        if (new_value == 0) {
            new_value = 59;
            return;
        }
        break;
    default:
        return;
    }
    --new_value;
}

void process_confirm()
{
    exit_settings();
}

//遥控器编码十六进制
//0x45 0x46 0x47
//0x44 0x40 0x43
//0x07 0x15 0x09
//0x16 0x19 0x0D
//0x0C 0x18 0x5E
//0x08 0x1C 0x5A
//0x42 0x52 0x4A
__bit process_irkey()
{
    if (IrValue[2] == 0x46) {//CH 双击进入设置，单击确认（设置的时候暂停ds1302）
        process_ch();
    } else if (IrValue[2] == 0x19) {//100+ 背光开关
        lcd_light_back = !lcd_light_back;
    } else if (IrValue[2] == 0x0D) {//200+ beep开关
        beep_setting = !beep_setting;
    } else if (enter_settings_flag) {
        switch (IrValue[2]) {
        case 0x45://CH－ 前一个设置项
            process_ch_minus();
            break;
        case 0x47://CH＋ 后一个设置项
            process_ch_plus();
            break;
        case 0x44://|<< 加10
            break;
        case 0x40://>>| 减10
            break;
        case 0x43://>|| 
            break;
        case 0x15://+ 加1
            process_plus_one();
            break;
        case 0x07://- 减1
            process_minus_one();
            break;
        case 0x09://EQ 确认
            process_confirm();
            break;
        default:
            return 0;
        }
        return 1;
    } else {
        return 0;
    }
    return 1;
}

void IrInit()
{
    IT1 = 1;//下降沿触发
    EX1 = 1;//打开中断1允许
    EA = 1;//打开总中断

    IRIN = 1;//初始化红外端口
}

/* __bit DeCode(void) */
/* { */
/*     unsigned char i,j; */
/*     unsigned char temp = 0;    //储存解码出的数据 */
/*     for(i=0;i<4;i++)      //连续读取4个用户码和键数据码 */
/*     { */
/*         for(j=0;j<8;j++)  //每个码有8位数字 */
/*         { */
/*             temp=temp>>1;  //temp中的各数据位右移一位，因为先读出的是高位数据 */
/*             T3H=0;         //定时器清0 */
/*             T3L=0;         //定时器清0 */
/*             T4T3M |= 0x08;         //开启定时器T0 */
/*             while(IRIN==0) { //如果是低电平就等待 //低电平计时 */
/*                 if (T3H > 0xEE) {//时间过长的话退出循环 */
/*                     EX1=1;       */
/*                     T4T3M &= 0xF7;    //开启定时器T1 */
/*                     /\* UART_send_string("ir err3"); *\/ */
/*                     return 0; */
/*                 } */
/*             } */
/*             T4T3M &= 0xF7;         //关闭定时器T0 */
/*             LowTime=T3H*256+T3L;    //保存低电平宽度 */
/*             T3H=0;         //定时器清0 */
/*             T3L=0;         //定时器清0 */
/*             T4T3M |= 0x08;         //开启定时器T0 */
/*             while(IRIN==1)   //如果是高电平就等待 */
/*             { */
/*                 if (T3H > 0xEE) {//时间过长的话退出循环 */
/*                     EX1=1;       */
/*                     T4T3M &= 0xF7;    //开启定时器T1 */
/*                     /\* UART_send_string("ir err4"); *\/ */
/*                     return 0; */
/*                 } */
/*             }; */
/*             T4T3M &= 0xF7;        //关闭定时器T0 */
/*             HighTime=T3H*256+T3L;   //保存高电平宽度 */
/*             if((LowTime<370)||(LowTime>640)) */
/*                 return 0;        //如果低电平长度不在合理范围，则认为出错，停止解码 */
/*             if((HighTime>420)&&(HighTime<620))   //如果高电平时间在560微秒左右，即计数560／1.085＝516次 */
/*                 temp=temp&0x7f;       //(520-100=420, 520+100=620)，则该位是0 */
/*             if((HighTime>1300)&&(HighTime<1800)) //如果高电平时间在1680微秒左右，即计数1680／1.085＝1548次 */
/*                 temp=temp|0x80;       //(1550-250=1300,1550+250=1800),则该位是1 */
/*         } */
/*         IrValue[i]=temp;//将解码出的字节值保存在a[i] */
/*     } */
/*     if(IrValue[2]=~IrValue[3])  //验证键数据码和其反码是否相等,一般情况下不必验证用户码 */
/*     { */
/*         return 1;     //解码正确，返回1 */
/*     } */
/*     return 0; */
/* } */

/* void ReadIr() __interrupt 2 */
/* { */
/*     EX1=0;      //关闭外中断1，不再接收二次红外信号的中断，只解码当前红外信号 */

/*     T4T3M &= 0xF7; */
/*     T3H=0;      //定时器T1的高8位清0 */
/*     T3L=0;      //定时器T1的低8位清0 */
/*     T4T3M |= 0x08;    //开启定时器T1 */
/*     while(IRIN==0) { //如果是低电平就等待，给引导码低电平计时 */
/*         if (T3H > 0xEE) {//时间过长的话退出循环 */
/*             EX1=1; */
/*             T4T3M &= 0xF7; */
/*             /\* UART_send_string("ir err1"); *\/ */
/*             return; */
/*         } */
/*     };           */

/*     T4T3M &= 0xF7;                //关闭定时器T1 */
/*     LowTime=T3H*256+T3L;  //保存低电平时间 */
/*     T3H=0;      //定时器T1的高8位清0 */
/*     T3L=0;      //定时器T1的低8位清0 */
/*     T4T3M |= 0x08;    //开启定时器T1 */

/*     while(IRIN==1) { //如果是高电平就等待，给引导码高电平计时 */
/*         if (T3H > 0xEE) {//时间过长的话退出循环 */
/*             EX1=1; */
/*             T4T3M &= 0xF7;    //开启定时器T1 */
/*             /\* UART_send_string("ir err2"); *\/ */
/*             return; */
/*         } */
/*     };   */
/*     T4T3M &= 0xF7;        //关闭定时器T1 */
/*     HighTime=T3H*256+T3L;//保存引导码的高电平长度 */

/*     if((LowTime>7800)&&(LowTime<8800)&&(HighTime>3600)&&(HighTime<4700)) */
/*     { */
/*         //如果是引导码,就开始解码,否则放弃,引导码的低电平计时 */
/*         //次数＝9000us/1.085=8294, 判断区间:8300－500＝7800，8300＋500＝8800. */
/*         if(DeCode()==1) // 执行遥控解码功能 */
/*         { */
/*             /\* Disp();//调用1602LCD显示函数 *\/ */
/*             process_irkey(); */
/*             enter_settings(); */
/*             display_current_setting(); */

/*             UART_send_byte(IrValue[2]); */
/*             led = !led; */
/*         } */
/*     } */
/*     EX1=1;   //开启外中断EX1 */
/* } */

__bit DeCode(void)
{
    unsigned char i,j;
    unsigned char temp = 0;    //储存解码出的数据
    for(i=0;i<4;i++)      //连续读取4个用户码和键数据码
    {
        for(j=0;j<8;j++)  //每个码有8位数字
        {
            temp=temp>>1;  //temp中的各数据位右移一位，因为先读出的是高位数据
            T3H=0;         //定时器清0
            T3L=0;         //定时器清0
            T4T3M |= 0x08;         //开启定时器T0
            while(IRIN==0) { //如果是低电平就等待 //低电平计时
                if (T3H > 0xEE) {//时间过长的话退出循环
                    EX1=1;      
                    T4T3M &= 0xF7;    //开启定时器T1
                    UART_send_string("ir err3");
                    return 0;
                }
            }
            T4T3M &= 0xF7;         //关闭定时器T0
            LowTime=T3H*256+T3L;    //保存低电平宽度
            T3H=0;         //定时器清0
            T3L=0;         //定时器清0
            T4T3M |= 0x08;         //开启定时器T0
            while(IRIN==1)   //如果是高电平就等待
            {
                if (T3H > 0xEE) {//时间过长的话退出循环
                    EX1=1;      
                    T4T3M &= 0xF7;    //开启定时器T1
                    UART_send_string("ir err4");
                    return 0;
                }
            };
            T4T3M &= 0xF7;        //关闭定时器T0
            HighTime=T3H*256+T3L;   //保存高电平宽度
            if((LowTime<370)||(LowTime>640))
                return 0;        //如果低电平长度不在合理范围，则认为出错，停止解码
            if((HighTime>420)&&(HighTime<620))   //如果高电平时间在560微秒左右，即计数560／1.085＝516次
                temp=temp&0x7f;       //(520-100=420, 520+100=620)，则该位是0
            if((HighTime>1300)&&(HighTime<1800)) //如果高电平时间在1680微秒左右，即计数1680／1.085＝1548次
                temp=temp|0x80;       //(1550-250=1300,1550+250=1800),则该位是1
        }
        IrValue[i]=temp;//将解码出的字节值保存在a[i]
    }
    if(IrValue[2]=~IrValue[3])  //验证键数据码和其反码是否相等,一般情况下不必验证用户码
    {
        return 1;     //解码正确，返回1
    }
    return 0;
}

void ReadIr() __interrupt 2
{
    EX1=0;      //关闭外中断1，不再接收二次红外信号的中断，只解码当前红外信号

    T4T3M &= 0xF7;
    T3H=0;      //定时器T1的高8位清0
    T3L=0;      //定时器T1的低8位清0
    T4T3M |= 0x08;    //开启定时器T1
    while(IRIN==0) { //如果是低电平就等待，给引导码低电平计时
        if (T3H > 0xEE) {//时间过长的话退出循环
            EX1=1;
            T4T3M &= 0xF7;
            UART_send_string("ir err1");
            return;
        }
    };          

    T4T3M &= 0xF7;                //关闭定时器T1
    LowTime=T3H*256+T3L;  //保存低电平时间
    T3H=0;      //定时器T1的高8位清0
    T3L=0;      //定时器T1的低8位清0
    T4T3M |= 0x08;    //开启定时器T1

    while(IRIN==1) { //如果是高电平就等待，给引导码高电平计时
        if (T3H > 0xEE) {//时间过长的话退出循环
            EX1=1;
            T4T3M &= 0xF7;    //关闭定时器T1
            UART_send_string("ir err2");
            return;
        }
    };  
    T4T3M &= 0xF7;        //关闭定时器T1
    HighTime=T3H*256+T3L;//保存引导码的高电平长度

    if((LowTime>7800)&&(LowTime<8800)&&(HighTime>3600)&&(HighTime<4700))
    {
        //如果是引导码,就开始解码,否则放弃,引导码的低电平计时
        //次数＝9000us/1.085=8294, 判断区间:8300－500＝7800，8300＋500＝8800.
        if(DeCode()==1) // 执行遥控解码功能
        {
            /* Disp();//调用1602LCD显示函数 */
            process_irkey();
            enter_settings();
            display_current_setting();

            UART_send_byte(IrValue[2]);
            led = !led;
        }
    }
    EX1=1;   //开启外中断EX1
}
