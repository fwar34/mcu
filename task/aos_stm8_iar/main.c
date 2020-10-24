/*
  增强的简易多任务操作系统,具有简单的消息机制和休眠/睡眠机制,支持任务动态装入和结束.
*/

#include <iostm8.h>
#include <stdio.h>
#include <intrinsics.h>
#include "task.h"
#include "uart.h"
/*============================以下为测试代码============================*/
void led_init()
{
    PD_DDR |= 1 << 2;
    PD_CR1 |= 1 << 2;
    PD_CR2 &= ~(1 << 2);
}

void task1(){//无关紧要的任务
    while(1){
        //PD_ODR ^= 1 << 2;
      //PD_ODR_ODR2 = !PD_ODR_ODR2;
      uart_send_byte(0x1);
      task_sleep(1000);
        //printf("task1 reserver\n");
    }
}

unsigned char stra[3], strb[3];
unsigned int count1 = 0;
//测试任务之主任务:
void task2(){
    static unsigned char i;

    i = sizeof(stra);
    uart_send_byte(0x2);
    do{
        stra[i-1] = strb[i-1];
        
        task_switch();
    }while(--i);
    
    if (++count1 == 5000) {
      count1 = 0;
      PD_ODR_ODR2 = !PD_ODR_ODR2;
    }
        
    event_push(EVENT_RF_PULS_SENT);//发送消息(其实质是唤醒监听该消息的进程)

    task_exit();//结束任务.
}

//测试任务之主任务:将数据放入缓冲区strb[]内,然后在创建子任务task2后进入休眠,等待EVENT_RF_PULS_SENT消息.
//task2在处理完缓冲区strb[]中的数据后发送EVENT_RF_PULS_SENT消息唤醒主任务,然后结束自已.
//主任务被唤醒后,解除对EVENT_RF_PULS_SENT的监听,并结束任务.
//注意:为了演示能持续进行,任务在结束前重新装入了它自已.这种用法没错误,但在实际应用中不大可能出现.
void task3(){
    static unsigned char event_backup;//用于保存信号EVENT_RF_PULS_SENT原来的值.在这个例子里实际上是不需要保存的,因为EVENT_RF_PULS_SENT未被其它进程监听.但在真实应用中则不一定能预知.

    event_reg(EVENT_RF_PULS_SENT, event_backup);//注册消息,原值保存在event_backup中(该变量必须申明为静态)

#if 1
    //如果等待的消息产生于另一任务进程中,则使用task_suspend()就可以了.
    strb[0] = 3, strb[1] = 2, strb[2] = 1;
    uart_send_byte(0x3);
    task_load((unsigned int)task2);//装载子任务
    task_suspend();
#else
    //跟中断打交道时最好使用task_wait_interrupt().
    //这里的例子是假定中断服务程序发现strb[]全部不为0时,送出EVENT_RF_PULS_SENT消息.
    //如果进程所等待的消息产生于中断中,则要用该宏来完成.否则有可能丢失信息,进程将无法再醒过来.详细说明见头文件说明.
    //括号中的语句为,可能触发中断的语句.
    task_wait_interrupt(
        strb[0] = 3; strb[1] = 2; strb[2] = 1;
        task_load((unsigned int)task2);
        );
#endif

    event_unreg(EVENT_RF_PULS_SENT, event_backup);

    task_load((unsigned int)task3);//演示如何在任务中载入其它任务.这里载入的是它自已,实际应用中不大可能装载自已.

    task_exit();//结束任务.
}

void main(){
    __disable_interrupt();
    task_init();

    //装载任务,成功后返回值为装载的任务槽号(示例中没有用到返回值).没有空槽可用则一直等待.

    task_load((unsigned int)task1);//task1为无关任务,模拟实际使用中的其它任务.在这里不需理睬.
    task_load((unsigned int)task3);//主任务
    
    clock_init();
    uart_init();
    timer3_init();
    led_init();
    
    uart_send_byte(0xff);
     os_start();
}
