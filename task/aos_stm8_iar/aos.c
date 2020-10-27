#include <intrinsics.h>
#include <stdint.h>
#include <string.h>
#include <iostm8.h>
#include "aos.h"
#include "aos_config.h"
#include "circle_queue.h"

extern void archFirstThreadRestore(uint8_t* new_stack_ptr);
extern void archContextSwitch(uint8_t* old_stack_ptr, uint8_t* new_stack_ptr);

static uint8_t* stack_temp = NULL;

#define IDLE_TASK_TID MAX_TASKS
#define TASK_SAVE()                             \
    asm("ldw Y, 0x08"); /*?b8,?b9*/             \
    asm("pushw Y");                             \
    asm("ldw Y, 0x0A"); /*?b10,?b11*/           \
    asm("pushw Y");                             \
    asm("ldw Y, 0x0C"); /*?b12,?b13*/           \
    asm("pushw Y");                             \
    asm("ldw Y, 0x0E"); /*?b14,?b15*/           \
    asm("pushw Y");                             \
    asm("ldw Y, SP");                           \
    asm("ldw l:stack_temp, Y");

#define TASK_RESTORE()                          \
    asm("ldw Y, l:stack_temp");                 \
    asm("ldw SP, Y");                           \
    asm("popw Y");                              \
    asm("ldw 0x0E, Y"); /*?b14,?b15*/           \
    asm("popw Y");                              \
    asm("ldw 0x0C, Y"); /*?b12,?b13*/           \
    asm("popw Y");                              \
    asm("ldw 0x0A, Y"); /*?b10,?b11*/           \
    asm("popw Y");                              \
    asm("ldw 0x08, Y"); /*?b8,?b9*/


typedef enum {
    TASK_INVALID,
    TASK_BLOCK,
    TASK_READY,
    TASK_RUNNING
} TaskStatus;

typedef struct {
    uint8_t* stack_ptr;
    uint8_t tid;
    task_func task;
    uint8_t status;
    uint16_t delay_ticks;
    CircleQueue event_queue;
    uint8_t semaphore;
    uint8_t stack[MAX_TASK_STACK_LENGTH];
} TCB_Info;

typedef struct {
    uint8_t current_tid;
    uint8_t is_init;
    TCB_Info tcb_info[MAX_TASKS + 1]; //最后一个是空闲任务
    uint8_t event_vector[MAX_EVENT_VECTOR + 1];//消息向量,每项保存一个task_id号
} AOS_Info;

AOS_Info aos;

void aos_task_idle()
{
    while (1);
}

void aos_init()
{
    uint8_t i;
    for (i = 0; i < MAX_TASKS + 1; ++i) {
        memset(aos.tcb_info, 0, sizeof(TCB_Info));
    }
    for (i = 0; i < MAX_EVENT_VECTOR + 1; ++i) {
        aos.event_vector[i] = 0xFF;
    }
    //tid为MAX_TASKS(即最后一个)的是空闲任务
    TCB_Info* info = &aos.tcb_info[MAX_TASKS];
    info->task = aos_task_idle;
    info->stack_ptr = info->stack + MAX_TASK_STACK_LENGTH - 1;
    *(info->stack_ptr)-- = (uint16_t)task_shell & 0xFF;
    *(info->stack_ptr)-- = (uint16_t)task_shell >> 8;
    info->stack_ptr -= 8; //?b8->?b15
    info->tid = MAX_TASKS;
    info->status = TASK_READY;
}

uint8_t aos_get_next_task()
{
    uint8_t tid = aos.current_tid;
    while (1) {
        if (++tid >= MAX_TASKS) { //跳过idle_task
            tid = 0;
        }

        //当前其他任务都没有就绪则切换到空闲任务
        if (tid == aos.current_tid) {
            aos.current_tid = MAX_TASKS;
            break;
        }

        if (aos.tcb_info[tid].status == TASK_READY) {
            aos.current_tid = tid;
            break;
        }
    }
    return aos.current_tid;
}

uint8_t event_reg(uint8_t event)
{
    if (!event || event > MAX_EVENT_VECTOR) {
        return 0;
    }

    if (aos.event_vector[event] != 0xFF) {
        return 0;
    }

    aos.event_vector[event] = aos.current_tid;
    return 1;
}

void event_unreg(uint8_t event)
{
    if (!event || event > MAX_EVENT_VECTOR) {
        return;
    }

    aos.event_vector[event] = 0xFF;
}

uint8_t event_push(uint8_t event)
{
    if (event == 0 || event > MAX_EVENT_VECTOR) {
        return 0;
    }
    push(&aos.tcb_info[aos.event_vector[event]].event_queue, &event);
    return 1;
}

uint8_t event_pop(uint8_t* event)
{
    if (empty(&aos.tcb_info[aos.current_tid].event_queue)) {
        return 0;
    }

    if (!pop(&aos.tcb_info[aos.current_tid].event_queue, event)) {
      return 0;
    }
    
    return 1;
}

void event_wait()
{
    __disable_interrupt();
    aos.tcb_info[aos.current_tid].status = TASK_BLOCK;
    aos_task_switch();
    __enable_interrupt();
}

void aos_start()
{
    aos.current_tid = 0;
    stack_temp = aos.tcb_info[aos.current_tid].stack_ptr;
    TASK_RESTORE();
    __enable_interrupt();   
}

void aos_task_exit()
{
    __disable_interrupt();
    aos.tcb_info[aos.current_tid].status = TASK_INVALID;
    aos_task_switch();
    __enable_interrupt();
}

void task_shell()
{
    __enable_interrupt();
    if (aos.tcb_info[aos.current_tid].status == TASK_READY &&
        aos.tcb_info[aos.current_tid].task) {
        (aos.tcb_info[aos.current_tid].task)();
    }
}

void aos_task_switch()
{
    __istate_t _istate = __get_interrupt_state();    
    __disable_interrupt();

    uint8_t old_tid = aos.current_tid;
    uint8_t new_tid = aos_get_next_task();
    aos.tcb_info[new_tid].status = TASK_RUNNING;

    if (aos.tcb_info[old_tid].status != TASK_INVALID) {
        archContextSwitch(aos.tcb_info[old_tid].stack_ptr, aos.tcb_info[new_tid].stack_ptr);
    } else {
        //如果当前任务已经删除则不保存当前任务的上下文
        archFirstThreadRestore(aos.tcb_info[new_tid].stack_ptr);
    }

    __set_interrupt_state(_istate);
}

int8_t aos_task_load(task_func task)
{
    uint8_t i;
    TCB_Info* info = NULL;
    for (i = 0; i < MAX_TASKS; ++i) {
        info = &aos.tcb_info[i];
        if (info->status == TASK_INVALID) {
            memset(info, 0, sizeof(TCB_Info));
            info->task = task;
            info->stack_ptr = info->stack + MAX_TASK_STACK_LENGTH - 1;
            *(info->stack_ptr)-- = (uint16_t)task_shell & 0xFF;
            *(info->stack_ptr)-- = (uint16_t)task_shell >> 8;
            info->stack_ptr -= 8; //?b8->?b15
            info->tid = i;
            info->status = TASK_READY;
            return i;
        }
    }
    return -1;
}

void aos_task_weakup(uint8_t tid)
{
    if (tid >= MAX_TASKS) {
        return;
    }
    __disable_interrupt();
    aos.tcb_info[tid].status = TASK_READY;
    aos_task_switch();
    __enable_interrupt();
}

void aos_task_suspend()
{
    __disable_interrupt();
    aos.tcb_info[aos.current_tid].status = TASK_BLOCK;
    aos_task_switch();
    __enable_interrupt();
}

void aos_task_sleep(uint16_t ticks)
{
    if (!ticks) {
        return;
    }
    __disable_interrupt();
    aos.tcb_info[aos.current_tid].delay_ticks = ticks;
    aos.tcb_info[aos.current_tid].status = TASK_BLOCK;
    aos_task_switch();
    __enable_interrupt();
}

//========时钟中断函数========================================================
#pragma vector = TIM3_OVR_UIF_vector
__interrupt void clock_timer()
{
    TIM3_SR1_UIF = 0;
    //https://mp.weixin.qq.com/s/ScX5Y50K9jD6VUnORkWsmw?
    //stm8这里不用关中断，因为tim3的中断优先级默认就是3，最高优先级，不会被其他可屏蔽的中断打断
    //__istate_t _istate = __get_interrupt_state();    
    //__disable_interrupt();
    
    uint8_t old_tid = aos.current_tid;
    aos.tcb_info[old_tid].status = TASK_READY;

    uint8_t i;
    for (i = 0; i < MAX_TASKS; ++i) {
        TCB_Info* info = &aos.tcb_info[i];
        if (info->status == TASK_BLOCK) {
            if (info->delay_ticks > 0) {
                if (--info->delay_ticks == 0) {
                    info->status = TASK_READY;
                }
            }

            if (!empty(&info->event_queue)) {
                info->status = TASK_READY;
            }
        }
    }

    uint8_t new_tid = aos_get_next_task();
    aos.tcb_info[new_tid].status = TASK_RUNNING;
    archContextSwitch(aos.tcb_info[old_tid].stack_ptr, aos.tcb_info[new_tid].stack_ptr);

    //__set_interrupt_state(_istate);
}
