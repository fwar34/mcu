/*
  增强的简易多任务操作系统,具有简单的消息机制和休眠/睡眠机制,支持任务动态装入和结束.
*/

#include <string.h>
#include <iostm8.h>
#include <stdio.h>
#include <intrinsics.h>
#include "aos.h"
#include "aos_config.h"
#include "uart.h"
#include "circle_queue.h"
#include "common_list.h"
/*============================以下为测试代码============================*/
void led_init()
{
    PG_DDR |= 1 << 1;
    PG_CR1 |= 1 << 1;
    PG_CR2 &= ~(1 << 1);

    PD_DDR |= 1 << 2;
    PD_CR1 |= 1 << 2;
    PD_CR2 &= ~(1 << 2);

    PC_DDR |= ((1 << 3) | (1 << 4));
    PC_CR1 |= ((1 << 3) | (1 << 4));
    PC_CR2 &= ~((1 << 3) | (1 << 4));
}

void task0()
{
    while (1) {
        //PG_ODR ^= 1 << 2;
        PG_ODR_ODR1 = !PG_ODR_ODR1;
        PD_ODR_ODR2 = !PD_ODR_ODR2;

        /* uart_send_byte(0x0); */
        uart_send_string("task0\n");
        aos_task_sleep(200);
        /* printf("task1 reserver\n"); */
    }
}

static uint8_t recv_flag = 0;
unsigned char stra[3], strb[3];
//接收task
void task1()
{
    unsigned int count1 = 0;
    unsigned char i;
    event_reg(EVENT_RF_PULS_RECV);
    recv_flag = 1;

    uint8_t event;
    while (1) {
        event_wait(0);
        /* uart_send_string("1s recv\n"); */
        if (!event_pop(&event)) {
            uart_send_string("recv task pop event error!\n");
        }
        i = sizeof(stra);
        do
        {
            stra[i-1] = strb[i-1];
            aos_task_switch();
        } while (--i);
    
        event_push(EVENT_RF_PULS_SENT);//发送消息(其实质是唤醒监听该消息的进程)
        if (++count1 == 5000) {
            /* uart_send_byte(0x1); */
            uart_send_string("recv\n");
            //uart_send_byte(event);
            count1 = 0;
            PG_ODR_ODR1 = !PG_ODR_ODR1;
            PC_ODR_ODR4 = !PC_ODR_ODR4;
        }
    }
    /* aos_task_exit();//结束任务. */
}

//测试任务之主任务:将数据放入缓冲区strb[]内,然后在创建子任务task2后进入休眠,等待EVENT_RF_PULS_SENT消息.
//task2在处理完缓冲区strb[]中的数据后发送EVENT_RF_PULS_SENT消息唤醒主任务,然后结束自已.
//主任务被唤醒后,解除对EVENT_RF_PULS_SENT的监听,并结束任务.
//注意:为了演示能持续进行,任务在结束前重新装入了它自已.这种用法没错误,但在实际应用中不大可能出现.
void task2() //发送task
{
    uint16_t count2 = 0;
    event_reg(EVENT_RF_PULS_SENT);

    uint8_t event;
    while (1) {
        //如果等待的消息产生于另一任务进程中,则使用task_suspend()就可以了.
        strb[0] = 3, strb[1] = 2, strb[2] = 1;
        event_push(EVENT_RF_PULS_RECV);//发送消息(其实质是唤醒监听该消息的进程)
        if (++count2 == 5000) {
            /* uart_send_byte(0x2); */
            uart_send_string("send\n");
            //uart_send_byte(event);
            count2 = 0;
            PG_ODR_ODR1 = !PG_ODR_ODR1;
            PC_ODR_ODR3 = !PC_ODR_ODR3;
        }
        /* aos_task_load(task2);//装载子任务 */

        if (recv_flag) {
            //这里先等待task2启动好（注册了EVENT_RF_PULS_RECV消息）再发数据，防止接收任务还没有注册消息，这里就
            event_wait(0);
            if (!event_pop(&event)) {
                uart_send_string("send task pop event error!\n");
            }
            /* aos_task_sleep(1); */
            /* uart_send_string("1s send\n"); */
        }
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
void timer3_init()        //
{
    TIM3_PSCR = 0x07; //128分频
    TIM3_ARRH = 0x02; //5mstick@16MHz
    TIM3_ARRL = 0x70;
    /* TIM3_ARRH = 0x00; //1mstick@16MHz */
    /* TIM3_ARRL = 0x7D; */
    TIM3_CR1_ARPE = 0; //禁止预装载来更新，立即更新TIM3_ARR成设定值
    TIM3_IER_UIE = 1;
    //TIM3_EGR_UG = 1;
    TIM3_CR1_CEN = 1;
} 

void main()
{
    aos_init();

    aos_task_load(task0);//task1为无关任务,模拟实际使用中的其它任务.在这里不需理睬.
    aos_task_load(task1);//接收任务
    aos_task_load(task2);//发送任务
    
    clock_init();
    uart_init();
    timer3_init();
    led_init();
    
    uart_send_byte(0xff);
    aos_start();
    //__enable_interrupt();
    //while (1);
}
