/* https://blog.csdn.net/qq_42012736/article/details/80555951 */
#include "stm8s.h"
#include "lcd1602.sdcc.h"
#include "delay.sdcc.h"
#include "common.sdcc.h"
#include "ds1302.sdcc.h"
#include "uart_sdcc.h"

#define INFRARED_PORT GPIOD
#define INFRARED_PIN GPIO_PIN_3

unsigned char IrValue[4];//用于存储数据码，对应前两个是地址位，后两个是数据位和校验位
unsigned char ch_count = 0;//两次ch键进入设置的时间计数
unsigned char enter_settings_flag = 0;//进入设置的标志
unsigned short idle_count = 0;//最后一次设置开始空闲计数
unsigned int LowTime, HighTime; //储存高、低电平的宽度 

unsigned char get_header = 0; //是否获取到了头部
unsigned char ir_repeat_count = 0; //重复码的次数
unsigned char surge_count = 0; //下降沿计数器
unsigned char ir_repeat_flag = 0; //是否有重复码

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
//45 46 47
//44 40 43
//07 15 09
//16 19 0D
//0C 18 5E
//08 1C 5A
//42 52 4A
unsigned char process_irkey()
{
    if (IrValue[2] == 0x46) {//CH 双击进入设置，单击确认（设置的时候暂停ds1302）
        process_ch();
    } else if (IrValue[2] == 0x19) {//100+ 背光开关
        GPIO_WriteReverse(LCD_BK_PORT, LCD_BK_PIN);
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
    GPIO_Init(INFRARED_PORT, INFRARED_PIN, GPIO_MODE_IN_FL_IT); //浮动输入带中断，外部有上拉电阻
    EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOD, EXTI_SENSITIVITY_FALL_ONLY); //下降沿出发
}

unsigned char DeCode(void)
{
    unsigned char i,j;
    unsigned char temp = 0;    //储存解码出的数据
    for (i = 0; i < 4; i++)      //连续读取4个用户码和键数据码
    {
        for (j = 0; j < 8; j++)  //每个码有8位数字
        {
            temp = temp >> 1;  //temp中的各数据位右移一位，因为先读出的是高位数据
            TIM2_SetCounter(0x0000);
            TIM2_Cmd(ENABLE);
            while (!GPIO_ReadInputPin(INFRARED_PORT, INFRARED_PIN)) { //如果是低电平就等待 //低电平计时
                if (TIM2_GetCounter() > 0xEE00) {//时间过长的话退出循环
                    TIM2_Cmd(DISABLE);
                    //uart_send_string("ir err3");
                    return 0;
                }
            }
            TIM2_Cmd(DISABLE);
            LowTime = TIM2_GetCounter();
            TIM2_SetCounter(0x0000);
            TIM2_Cmd(ENABLE);

            while (GPIO_ReadInputPin(INFRARED_PORT, INFRARED_PIN))   //如果是高电平就等待
            {
                if (TIM2_GetCounter() > 0xEE00) {//时间过长的话退出循环
                    TIM2_Cmd(DISABLE);
                    //uart_send_string("ir err4");
                    return 0;
                }
            };
            TIM2_Cmd(DISABLE);
            HighTime = TIM2_GetCounter();

            if (LowTime < 420 || LowTime > 700) //560 - 140, 560 + 140
                return 0;        //如果低电平长度不在合理范围，则认为出错，停止解码
            if (HighTime > 460 && HighTime < 660)   //如果高电平时间在560微秒左右，即计数560／1＝560次
                temp = temp & 0x7f;       //(560-100=460, 560+100=660)，则该位是0
            if (HighTime > 1430 && HighTime < 1930) //如果高电平时间在1680微秒左右，即计数1680／1＝1680次
                temp = temp | 0x80;       //(1680-250=1430,1680+250=1930),则该位是1
        }
        IrValue[i] = temp;//将解码出的字节值保存在a[i]
    }

    if (IrValue[2] = ~IrValue[3])  //验证键数据码和其反码是否相等,一般情况下不必验证用户码
    {
        return 1;     //解码正确，返回1
    }
    return 0;
}

void ReadIr()
{
    if (GPIO_ReadInputPin(INFRARED_PORT, INFRARED_PIN)) {
        return;
    }

    GPIOD->CR2 &= ~(1 << 3);
    TIM2_Cmd(DISABLE);
    TIM2_SetCounter(0x0000);
    TIM2_Cmd(ENABLE);
    while (!GPIO_ReadInputPin(INFRARED_PORT, INFRARED_PIN)) { //如果是低电平就等待，给引导码低电平计时
        if (TIM2_GetCounter() > 0xEE00) {//时间过长的话退出循环
            TIM2_Cmd(DISABLE);
            //uart_send_string("ir err1");
            GPIOD->CR2 |= 1 << 3;
            return;
        }
    }
    TIM2_Cmd(DISABLE);
    LowTime = TIM2_GetCounter();
    TIM2_SetCounter(0x0000);
    TIM2_Cmd(ENABLE);


    while (GPIO_ReadInputPin(INFRARED_PORT, INFRARED_PIN)) { //如果是高电平就等待，给引导码高电平计时
        if (TIM2_GetCounter() > 0xEE00) {//时间过长的话退出循环
            TIM2_Cmd(DISABLE);

            //uart_send_string("ir err2");
            GPIOD->CR2 |= 1 << 3;
            return;
        }
    };  
    TIM2_Cmd(DISABLE);
    HighTime = TIM2_GetCounter();

    if (LowTime > 8500 && LowTime < 9500 && HighTime > 4000 && HighTime < 5000)
    {
        //如果是引导码,就开始解码,否则放弃,引导码的低电平计时
        //低电平次数＝9000us/1=9000, 判断区间:9000－500＝8500，9000＋500＝9500.
        //高电平次数=4500us/1=4500, 判断区间:4500 - 500 = 4000, 4500 + 500 = 5000
        if (DeCode() == 1) // 执行遥控解码功能
        {
            /* Disp();//调用1602LCD显示函数 */
            process_irkey();
            enter_settings();
            display_current_setting();

            //uart_send_byte(IrValue[2]);
            /* GPIO_WriteReverse(LED_PORT, LED_PIN); */
            uart_send_hex(IrValue[2]);
            if (IrValue[2] == 0x45) {
                uart_send_string("AT+CWJAP=\"PHICOMM\",\"fengliang\"\r\n");
            } else if (IrValue[2] == 0x46) {
                uart_send_string("AT+CWJAP=\"fenghongqi\",\"fengliang\"\r\n");
            } else if (IrValue[2] == 0x47) {
                //获取IP
                uart_send_string("AT+CIFSR\r\n");
            } else {
                uart_send_string(uart_recv_buf);
                clear_uart_recv_buf();
            }
        }
    }
    GPIOD->CR2 |= 1 << 3;
}

void IrMachine()
{
    if (GPIOD->IDR & (1 << 3)) {
        return;
    }

    unsigned int timer_count = 0;
    TIM2->CR1 &= ~TIM2_CR1_CEN;
    timer_count = TIM2->CNTRH << 8 | TIM2->CNTRL;
    TIM2->CNTRH = 0;
    TIM2->CNTRL = 0;
    TIM2->CR1 |= TIM2_CR1_CEN;
    //引导码解析
    if (timer_count >= 13300 && timer_count <= 13700  && !get_header) {
        ir_repeat_count = 0; //IR重复码清零
        ir_repeat_flag = 0;
        get_header = 1; //成功解析了头部位置
        surge_count = 1; //第一个下降沿
    //解析用户码和用户反码，键码和键码反码
    //1到32个下降沿是用户码和用户反码,键码和键码反码,32bit（4个字节）
    } else if (surge_count >= 1 && surge_count <= 32) { 
        if (timer_count >= 1000 && timer_count <= 1300) { //0
            IrValue[(surge_count - 1) / 8] >>= 1;
            ++surge_count;
        } else if (timer_count >= 2000 && timer_count <= 2450) { //1
            IrValue[(surge_count - 1) / 8] >>= 1;
            IrValue[(surge_count - 1) / 8] |= 0x80;
            ++surge_count;
        }

        //解析完成
        if (surge_count - 1 == 32) {
            /* GPIO_WriteReverse(LED_PORT, LED_PIN); */
        }
    } else if (surge_count > 32 && !ir_repeat_flag) {
        ir_repeat_flag = 1;
        surge_count = 0;
        get_header = 0;
    } else if (timer_count >= 11000 && timer_count <= 11500) {
        ir_repeat_flag = 1;
        if (ir_repeat_count < 250)
            ++ir_repeat_count;

        if (ir_repeat_count > 3)
            GPIO_WriteReverse(LED_PORT, LED_PIN);
    }
}
