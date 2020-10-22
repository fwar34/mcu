/* #include <iostm8.h> */
/* #include <absacc.h> */
#include "task.h"

/*============================以下为任务管理器代码============================*/

unsigned char  event_vector[MAX_EVENT_VECTOR];//消息钩子

unsigned char task_id;
unsigned int task_sp[MAX_TASKS];//任务的栈指针
unsigned char task_stack[MAX_TASKS][MAX_TASK_DEP];//任务堆栈.
unsigned char task_sleep[MAX_TASKS];//任务睡眠定时器

void task_init()
{
    register unsigned char i;
    i = MAX_EVENT_VECTOR;
    do
    {
        /* event_vector[i-1] = -1; */
        event_vector[i - 1] = 0xFF;
    } while (--i);
}

//任务切换函数(任务调度器)
//任务切换函数(任务调度器)
void task_switch()
{
    register unsigned int* cur_s = task_sp + task_id;
    register unsigned int* new_s = cur_s;
    register unsigned char* d = task_sleep + task_id;

    register unsigned char cc = get_cc();
    disableInterrupts();

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

    if (*new_s && new_s != cur_s) {
        if (*cur_s)
            archContextSwitch(cur_s, new_s);        
        else //当前任务已经退出就不用保存当前任务了，只用切换到新的任务就行
            archFirstThreadRestore(new_s);
    }

    set_cc(cc);
}

//寻找一个空任务,并将任务装入.无空任务时等待.do-while循环中不作任务切换,所以无需支持重入
unsigned char task_load(unsigned int fn)
{
    register unsigned char i;//关键函数内不应使用局部变量.虽然变量在使用期间内无任务切换,但有可能产生覆盖问题
    register unsigned char* p;
    while (1) {
        i = MAX_TASKS;
        do {
            if (task_sp[i - 1] == 0) {
                p = task_stack[i - 1] + MAX_TASK_DEP - 1;
                *p-- = fn & 0xff;
                *p-- = fn >> 8;
                task_sp[i - 1] = (unsigned int)p;
                task_sleep[i - 1] = 0;
                return i - 1;
            }
        } while (--i);
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
/* #pragma SAVE */
/* #pragma NOAREGS */
/* void clock_timer(void) __interrupt 1 using 1 */
void clock_timer() __interrupt 15
{
    register unsigned char* p;
    register unsigned char i;

    //任务延迟处理
    i = MAX_TASKS;
    p = task_sleep; 
    do {
        /* if(*p != 0 && *p != -1)//不为0,也不为0xff,则将任务延时值减1.为0xff表示任务已挂起,不由定时器唤醒 */
        if (*p != 0 && *p != 0xFF)//不为0,也不为0xff,则将任务延时值减1.为0xff表示任务已挂起,不由定时器唤醒
            (*p)--;
        p++;
    } while (--i);
}

/* #pragma RESTORE */
