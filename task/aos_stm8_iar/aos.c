#include <intrinsics.h>
#include <stdint.h>
#include "aos.h"

/* extern unsigned char  event_vector[MAX_EVENT_VECTOR];//消息向量,每项保存一个task_id号,指向监听它的进程(task_id).无监者时应置为0xFF */

static uint16_t stack_temp = 0;

#define IDLE_TASK_TID MAX_TASKS
#define TASK_SAVE()                             \
    asm("ldw Y, 0x07"); /*?b8,?b9*/             \
    asm("pushw Y");                             \
    asm("ldw Y, 0x09"); /*?b10,?b11*/           \
    asm("pushw Y");                             \
    asm("ldw Y, 0x0A"); /*?b12,?b13*/           \
    asm("pushw Y");                             \
    asm("ldw Y, 0x0C"); /*?b14,?b15*/           \
    asm("pushw Y");                             \
    asm("ldw Y, SP");                           \
    asm("ldw l:stack_temp, Y");

#define TASK_RESTORE()                          \
    asm("ldw Y, l:stack_temp")                  \
    asm("ldw SP, Y");                           \
    asm("popw Y");                              \
    asm("ldw 0x0C, Y"); /*?b14,?b15*/           \
    asm("popw Y");                              \
    asm("ldw 0x0A, Y"); /*?b12,?b13*/           \
    asm("popw Y");                              \
    asm("ldw 0x09, Y"); /*?b10,?b11*/           \
    asm("popw Y");                              \
    asm("ldw 0x07, Y"); /*?b8,?b9*/

typedef enum {
    TASK_INVALID,
    TASK_BLOCK,
    TASK_READY,
    TASK_RUNNING
} TaskStatus;

typedef struct {
    uint16_t stack_ptr;
    uint8_t pid;
    task_func task;
    uint8_t status;
    uint16_t delay_ticks;
    uint8_t event;
    uint8_t semaphore;
    uint8_t stack[MAX_TASK_STACK_LENGTH];
} TCB_Info;

typedef struct {
    uint8_t current_tid;
    uint8_t is_init;
    TCB_Info tcb_info[MAX_TASKS + 1]; //最后一个是空闲任务
} AOS_Info;

AOS_Info aos;

/* unsigned char task_id; */
/* unsigned int task_sp[MAX_TASKS];//任务的栈指针 */
/* unsigned char task_stack[MAX_TASKS][MAX_TASK_DEP];//任务堆栈. */
/* unsigned int task_sleep[MAX_TASKS];//任务睡眠定时器 */

void aos_task_idle()
{
    while (1);
}

void aos_init()
{
    uint8_t i = 0;
    for (; i < MAX_TASKS; ++i) {
        memset(aos.tcb_info, 0, sizeof(TCB_Info));
    }
    //tid为MAX_TASKS(即最后一个)的是空闲任务
    aos_task_load(aos_task_idle);
}

uint8_t aos_get_next_task()
{
    uint8_t tid = aos.current_tid;
    while (1) {
        if (++tid > MAX_TASKS) {
            tid = 0;
        }

        //当前其他任务都没有就绪则切换到空闲任务
        if (tid == aos.current_tid) {
            aos.current_tid = IDLE_TASK_TID;
            break;
        }

        if (aos.tcb_info[tid].status == TASK_READY) {
            aos.current_tid = tid;
            break;
        }
    }
    return aos.current_tid;
}

void aos_task_start()
{
    stack_temp = aos.tcb_info[0].stack_ptr;
    TASK_RESTORE();
    __enable_interrupt();   
}

void aos_task_exit()
{
    aos.tcb_info[aos.current_tid].status = TASK_INVALID;
    aos_task_switch()
}

void aos_task_switch()
{
    __istate_t _istate = __get_interrupt_state();    
    __disable_interrupt(); //由于关闭全局中断会影响cc寄存器，所以先获取cc的值再关闭全局中断

    //如果当前任务已经删除则不保存上下文
    if (aos.tcb_info[aos.current_tid].status != TASK_INVALID) {
        TASK_SAVE();
        aos.tcb_info[aos.current_tid].stack_ptr = stack_temp;
    }

    uint8_t next_tid = aos_get_next_task();
    aos.tcb_info[next_tid].status = TASK_RUNNING;
    stack_temp = aos.tcb_info[next_tid].stack_ptr;
    TASK_RESTORE();

    __set_interrupt_state(_istate);
}

//寻找一个空任务,并将任务装入.无空任务时等待.do-while循环中不作任务切换,所以无需支持重入
unsigned char aos_task_load(task_func task)
{
    uint8_t i = 0;
    while (1) {
        for (i = MAX_TASKS; i >= 0; --i) {
            if (aos.tcb_info.status == TASK_INVALID) {
                aos.tcb_info.status = TASK_READY;
                aos.tcb_info.stack_ptr = aos.tcb_info.stack + MAX_TASK_STACK_LENGTH - 1;
                *(aos.tcb_info.stack_ptr)-- = task & 0xFF;
                *(aos.tcb_info.stack_ptr)-- = task >> 8;

                *(aos.tcb_info.stack_ptr)-- = 0; //?b8 
                *(aos.tcb_info.stack_ptr)-- = 0; //?b9
                *(aos.tcb_info.stack_ptr)-- = 0; //?b10
                *(aos.tcb_info.stack_ptr)-- = 0; //?b11
                *(aos.tcb_info.stack_ptr)-- = 0; //?b12
                *(aos.tcb_info.stack_ptr)-- = 0; //?b13
                *(aos.tcb_info.stack_ptr)-- = 0; //?b14
                *(aos.tcb_info.stack_ptr)-- = 0; //?b15
                return i;
            }
        }
        task_sleep(2);//无空闲任务可用,进程休眠2周期
    }
}


//========时钟中断函数========================================================
#pragma vector = TIM3_OVR_UIF_vector
__interrupt void clock_timer()
{
    __disable_interrupt();
    TIM3_SR1_UIF = 0;

    uint8_t i = 0;
    for (; i < MAX_TASKS; ++i) {
        if (aos.tcb_info[i].status == TASK_BLOCK) {
            if (aos.tcb_info[i].)
        }
    }

    /* unsigned int* p; */
    /* unsigned char i; */

    /* //任务延迟处理 */
    /* i = MAX_TASKS; */
    /* p = task_sleep;  */
    /* do { */
    /*     if (*p != 0 && *p != 0xFF)//不为0,也不为0xff,则将任务延时值减1.为0xff表示任务已挂起,不由定时器唤醒 */
    /*         (*p)--; */
    /*     p++; */
    /* } while (--i); */
    __enable_interrupt();
}
