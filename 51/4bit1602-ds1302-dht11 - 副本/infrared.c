/* https://blog.csdn.net/qq_42012736/article/details/80555951 */
#include "lcd1602.h"
#include "delay.h"
#include "common.h"
#include "ds1302.h"

extern unsigned int new_value;

sbit IRIN = P3 ^ 3;
unsigned char IrValue[4];//用于存储数据码，对应前两个是地址位，后两个是数据位和校验位
unsigned char ch_count = 0; //两次ch键进入设置的时间计数
bit enter_settings_flag = 0; //进入设置的标志
unsigned short idle_count = 0; //最后一次设置开始空闲计数
unsigned char hex_array[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
  
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
        if (ch_count <= 50) { //500ms之内点击两次ch键为进入设置
            ds1302_pause(1);
            new_value = ds1302_read(DS1302_YEAR_REG);
            ++current_setting;
            enter_settings_flag = 1;
        }
        ch_count = 0;
    } else { //第一次点击ch按钮
        ch_count = 1;  //开始计数
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
    case 1: //年
        if (new_value == 99) {
            new_value = 0;
            return;
        }
        break;
    case 2: //月
        if (new_value == 12) {
            new_value = 1;
            return;
        }
        break;
    case 3: //日
        if (new_value == 31) {
            new_value = 1;
            return;
        }
        break;
    case 4: //星期
        if (new_value == 7) {
            new_value = 1;
            return;
        }
        break;
    case 5: //时
    case 6: //分
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
    case 1: //年
        if (new_value == 0) {
            new_value = 99;
            return;
        }
        break;
    case 2: //月
        if (new_value == 1) {
            new_value = 12;
            return;
        }
        break;
    case 3: //日
        if (new_value == 1) {
            new_value = 31;
            return;
        }
        break;
    case 4: //星期
        if (new_value == 1) {
            new_value = 7;
            return;
        }
        break;
    case 5: //时
    case 6: //分
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
//45 46 47
//44 40 43
//07 15 09
//16 19 0D
//0C 18 5E
//08 1C 5A
//42 52 4A
bit process_irkey()
{
    if (IrValue[2] == 0x46) { //CH 双击进入设置，单击确认（设置的时候暂停ds1302）
        process_ch(); 
    } else if (IrValue[2] == 0x19) { //100+ 背光开关
        lcd_light_back = !lcd_light_back;
    } else if (IrValue[2] == 0x0D) { //200+ beep开关
        beep_setting = !beep_setting;
    } else if (enter_settings_flag) {
        switch (IrValue[2]) {
        case 0x45: //CH－ 前一个设置项
            process_ch_minus();
            break;
        case 0x47: //CH＋ 后一个设置项
            process_ch_plus();
            break;
        case 0x44: //|<< 加10
            break;
        case 0x40: //>>| 减10
            break;
        case 0x43: //>|| 
            break;
        case 0x15: //+ 加1
            process_plus_one();
            break;
        case 0x07: //- 减1
            process_minus_one();
            break;
        case 0x09: //EQ 确认
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
    EA = 1;   //打开总中断

    IRIN = 1;//初始化红外端口
}

void ReadIr() interrupt 2
{
    unsigned char j, k;//循环控制变量
    unsigned int err;
    unsigned char Time = 0;//计时变量，

    EX1 = 0;   //关闭外部中断1,只解码当前红外信号
    Delay7ms();
    if (IRIN == 0)     //确认是否真的接收到正确的信号；与开关消抖类似
    {    
        err = 1000;               //1000*10us=10ms,超过说明接收到错误的信号.
        //这里10ms是大于9ms的，这么做更保险一点，下面的做法类似

        //读取数据的头，即开始信号
        while ((IRIN == 0) && (err > 0))   //等待前面9ms的低电平过去         
        {           
            Delay10us();
            err--;
        } 

        if (IRIN == 1)         //开始信号校验成功      
        {
            err = 500; //500*10us=5ms；
            while ((IRIN == 1) && (err > 0))        //等待4.5ms的起始高电平过去
            {
                Delay10us();
                err--;
            }

            //开始解码
            for (k = 0; k < 4; k++)        //共有4组数据
            {               
                for (j = 0; j < 8; j++)    //接收一组数据
                {
                    err = 60; //校验上限600us 
                    while ((IRIN == 0) && (err > 0))//等待信号前面的560us低电平过去
                    {
                        Delay10us();
                        err--;
                    }

                    err = 500;
                    while ((IRIN == 1) && (err > 0))    //计算高电平的时间长度。
                    {
                        Delay100us();   //0.1ms
                        Time++;
                        err--;
                        if (Time > 30) //超时太久时退出
                        {
                            EX1 = 1; //打开外部中断1
                            return;
                        }
                    }
                    IrValue[k] >>= 1;  //k表示第几组数据
                    if (Time >= 8)         //如果高电平出现大于565us，那么是1
                        //注意这里高电平理论时间长是1680us，低电平的是560us
                        //取Time大于6来检验当然就可以了，但不太保险，网上各类教程都是娶了一个中间值8
                    {
                        IrValue[k] |= 0x80;//在最高为写1，通过按位与运算实现
                        //如果不写默认是0；
                    }
                    Time = 0;     //用完时间要重新赋值                         
                }
            }
        }

        //下面要对数据进行校验，校验的方式位判断第四位数据是否位第三位数据吗的反码
        if (IrValue[2] == ~IrValue[3]) {
            /* display_key_code(); */
            if (process_irkey()) {
                beep_ring_1s();
                idle_count = 1;
            }
        }
    }
    EX1 = 1; //打开外部中断1
}
