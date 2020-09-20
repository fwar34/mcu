#if 0
#include "lcd1602.sdcc.h"
#include "delay.sdcc.h"
#include "common.sdcc.h"
#include "ds1302.sdcc.h"
#include "uart_sdcc.h"

extern unsigned int new_value;

sbit IRIN = P3 ^ 3;
unsigned char IrValue[4];//用于存储数据码，对应前两个是地址位，后两个是数据位和校验位
unsigned char IrRecStep = 0;                  //接收步骤
unsigned int IrRecCnt = 0;                   //接收时间计数
unsigned char IrIndex = 0;                    //接收位数
bit IrRecFlag = 0;                  //接收完标志


unsigned char ch_count = 0;//两次ch键进入设置的时间计数
bit enter_settings_flag = 0;//进入设置的标志
unsigned short idle_count = 0;//最后一次设置开始空闲计数
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


void IrReceive()
{
    switch(IrRecStep)
    {
    case 0:
        IrIndex = 0;                   //接收位数
        while (IRIN==0) // 读入 PD4 的引脚信号  //检测低电平
        {
            IrRecCnt++;                 //接收时间计数
        }
        if(IRIN==1)
        {
            if((IrRecCnt>=155)&&(IrRecCnt<=165)) // 码头低电平时间9ms
            {
                IrRecCnt = 1;
                IrRecStep++;
                IrValue[0] = 0;
                IrValue[1] = 0;
                IrValue[2] = 0;
                IrValue[3] = 0;
            }
            else
            {
                IrRecCnt = 0;
                IrRecStep = 0;
            }
        }
        break;
    case 1:
        if(IRIN==1)
        {
            IrRecCnt++;
            if(IrRecCnt >= 100)   //高电平时间过长,退出
            {
                IrRecCnt = 0;
                IrRecStep = 0;
                UART_send_string("er1");
            }
        }
        else
        {
            if((IrRecCnt>=75)&&(IrRecCnt<=85))   // 码头高电平时间4.5ms
            {
                IrRecCnt = 1;
                IrRecStep = 2;
            }
            else
            {
                IrRecCnt =0;
                IrRecStep = 0;
            }
        }
        break;
    case 2:
        if(IRIN==0)
        {
            IrRecCnt++;
            if(IrRecCnt > 30)            //低电平时间过长,退出
            {
                IrRecCnt = 0;
                IrRecStep = 0;
                UART_send_string("er2");
            }
        }
        else
        {
            if((IrRecCnt >= 8)&&(IrRecCnt <= 12)) //每位开头0.56ms低电平
            {
                IrRecCnt = 1;
                IrRecStep = 3;
            }
            else
            {
                IrRecCnt = 0;
                IrRecStep = 0;
            }
        }
        break;
    case 3:
        if(IRIN==1)
        {
            IrRecCnt++;
        }
        else
        {
            if((IrRecCnt >= 25)&&(IrRecCnt <= 35))  //高电平时间约为1.68ms,则为数据1
            {
                /* IrValue[IrIndex/8] |= IrCode[IrIndex & 0x07]; //相应位置1 */
                IrValue[IrIndex/8] >>= 1;
                IrValue[IrIndex/8] |= 0x80;
                IrRecCnt = 1;
                IrIndex++;
                IrRecStep = 2;
            }
            else if((IrRecCnt >= 8)&&(IrRecCnt <= 12))//高电平时间约为0.56ms,则为数据0
            {
                IrRecCnt = 1;
                IrIndex++;
                IrRecStep = 2;
            }
            else
            {
                IrRecStep = 0;     //退出
                IrRecCnt = 0;
            }
            if(IrIndex >= 32)    //是否接收完32位
            {
                IrRecStep = 0;
                IrRecFlag = 1;
                beep_ring_1s();
                UART_send_string("beep 1s");
            }
        }
        break;
    }
}
#endif