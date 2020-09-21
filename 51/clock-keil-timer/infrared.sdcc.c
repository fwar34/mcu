/* https://blog.csdn.net/qq_42012736/article/details/80555951 */
#include "lcd1602.sdcc.h"
#include "delay.sdcc.h"
#include "common.sdcc.h"
#include "ds1302.sdcc.h"
#include "uart_sdcc.h"
#include "infrared.sdcc.h"

extern unsigned int new_value;

sbit leddd = P0 ^ 5;

sbit IRIN = P3 ^ 3;
unsigned char IrValue[4];//用于存储数据码，对应前两个是地址位，后两个是数据位和校验位
unsigned char ch_count = 0;//两次ch键进入设置的时间计数
bit enter_settings_flag = 0;//进入设置的标志
unsigned short idle_count = 0;//最后一次设置开始空闲计数
unsigned char hex_array[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
unsigned int LowTime, HighTime; //储存高、低电平的宽度 
  
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
        if (ch_count <= 50) {//500ms之内点击两次ch键为进入设置
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
//45 46 47
//44 40 43
//07 15 09
//16 19 0D
//0C 18 5E
//08 1C 5A
//42 52 4A
bit process_irkey()
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

#if 0
/* void ReadIr() __interrupt(2) 也可以*/
void ReadIr() interrupt 2
{  
    unsigned char j, k;//循环控制变量
    unsigned int duration; //计时变量

    //UART_send_string("ir ReadIr");
    EX1 = 0;//关闭外部中断1,只解码当前红外信号
    /* Delay7ms(); */
    TH1 = 0;
    TL1 = 0;
    TR1 = 1;
    //while (TH1 * 256 + TL1 < 6451); //1.085 * 6451 = 7ms

    if (IRIN == 0)//确认是否真的接收到正确的信号；与开关消抖类似
    {
        //读取数据的头，开始信号
        while (IRIN == 0)//等待前面9ms的低电平过去         
        {
            //10ms还是低电平就退出
            //超过说明接收到错误的信号.
            //这里10ms是大于9ms的，这么做更保险一点，下面的做法类似
            if (TH1 * 256 + TL1 > 9216) { //10ms
                TR1 = 0;
                EX1 = 1;//打开外部中断1
                UART_send_string("ir error1");
                return;
            }
        }

        //开始信号校验成功      
        TH1 = 0;
        TL1 = 0;
        while (IRIN == 1)//等待4.5ms的起始高电平过去
        {
            if (TH1 * 256 + TL1 > 5000) { //5ms还是高电平就退出
                TR1 = 0;
                EX1 = 1;//打开外部中断1
                UART_send_string("ir error2");
                return;
            }
        }

        //开始解码
        for (k = 0; k < 4; k++)//共有4组数据
        {
            for (j = 0; j < 8; j++)//接收一组数据
            {
                TH1 = 0;
                TL1 = 0;
                while (IRIN == 0)//等待信号前面的560us低电平过去
                {
                    if (TH1 * 256 + TL1 > /*553*/921) { //600us还是低电平就退出
                        TR1 = 0;
                        EX1 = 1;//打开外部中断1
                        UART_send_string("ir error3");
                        return;
                    }
                }

                TH1 = 0;
                TL1 = 0;
                while (IRIN == 1)//计算高电平的时间长度。
                {
                    if (TH1 * 256 + TL1 > /*1843*/2119) { //高电平大于2ms就退出
                        TR1 = 0;
                        EX1 = 1;//打开外部中断1
                        UART_send_string("ir error4");
                        break;
                    }
                }
                TR1 = 0;
                duration = TH1 * 256 + TL1;
                /* UART_send_byte(0xAA); */
                /* UART_send_byte(TH1); */
                /* UART_send_byte(TL1); */
                /* UART_send_byte(0xBB); */
                
                IrValue[k] >>= 1;//k表示第几组数据
                if (duration >= 737)//如果高电平出现大于800us，那么是1
                                    //注意这里高电平理论时间长是1680us，低电平的是560us
                                    //大于600us来检验当然就可以了，但不太保险，网上各类教程都是娶了一个中间值800us
                {
                    IrValue[k] |= 0x80;//在最高为写1，通过按位与运算实现
                    //如果不写默认是0；
                }
                TR1 = 1;
            }
        }

        //下面要对数据进行校验，校验的方式位判断第四位数据是否位第三位数据码的反码
        if (IrValue[2] == ~IrValue[3]) {
            /* display_key_code(); */
            if (process_irkey()) {
                //beep_ring_1s();
                idle_count = 1;
                leddd = !leddd;
            }
        }
    }

    TR1 = 0;
    EX1 = 1;//打开外部中断1
}
#endif

bit DeCode(void)
{
    unsigned char i,j;
    unsigned char temp = 0;    //储存解码出的数据
    for(i=0;i<4;i++)      //连续读取4个用户码和键数据码
    {
        for(j=0;j<8;j++)  //每个码有8位数字
        {
            temp=temp>>1;  //temp中的各数据位右移一位，因为先读出的是高位数据
            TH1=0;         //定时器清0
            TL1=0;         //定时器清0
            TR1=1;         //开启定时器T0
            while(IRIN==0) { //如果是低电平就等待 //低电平计时
                if (TH1 * 256 + TL1 > 553) {
                    EX1=1;      
                    TR1=0;    //开启定时器T1
                    UART_send_string("ir err3");
                    break;
                }
            }
            TR1=0;         //关闭定时器T0
            LowTime=TH1*256+TL1;    //保存低电平宽度
            TH1=0;         //定时器清0
            TL1=0;         //定时器清0
            TR1=1;         //开启定时器T0
            while(IRIN==1)   //如果是高电平就等待
            {
                if (TH1 * 256 + TL1 > 1843) { //2ms
                    EX1=1;      
                    TR1=0;    //开启定时器T1
                    UART_send_string("ir err4");
                    break;
                }
            };
            TR1=0;        //关闭定时器T0
            HighTime=TH1*256+TL1;   //保存高电平宽度
            if((LowTime<370)||(LowTime>640))
                return 0;        //如果低电平长度不在合理è围，则认为出错，停止解码
            if((HighTime>420)&&(HighTime<620))   //如果高电平时间在560微秒左右，即计数560／1.085＝516次
                temp=temp&0x7f;       //(520-100=420, 520+100=620)，则该位是0
            if((HighTime>1300)&&(HighTime<1800)) //如果高电平时间在1680微秒左右，即计数1680／1.085＝1548次
                temp=temp|0x80;       //(1550-250=1300,1550+250=1800),则该位是1
        }
        IrValue[i]=temp;//将解码出的字节值å¨存在a[i]
    }
    if(IrValue[2]=~IrValue[3])  //验证键数据码和其反码是否相等,一般情况下不必验证用户码
        return 1;     //解码正确，返回1
    return 0;
}

void ReadIr() interrupt 2
{
    EX1=0;      //关闭外中断1，不再接收二次红外信号的中断，只解码当前红外信号

    leddd = !leddd;
    TH1=0;      //定时器T1的高8位清0
    TL1=0;      //定时器T1的低8位清0
    TR1=1;    //开启定时器T1
    while(IRIN==0) {
        if (TH1 * 256 + TL1 > 9216) {
            EX1=1;      //关闭外中断1，不再接收二次红外信号的中断，只解码当前红外信号
            TR1=0;    //开启定时器T1
            UART_send_string("ir err1");
            break;
        }
    };          //如果是低电平就等待，给引导码低电平计时
    TR1=0;                //关闭定时器T1
    LowTime=TH1*256+TL1;  //保存低电平时间
    TH1=0;      //定时器T1的高8位清0
    TL1=0;      //定时器T1的低8位清0
    TR1=1;    //开启定时器T1
    while(IRIN==1) {
        if (TH1 * 256 + TL1 > 4608) {
            EX1=1;      //关闭外中断1，不再接收二次红外信号的中断，只解码当前红外信号
            TR1=0;    //开启定时器T1
            UART_send_string("ir err2");
            break;
        }
    };  //如果是高电平就等待，给引导码高电平计时
    TR1=0;        //关闭定时器T1
    HighTime=TH1*256+TL1;//保存引导码的高电平长度

    if((LowTime>7800)&&(LowTime<8800)&&(HighTime>3600)&&(HighTime<4700))
    {
        //如果是引导码,就开始解码,否则放弃,引导码的低电平计时
        //次数＝9000us/1.085=8294, 判断区间:8300－500＝7800，8300＋500＝8800.
        if(DeCode()==1) // 执行遥控解码功能
        {
            /* Disp();//调用1602LCD显示函数 */
            //beep_ring_1s();//蜂鸣器响一声 提示解码成功
            /* leddd = !leddd; */
         }
    }
    EX1=1;   //开启外中断EX1
    /* UART_send_string("decode"); */
}
