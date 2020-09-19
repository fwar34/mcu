#include "dht11.h"
#include "key.h"
#include "ds1302.h"
#include "common.h"

extern unsigned char ch_count; //两次ch键进入设置的时间计数
extern bit first_ch_flag; //表示第一次按ch的标�?
extern unsigned char dht11_data[5]; //湿度十位，湿度个位，温度十位，温度个位，是否显示的标�?
extern unsigned short idle_count; //最后一次设置开始空闲计�?

static unsigned short count = 0; //dht11更新的计�?

/* void Timer0Init(void)		//50毫秒@11.0592MHz */
/* { */
/*     TMOD = 0x01;                    //set timer0 as mode1 (16-bit) */
/*     TH0 = 0x4C; */
/*     TL0 = 0x00; */

/*     TF0 = 0;		//清除TF0标志 */
/*     TR0 = 1;		//定时�?0开始计�? */

/*     ET0  = 1;                           //enable timer0 interrupt */
/*     EA  = 1;                           //open global interrupt switch */
/* } */

void Timer0Init(void)		//10毫秒@24.000MHz
{
    /* AUXR &= 0x7F;		//定时器时�?12T模式 */
    TMOD &= 0xF0;		//设置定时器模�?
    TMOD |= 0x01;		//设置定时器模�?
    TL0 = 0xE0;		//设置定时初�?
    TH0 = 0xB1;		//设置定时初�?
    TF0 = 0;		//清除TF0标志
    TR0 = 1;		//定时�?0开始计�?

    ET0  = 1;                           //enable timer0 interrupt
    EA  = 1;                           //open global interrupt switch
}

void Timer1Init(void)        //timer1@11.0592MHz
{
    TMOD &= 0x0F;
    TMOD |= 0x10;

    //不关心timer1的中�?
    /* TF1 = 0;     //清除TF0标志 */
    /* ET1  = 1;                           //enable timer1 interrupt */
    TR1 = 0;     //定时�?1关闭
    EA  = 1;                           //open global interrupt switch
}


/* https://zhidao.baidu.com/question/477148677.html */
/* void Timer0Delay1s() interrupt 1 */
/* { */
/*     static unsigned char count; */
/*     TH0 = (65535 - 50000) / 256; */
/*     TL0 = (65535 - 50000) % 256; */
/*     if (count ++ == 20) { */
/*         count = 0; */
/*         //TODO */
/*     } */
/* } */

/* Timer0 interrupt routine */
void tm0_isr() interrupt 1
{
    TL0 = 0xE0;		//设置定时初�?
    TH0 = 0xB1;		//设置定时初�?
    if (ch_count > 0) { //第一次点击ch按钮会把ch_count设置�?1
        ++ch_count;
        if (ch_count > 100) { //1s过后没有点击第二次ch按钮的话重置字段
            ch_count = 0;
        }
    }

    if (idle_count > 0) { //每一次设置会把idle_count设置�?1,所以大�?0才判断是否是设置空闲超时
        ++idle_count;
        if (idle_count > 100 * 10) { //设置空闲�?10秒之后退�?
            exit_settings();
        }
    }

    if (++count == 100 * 2) {                //1000ms * 2 -> 2s更新一次dht11
        /* lcd_light_back = !lcd_light_back ; */
        count = 0;                //reset counter
        /* if (!dht11_read_data()) {  */
        /*     //read success */
        /*     dht11_data[5] = 1; */
        /* } */
        dht11_read_data2();
        // dht11_read_data();
    }

    process_key(); //处理物理按键
}
