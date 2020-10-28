/*
  增强的简易多任务操作系统,具有简单的消息机制和休眠/睡眠机制,支持任务动态装入和结束.
*/

#include <iostm8.h>
#include <stdio.h>
#include <intrinsics.h>
#include "aos.h"
#include "aos_config.h"
#include "uart.h"
/*============================以下为测试代码============================*/
void led_init()
{
    PG_DDR |= 1 << 1;
    PG_CR1 |= 1 << 1;
    PG_CR2 &= ~(1 << 1);
}

void task0()
{
    while (1) {
        //PG_ODR ^= 1 << 2;
        PG_ODR_ODR1 = !PG_ODR_ODR1;
        uart_send_byte(0x1);
        aos_task_sleep(200);
        //printf("task1 reserver\n");
    }
}

unsigned char stra[3], strb[3];
unsigned int count1 = 0;
//测试任务之主任务:
void task2()
{
    static unsigned char i;
    event_reg(EVENT_RF_PULS_RECV);

    while (1) {
        event_wait();
        i = sizeof(stra);
        uart_send_byte(0x2);
        do
        {
            stra[i-1] = strb[i-1];
            aos_task_switch();
        } while (--i);
    
        if (++count1 == 5000) {
            count1 = 0;
            PG_ODR_ODR1 = !PG_ODR_ODR1;
        }
        event_push(EVENT_RF_PULS_SENT);//发送消息(其实质是唤醒监听该消息的进程)
    }
    /* aos_task_exit();//结束任务. */
}

//测试任务之主任务:将数据放入缓冲区strb[]内,然后在创建子任务task2后进入休眠,等待EVENT_RF_PULS_SENT消息.
//task2在处理完缓冲区strb[]中的数据后发送EVENT_RF_PULS_SENT消息唤醒主任务,然后结束自已.
//主任务被唤醒后,解除对EVENT_RF_PULS_SENT的监听,并结束任务.
//注意:为了演示能持续进行,任务在结束前重新装入了它自已.这种用法没错误,但在实际应用中不大可能出现.
void task1()
{
    /* static unsigned char event_backup;//用于保存信号EVENT_RF_PULS_SENT原来的值.在这个例子里实际上是不需要保存的,因为EVENT_RF_PULS_SENT未被其它进程监听.但在真实应用中则不一定能预知. */

    /* event_reg(EVENT_RF_PULS_SENT, event_backup);//注册消息,原值保存在event_backup中(该变量必须申明为静态) */
    event_reg(EVENT_RF_PULS_SENT);

    while (1) {
#if 1
    //如果等待的消息产生于另一任务进程中,则使用task_suspend()就可以了.
    strb[0] = 3, strb[1] = 2, strb[2] = 1;
    event_push(EVENT_RF_PULS_RECV);//发送消息(其实质是唤醒监听该消息的进程)
    uart_send_byte(0x3);
    /* aos_task_load(task2);//装载子任务 */
    event_wait();
#else
    //跟中断打交道时最好使用task_wait_interrupt().
    //这里的例子是假定中断服务程序发现strb[]全部不为0时,送出EVENT_RF_PULS_SENT消息.
    //如果进程所等待的消息产生于中断中,则要用该宏来完成.否则有可能丢失信息,进程将无法再醒过来.详细说明见头文件说明.
    //括号中的语句为,可能触发中断的语句.
    /* task_wait_interrupt( */
    /*     strb[0] = 3; strb[1] = 2; strb[2] = 1; */
    /*     task_load((unsigned int)task2); */
    /*     ); */
#endif
    }

    /* event_unreg(EVENT_RF_PULS_SENT, event_backup); */
    /* event_unreg(EVENT_RF_PULS_SENT); */
    /* aos_task_load(task1);//演示如何在任务中载入其它任务.这里载入的是它自已,实际应用中不大可能装载自已. */
    /* aos_task_exit();//结束任务. */
}

//==================系统时钟初始化=================================
void clock_init()
{
    CLK_CKDIVR = 0x00;//HSI 不分频，主时钟 16M
}

//==================系统时钟初始化=================================
void timer3_init()        //5毫秒tick@16MHz
{
    TIM3_PSCR = 0x07; //128分频
    TIM3_ARRH = 0x02;
    TIM3_ARRL = 0x70;
    TIM3_CR1_ARPE = 0; //禁止预装载来更新，立即更新TIM3_ARR成设定值
    TIM3_IER_UIE = 1;
    //TIM3_EGR_UG = 1;
    TIM3_CR1_CEN = 1;
} 

void main()
{
    aos_init();

    aos_task_load(task0);//task1为无关任务,模拟实际使用中的其它任务.在这里不需理睬.
    aos_task_load(task1);//主任务
    aos_task_load(task2);//主任务
    
    clock_init();
    uart_init();
    timer3_init();
    led_init();
    
    uart_send_byte(0xff);
    aos_start();
    //__enable_interrupt();
    //while (1);
}
