#include "lcd1602.sdcc.h"
#include "delay.sdcc.h"
#include "common.sdcc.h"
#include "ds1302.sdcc.h"
#include "uart_sdcc.h"

extern unsigned int new_value;

#define IRIN P3_3
unsigned int SURGE_INTERVAL = 0;
unsigned char HIGH_WORD = 0;
unsigned char LOW_WORD = 0;
unsigned char IR_CODE = 0;
unsigned int IR_REPEAT_FOLLOW_UP = 0;
unsigned int IR_REPEAT_COUNT = 0;
unsigned char SURGE_COUNT = 0;
unsigned char IR_COMPLAT = 0;

unsigned char IrValue[4];//用于存储数据码，对应前两个是地址位，后两个是数据位和校验位
unsigned char IR_ID = 0;                  //接收步骤
/* unsigned int IrRecCnt = 0;                   //接收时间计数 */
/* unsigned char IrIndex = 0;                    //接收位数 */
/* __bit IrRecFlag = 0;                  //接收完标志 */

unsigned char ch_count = 0;//两次ch键进入设置的时间计数
__bit enter_settings_flag = 0;//进入设置的标志
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

void IrReceive()
{
    switch(IR_ID)
    {
    //解码开始
    case 0:
    {
        IR_ID=1;
        T4T3M |= 0x08; //定时器3开始计时
        T3H=0;
        T3L=0;
    }
    break;
    //校验码头
    case 1:
    {
        T4T3M &= 0xF7;             //定时器3暂停计时
        HIGH_WORD=T3H;             //保存高低字节
        LOW_WORD=T3L;
        T3H=0;
        T3L=0;
        T4T3M |= 0x08;                  //定时器1开
        SURGE_INTERVAL=0;                 //测量数据整开
        SURGE_INTERVAL=(unsigned int)HIGH_WORD;
        SURGE_INTERVAL=SURGE_INTERVAL<<8;
        SURGE_INTERVAL=SURGE_INTERVAL|LOW_WORD;
        /* nop(); */
        //引导码捕捉
        /* if(SURGE_INTERVAL>=6300&&SURGE_INTERVAL<=7300) { */ 
        if(SURGE_INTERVAL>=11612&&SURGE_INTERVAL<=13456) { //12.6ms->14.6ms
            IR_ID=2;                       //遥控头获得位置1
            SURGE_COUNT=0;
        } else {
            IR_ID=0;
            UART_send_byte(0xAA);
            UART_send_byte(SURGE_INTERVAL >> 8);
            UART_send_byte(SURGE_INTERVAL & 0xFF);
        }
    }
    break;
    //解码
    case 2:
    {
        T4T3M &= 0xF7;                  //定时器1关
        HIGH_WORD=T3H;             //保存高低字节
        LOW_WORD=T3L;
        T3H=0;
        T3L=0;
        T4T3M |= 0x08;                 //定时器2开
        SURGE_INTERVAL=0;                //测量数据整开
        SURGE_INTERVAL=(unsigned int)HIGH_WORD;
        SURGE_INTERVAL=SURGE_INTERVAL<<8;
        SURGE_INTERVAL=SURGE_INTERVAL|LOW_WORD;
        if(SURGE_COUNT<32)
        {
            /* if(SURGE_INTERVAL>=500&&SURGE_INTERVAL<=650)//0码 */ 
            if(SURGE_INTERVAL>=921&&SURGE_INTERVAL<=1198)//0码 1ms->1.3ms
            {
                IR_CODE=IR_CODE<<1;
                SURGE_COUNT++;
            }
            /* else if(SURGE_INTERVAL>=1000&&SURGE_INTERVAL<=1300)//1码 */
            else if(SURGE_INTERVAL>=1843&&SURGE_INTERVAL<=2396)//1码 2ms->2.6ms
            {
                IR_CODE=IR_CODE<<1;
                IR_CODE=IR_CODE|0x0001;
                SURGE_COUNT++;
            }
            else
            {
                UART_send_byte(0xBB);
                IR_ID=0;
                IR_CODE=0;
                SURGE_COUNT=0;
            }

            if (SURGE_COUNT == 32) {
                UART_send_byte(SURGE_COUNT);
                SURGE_COUNT = 0;
                IR_ID = 0;
            }
            break;
        }
        else
        {
            UART_send_byte(0xCC);
            IR_COMPLAT=1;
            IR_ID=3;
            SURGE_COUNT=0;
            IR_REPEAT_COUNT=0;             //IR重复码清零
            break;
        }
    }
    break;
    case 3:
    {
        T4T3M &= 0xF7;                  //定时器1关
        HIGH_WORD=T3H;             //保存高低字节
        LOW_WORD=T3L;
        T3H=0;
        T3L=0;
        T4T3M |= 0x08;                 //定时器1开
        SURGE_INTERVAL=0;                //测量数据整开
        SURGE_INTERVAL=(unsigned int)HIGH_WORD;
        SURGE_INTERVAL=SURGE_INTERVAL<<8;
        SURGE_INTERVAL=SURGE_INTERVAL|LOW_WORD;
        /* if(SURGE_INTERVAL>=5000&&SURGE_INTERVAL<=8000)      //100ms为连加信号 */
        if(SURGE_INTERVAL>=9216&&SURGE_INTERVAL<=14746)      //100ms为连加信号
        {
            IR_REPEAT_FOLLOW_UP=1;
            IR_ID=3;
            if(IR_REPEAT_COUNT<250)
            {
                IR_REPEAT_COUNT++;
            }
        }
        UART_send_byte(0xDD);
    }
    break;
    default:
        break;
    }
}

void IrRead() __interrupt 2
{
    IrReceive();
}
