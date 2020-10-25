#include <intrinsics.h>
#include <stdint.h>
#include "aos.h"

extern void archContextSwitch (unsigned int *cur_s, unsigned int *new_s);                                                   
extern void archFirstThreadRestore(unsigned int *sp);

/* extern unsigned char  event_vector[MAX_EVENT_VECTOR];//消息向量,每项保存一个task_id号,指向监听它的进程(task_id).无监者时应置为0xFF */

//任务的栈指针
/* extern unsigned int task_sp[MAX_TASKS]; */
                                                                                
//预估方法:以2为基数,每增加一层函数调用,加2字节.如果其间可能发生中断,则还要再加上中断需要的栈深.
//减小栈深的方法:1.尽量少嵌套子程序 2.调子程序前关中断.
/* extern unsigned char  task_stack[MAX_TASKS][MAX_TASK_DEP];//任务堆栈. */
/* extern unsigned int  task_sleep[MAX_TASKS];//任务睡眠定时器 */

/* extern unsigned char task_id;//当前活动任务 */

#define IDLE_TASK_TID MAX_TASKS

void clock_init();
void timer3_init();

typedef enum {
    TASK_BLOCK,
    TASK_READY,
    TASK_RUNNING
} TaskStatus;

typedef struct {
    uint16_t stack_ptr;
    uint8_t pid;
    task_func task;
    uint8_t status;
    uint16_t delay;
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

void aos_task_switch()
{
     unsigned int* cur_s = task_sp + task_id;
     unsigned int* new_s = cur_s;
     unsigned int* d = task_sleep + task_id;

    __istate_t _istate = __get_interrupt_state();    
    __disable_interrupt(); //由于关闭全局中断会影响cc寄存器，所以先获取cc的值再关闭全局中断

    while (1) {
        if (task_id == 0) {
            task_id = MAX_TASKS - 1;
            new_s = task_sp + MAX_TASKS - 1;
            d = task_sleep + MAX_TASKS - 1;
        } else {
            task_id--;
            new_s--;
            d--;
        }
        if (*d == 0 && *new_s != 0)
            break;
    } 
    
    if (*new_s && cur_s != new_s) {
        if (*cur_s)
            archContextSwitch(cur_s, new_s); //这里切换到新的任务后在新的任务里面会开中断，详细的描述看atom-port-iar.s
        else //当前的任务已经退出，只切换到新的任务就行
            archFirstThreadRestore(new_s); //这里切换到新的任务后在新的任务里面会开中断，详细的描述看atom-port-iar.s
    }
   
    __set_interrupt_state(_istate);
}

//寻找一个空任务,并将任务装入.无空任务时等待.do-while循环中不作任务切换,所以无需支持重入
unsigned char aos_task_load(task_func task)
{
    uint8_t i = 0;
    while (1) {
        for (i = MAX_TASKS; i >= 0; --i) {
            if (aos.tcb_info.stack_ptr == NULL) {
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
    TIM3_EGR_UG = 1;
    TIM3_CR1_CEN = 1;
} 

//========时钟中断函数========================================================
#pragma vector = TIM3_OVR_UIF_vector
__interrupt void clock_timer()
{
     unsigned int* p;
     unsigned char i;

    TIM3_SR1_UIF = 0;
    //任务延迟处理
    i = MAX_TASKS;
    p = task_sleep; 
    do {
        if (*p != 0 && *p != 0xFF)//不为0,也不为0xff,则将任务延时值减1.为0xff表示任务已挂起,不由定时器唤醒
            (*p)--;
        p++;
    } while (--i);
}
