#include <intrinsics.h>
#include <stdint.h>
#include <string.h>
#include <iostm8.h>
#include "aos_list.h"
#include "aos_config.h"
#include "circle_queue.h"
#include "uart_sdcc.h"
#include "heap_1.h"

extern void archFirstThreadRestore(uint8_t* new_stack_ptr);
extern void archContextSwitch(uint8_t** old_stack_ptr, uint8_t* new_stack_ptr);
extern void* pvPortMalloc(size_t xWantedSize);

//static uint8_t* stack_temp = NULL;

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

typedef struct {
    uint8_t semaphore;
    List wait_tasks;
} Semaphore;

typedef struct {
    CircleQueue queue;
    List send_tasks;
    List recv_tasks;
} MessageQueue;

typedef struct {
    uint8_t* stack_ptr;
    uint8_t tid;
    task_func task;
    uint16_t delay_ticks;
    uint8_t* stack;
    Node task_node;
} TCB_Info;

typedef struct {
    uint8_t is_init;
    uint8_t schedule_lock_count;
    uint16_t current_tick_count;
    uint16_t unblock_tick_count;
    uint8_t current_priority;
    TCB_Info* current_tcb;
    List ready_tasks[MAX_PRIORITY];
    List delay_tasks;
    List delay_overflow_tasks;
    uint16_t tid;
} AOS_Info;

AOS_Info aos = {
    .current_tid = 0,
    .is_init = 0,
};

void task_shell()
{
    __enable_interrupt();
    if (aos.current_tcb->task) {
        (aos.current_tcb->task)();
    }
}

void aos_task_idle()
{
    while (1);
}

void aos_init()
{
    if (is_init) {
        return;
    }

    uint8_t i;
    for (i = 0; i < MAX_PRIORITY; ++i) {
        list_init(&ready_tasks[i], LIST_NORMAL);
    }

    list_init(&aos.delay_list, LIST_ASCENDING);
    list_init(&aos.delay_overflow_list, LIST_ASCENDING);
    list_init(&aos.event_list, LIST_ASCENDING);
    list_init(&aos.semaphore_list, LIST_ASCENDING);

    //添加空闲任务,优先级最小255
    static TCB_Info idle_tcb;
    static Node idle_node;
    idle_node.priority = 255;
    idle_node.data = &idle_tcb;
    list_insert_ascending(&aos.ready_list, &idle_node);
    idle_tcb.task = aos_task_idle;
    idle_tcb.stack_ptr = idle_tcb.stack + MAX_TASK_STACK_LENGTH - 1;
    *(idle_tcb.stack_ptr)-- = (uint16_t)task_shell & 0xFF;
    *(idle_tcb.stack_ptr)-- = (uint16_t)task_shell >> 8;
    idle_tcb.stack_ptr -= 8; //?b8->?b15
    idle_tcb.tid = ++tid;

    is_init = 1;
}

uint8_t event_create(Event* event)
{
}

void event_delete(uint8_t event)
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

    if (aos.event_vector[event] == 0xFF) {
        return 0;
    }

    //这里必须用临界区保护，因为不保护的话在push和设置TASK_READY中间被中断ISR调度的话，
    //当前task是SUSPEND会改成READY后可能立即被执行一次，等当前任务下次重新被切入的时候又会在这里把状态设置成READY，
    //就可能再次被执行了一次，第二次pop就会出错，因为已经被第一次pop出去了
    __disable_interrupt();
    push(&aos.tcb_info[aos.event_vector[event]].event_queue, &event);
    /* if (event == 1) { */
    /*     uart_send_string("push 1\n"); */
    /* } */
    aos.tcb_info[aos.event_vector[event]].status = TASK_READY;
    __enable_interrupt();

    return 1;
}

uint8_t event_pop(uint8_t* event)
{
    if (empty(&aos.tcb_info[aos.current_tid].event_queue)) {
        uart_send_string("event_queue empty!\n");
        return 0;
    }

    if (!pop(&aos.tcb_info[aos.current_tid].event_queue, event)) {
        return 0;
    }
    
    /* if (*event == 1) { */
    /*     uart_send_string("pop 1\n"); */
    /* } */
    return 1;
}

void event_wait(uint16_t ticks)
{
    if (!empty(&aos.tcb_info[aos.current_tid].event_queue)) {
        return;
    }

    if (ticks == 0) {
        //永久等待
        aos.tcb_info[aos.current_tid].status = TASK_SUSPEND;
    } else {
        //超时等待
        aos.tcb_info[aos.current_tid].delay_ticks = ticks;
        aos.tcb_info[aos.current_tid].status = TASK_BLOCK;
    }

    aos_task_switch();
}

void aos_start()
{
    if (!aos.is_init) {
        return;
    }

    aos.current_tcb = list_get_max(&aos.ready_list)->data;
    __enable_interrupt();   
    archFirstThreadRestore(aos.current_tcb->stack_ptr);
}

void aos_task_exit()
{
    aos.tcb_info[aos.current_tid].status = TASK_INVALID;
    aos_task_switch();
}

void aos_task_switch()
{
    __istate_t _istate = __get_interrupt_state();    
    __disable_interrupt();

    uint8_t old_tid = aos.current_tid;
    if (aos.tcb_info[old_tid].status == TASK_RUNNING) {
        aos.tcb_info[old_tid].status = TASK_READY;
    }
    uint8_t new_tid = aos_get_next_task();
    aos.tcb_info[new_tid].status = TASK_RUNNING;

    if (old_tid != new_tid) {
        if (aos.tcb_info[old_tid].status != TASK_INVALID) {
            archContextSwitch(&aos.tcb_info[old_tid].stack_ptr, aos.tcb_info[new_tid].stack_ptr);
        } else {
            //如果当前任务已经删除则不保存当前任务的上下文
            archFirstThreadRestore(aos.tcb_info[new_tid].stack_ptr);
        }
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
    aos.tcb_info[tid].status = TASK_READY;
    aos_task_switch();
}

/* void aos_task_suspend() */
/* { */
/*     aos.tcb_info[aos.current_tid].status = TASK_BLOCK; */
/*     aos_task_switch(); */
/* } */

void aos_task_sleep(uint16_t ticks)
{
    if (!ticks) {
        return;
    }
    aos.tcb_info[aos.current_tid].delay_ticks = ticks;
    aos.tcb_info[aos.current_tid].status = TASK_DELAY;
    aos_task_switch();
}

//========时钟中断函数========================================================
#pragma vector = TIM3_OVR_UIF_vector
__interrupt void tim_isr()
{
    TIM3_SR1_UIF = 0;
    //https://mp.weixin.qq.com/s/ScX5Y50K9jD6VUnORkWsmw?
    //stm8这里不用关中断，因为tim3的中断优先级默认就是3，最高优先级，不会被其他可屏蔽的中断打断
    //__istate_t _istate = __get_interrupt_state();    
    //__disable_interrupt();
    
    uint8_t old_tid = aos.current_tid;
    if (aos.tcb_info[old_tid].status == TASK_RUNNING) {
        aos.tcb_info[old_tid].status = TASK_READY;
    }

    uint8_t i;
    for (i = 0; i < MAX_TASKS; ++i) {
        TCB_Info* info = &aos.tcb_info[i];
        if (info->status == TASK_BLOCK || info->status == TASK_SUSPEND) {
            if (!empty(&info->event_queue)) {
                info->status = TASK_READY;
                info->delay_ticks = 0;
            }
        }

        if (info->status == TASK_BLOCK || info->status == TASK_DELAY) {
            if (info->delay_ticks > 0) {
                if (--info->delay_ticks == 0) {
                    info->status = TASK_READY;
                }
            }
        }
    }

    uint8_t new_tid = aos_get_next_task();
    aos.tcb_info[new_tid].status = TASK_RUNNING;
    if (old_tid != new_tid) {
        archContextSwitch(&aos.tcb_info[old_tid].stack_ptr, aos.tcb_info[new_tid].stack_ptr);
    }

    //__set_interrupt_state(_istate);
}
