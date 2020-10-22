/*============================以下为任务管理器代码============================*/

/*
  关于消息机制:
  该系统的消息机制其实并不是真正的消息机制,其过程是依靠休眠和唤醒来实现的.机制是这样的:

  当一个进程需要等待某消息时,实际上是将进程的task_id保存在消息向量表中,然后进入休眠/延时状态.
  此后事件发生时,系统直接根据消息号从向量表中找到等待它的进程的task_id,然后将其唤醒.整个过程中并没有真正的消息在传递.

  使用这机的方式实现消息,执行效率较高,但有一些限制,使用时应注意并避过:
  1.进程必须在进入休眠/延时后才能收到消息
  2.进程虽可同时等待多个消息,但由于无法知道消息的内容,所以除非在事件发生处额外作标记(定义变量)供进程辨认,否则不要同时等待多个消息
*/
#include "iostm8.h"

//extern void* _get_SP();
//extern void _set_SP(void* sp);

extern void archContextSwitch (unsigned int *cur_s, unsigned int *new_s);                                                   
extern void archFirstThreadRestore(unsigned int *sp);

//消息号在此处定义.不得重复.
#define EVENT_RF_PULS_SENT	0
#define EVENT_RF_PULS_RECV	1

#define MAX_EVENT_VECTOR 8//向量表的尺寸.必须 >= 最大消息号 +1 .
extern unsigned char  event_vector[MAX_EVENT_VECTOR];//消息向量,每项保存一个task_id号,指向监听它的进程(task_id).无监者时应置为-1

//注册指定消息.当该消息发生时,系统将唤醒注册者.
#define event_replace(eid) event_vector[eid] = task_id

//清除指定消息
#define event_clear(eid) event_vector[eid] = -1

//保存指定消息到reg中(unsigned char类型)的原注册者,并监听该消息.
#define event_reg(eid, reg) reg = event_vector[eid], event_vector[eid] = task_id

//从reg中(unsigned char类型)恢复指定消息的原注册者
#define event_unreg(eid, reg) event_vector[eid] = reg

//发送消息(严格地说,是唤醒监听者)
/* #define event_push(eid) { if(event_vector[eid] != -1) task_wakeup(event_vector[eid]); } */
#define event_push(eid) { if(event_vector[eid] != 0xFF) task_wakeup(event_vector[eid]); }

typedef void (*task_func)();


#define MAX_TASKS 3

//任务的栈指针
extern unsigned int task_sp[MAX_TASKS];
                                                                                
#define MAX_TASK_DEP 32 //最大栈深.最低不得少于2个,保守值为12.
//预估方法:以2为基数,每增加一层函数调用,加2字节.如果其间可能发生中断,则还要再加上中断需要的栈深.
//减小栈深的方法:1.尽量少嵌套子程序 2.调子程序前关中断.
extern unsigned char  task_stack[MAX_TASKS][MAX_TASK_DEP];//任务堆栈.
extern unsigned int  task_sleep[MAX_TASKS];//任务睡眠定时器

extern unsigned char task_id;//当前活动任务

void task_init();

//立即释放CPU,并在执行过其它全部未休眠的进程后回到释放点
void task_switch();

//装载进程.如果任务槽满,则延时两个定时器中断周期,直到有空槽为止
unsigned char task_load(unsigned int fn);

//设置指定的进程为休眠状态.
#define task_setsuspend(tid) task_sleep[tid] = 0xFF;

//设置指定的进程为延时状态
#define task_setsleep(tid, timer) task_sleep[tid] = timer

//唤醒指定的进程.
#define task_wakeup(tid) task_sleep[tid] = 0

//进程立即进入延时
#define task_sleep(timer) task_sleep[task_id] = timer, task_switch()

//进程立即进入休眠
/* #define task_suspend() task_sleep[task_id] = -1, task_switch() */
#define task_suspend() task_sleep[task_id] = 0xFF, task_switch()

//执行指定语句后进入休眠.与直接调用task_suspend()相比,可防止中断中的消息在提前到达于进入休眠等待前.
#define task_wait_interrupt(prog) { task_setsuspend(task_id); prog; task_switch(); }
/*task_wait_interrupt()的详细说明:
  出于执行效率的考虑,该系统的消息发送是有"BUG"的:进程必须未在活动中("未活动"是指 1.进入休眠 2.延时状态后)才能收到消息.
  具休地说就是,如果进程监听的消息产生于中断中,而该监听者当前正处于活动状态,则进程无法收到消息,

  假定以下应用环境:

  1.进程T1监听消息S1,然后向缓冲区BUFF写数据,接下来等待S1的产生
  2.中断服务程序检查缓冲区BUFF,发现有数据则处理,并在处理完后发送信号S1

  现在假定T1刚写完缓冲区,中断正好发生,并在处理完后发送信号S1,而此时T1并未进入信号等待阶段.
  当中断服务退出后,T1不知道S1已经发生了,继续按预定程序进入信号等待阶段,于是死在那里.

  调用task_wait_interrupt()宏可解决该问题.该宏实际上是先置进程为等待状态,然后才执行缓冲区操作.
  用户可按自已的喜好选择调用该宏,或直接书写为展开之后的代码:

  task_setsuspend(task_id);
  操作缓冲区的代码;
  task_switch();

*/
//与task_wait_interrupt()类似,但只在指定的时间内等待,而task_wait_interrupt()会永远等待.
#define task_sleep_interrupt(prog) task_setsleep(task_id), prog, task_switch()

//退出当然进程.如该进程注册了信号,则必须在退出前恢复/清理
#define task_exit() task_sp[task_id] = 0, task_switch()

//结束指定的进程
#define task_delete(tid) task_sp[tid] = 0

//启动任务调度.从最先压入的任务开始执行.
/* /\* #define os_start() task_id = MAX_TASKS - 1, SP = task_sp[MAX_TASKS - 1], EA = 1 *\/ */
#define os_start() task_id = MAX_TASKS - 1, archFirstThreadRestore(task_sp + MAX_TASKS - 1)
/* #define os_start()                                                      \ */
/*     task_id = MAX_TASKS - 1;                                            \ */
/*     __asm                                                               \ */
/*     ldw sp, (_task_sp, _task_id)                                        \ */
    /* __endasm */               

void clock_init();
void timer3_init();
