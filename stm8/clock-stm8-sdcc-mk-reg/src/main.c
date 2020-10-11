#include "iostm8.h"
#include "key.sdcc.h"
#include "ds1302.sdcc.h"
#include "lcd1602.sdcc.h"
#include "dht11.sdcc.h"
#include "infrared.sdcc.h"
#include "common.sdcc.h"
#include "uart_sdcc.h"
#include "delay.h"

extern unsigned int new_value;

extern unsigned char ch_count;//两次ch键进入设置的时间计数
extern unsigned char first_ch_flag;//表示第一次按ch的标志
extern unsigned char dht11_data[5];//湿度十位，湿度个位，温度十位，温度个位，是否显示的标志
extern unsigned short idle_count;//最后一次设置开始空闲计数

static unsigned int count = 40;//dht11更新的计数

void extid_isr() __interrupt(EXTI3_vector)
{
    IrMachine();
    key_scan();
}

void uart2_isr() __interrupt(UART2_R_RXNE_vector)
{
    /* UART2_ClearITPendingBit(UART2_IT_RXNE); */
    uart_recv_buf[uart_recv_buf_index++] = uart_recv_byte();
    if (uart_recv_buf_index >= 255)
        uart_recv_buf_index = 0;
}

void tim4_isr() __interrupt(TIM4_OVR_UIF_vector)
{
    TIM4_SR_UIF = 0;
        
    if (ch_count > 0) {//第一次点击ch按钮会把ch_count设置成1
        ++ch_count;
        if (ch_count > 20) {//1s过后没有点击第二次ch按钮的话重置字段
            ch_count = 0;
        }
    }

    if (idle_count > 0) {//每一次设置会把idle_count设置成1,所以大于0才判断是否是设置空闲超时
        ++idle_count;
        if (idle_count > 20 * 10) {//设置空闲了10秒之后退出
            idle_count = 0;
            exit_settings();
        }
    }

    if (++count >= 500 * 2) {//1000ms * 2 -> 2s更新一次dht11
        /* lcd_light_back = !lcd_light_back; */
        count = 0;//reset counter
        dht11_read_data();
        display_dht11();
        uart_send_string("debug ir:");
        uart_send_hex(debug_ir >> 8);
        uart_send_hex((uint8_t)debug_ir);
        debug_ir = 0;
    }

    process_key();//处理物理按键
}

void Timer2Init(void)        //timer2@1MHz, dht11和ir在使用 每次tick为1us
{
    TIM2_PSCR = 0x04;  //2^4=16分频
    TIM2_ARRH = 0xFF;
    TIM2_ARRL = 0xFF;
    TIM2_IER_UIE = 0; //禁止中断
    /* TIM2_IER &= ~MASK_TIM2_IER_UIE; */
    TIM2_EGR_UG = 1; //软件产生更新事件，可以立即更新预分频寄存器
    TIM2_CR1_CEN = 0; //暂停TIM2
}

void Timer3Init(void)        //0.5微秒@2MHz
{
    TIM3_PSCR = 0x04;
    TIM3_ARRH = 0xFF;
    TIM3_ARRL = 0xFF;
    TIM3_IER_UIE = 0;
    TIM3_EGR_UG = 1;
    TIM3_CR1_CEN = 0;
}

void Timer4Init(void)        //2毫秒@2MHz
{
    TIM4_PSCR = 0x07; //128分频
    TIM4_ARR = 249;
    TIM4_EGR_UG = 1;//软件产生更新事件，可以立即更新预分频寄存器
    TIM4_CR1_ARPE = 1;
    TIM4_SR_UIF = 0;
    TIM4_IER_UIE = 1;
    TIM4_CR1_CEN = 1;
}

void display_idle_count()
{
    /* unsigned char i = idle_count / 10; */
    /* unsigned char j = idle_count % 10; */
    unsigned char i = new_value / 10;
    unsigned char j = new_value % 10;
    write_char(0, 14, i + '0');
    write_char(0, 15, j + '0');
}

void main(void)
{
    CLK_CKDIVR = 0x00;//HSI 不分频，主时钟 16M
    delay_init(16);
    disableInterrupts();

    /* unsigned char msg[] = "hello"; */
    //初始时间20年8月16号14点16分55秒星期天
    DS1302_TIME start_time = {20, 9, 9, 3, 0, 6, 40};
    DS1302_TIME current_time;

    common_gpio_init();
    lcd1602_init();
    ds1302_init();
    uart_init();

    if (!ds1302_is_running()) {
        ds1302_write_time(&start_time);
    }

    Timer2Init();
    Timer3Init();
    Timer4Init();
    beep_mute();
    IrInit();

    wait_for_dht11();
    lcdWriteCmd(0x01); //1602清屏
    dht11_read_data();
    display_dht11();

    enableInterrupts();
    clear_uart_recv_buf();

    while (1)
    {
        /* display_idle_count(); */
        ds1302_read_time(&current_time);
        display(&current_time);
    }
}
