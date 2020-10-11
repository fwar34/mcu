/* https://blog.csdn.net/qq_42012736/article/details/80555951 */
#include "iostm8.h"
#include "lcd1602.sdcc.h"
#include "common.sdcc.h"
#include "ds1302.sdcc.h"
#include "uart_sdcc.h"

#define INFRARED_PIN PD_IDR_IDR3
#define TIM2_SET_COUNTER(count) TIM2_CNTRH = (uint8_t)((count) >> 8); TIM2_CNTRL = (uint8_t)(count)
#define TIM2_GET_COUNTER() ((uint16_t)TIM2_CNTRH << 8 | TIM2_CNTRL)
#define TIM2_ENABLE() TIM2_CR1_CEN = 1
#define TIM2_DISABLE() TIM2_CR1_CEN = 0

unsigned char IrValue[4];//用于存储数据码，对应前两个是地址位，后两个是数据位和校验位
unsigned char ch_count = 0;//两次ch键进入设置的时间计数
unsigned char enter_settings_flag = 0;//进入设置的标志
unsigned short idle_count = 0;//最后一次设置开始空闲计数

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
        LCD_BK_PIN = !LCD_BK_PIN;
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
    PD_DDR_DDR3 = 0;
    PD_CR1_C13 = 1; //浮动输入
    PD_CR2_C23 = 1; //带中断
    //注意EXTI_CR1_PDIS是2bit
    EXTI_CR1_PDIS = 0;
    EXTI_CR1_PDIS = 0x02; //仅下降沿触发

    /* EXTI_CR1 &= ~MASK_EXTI_CR1_PDIS; */
    /* EXTI_CR1 |= 0x02 << 6; //仅下降沿触发 */
}

void IrMachine()
{
    //外部中断配置的是下降沿触发，如果是高电平就不是自己触发的外部中断
    if (INFRARED_PIN) {
        return;
    }

    uint16_t timer_count = 0;
    TIM2_DISABLE();
    timer_count = TIM2_GET_COUNTER();
    ++debug_ir;

    TIM2_SET_COUNTER(0x0000);
    TIM2_ENABLE();
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
            /* IrValue[(surge_count - 1) / 8] >>= 1; */
            IrValue[(surge_count - 1) >> 3] >>= 1;
            ++surge_count;
        } else if (timer_count >= 2000 && timer_count <= 2450) { //1
            IrValue[(surge_count - 1) >> 3] >>= 1;
            IrValue[(surge_count - 1) >> 3] |= 0x80;
            ++surge_count;
        }

        //解析完成
        if (surge_count - 1 == 32) {
            LED_PIN = !LED_PIN;
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
            LED_PIN = !LED_PIN;
    }
}
