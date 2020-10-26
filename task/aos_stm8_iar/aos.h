#ifndef _AOS_H_
#define _AOS_H_
/*
  关于消息机制:
  该系统的消息机制其实并不是真正的消息机制,其过程是依靠休眠和唤醒来实现的.机制是这样的:

  当一个进程需要等待某消息时,实际上是将进程的task_id保存在消息向量表中,然后进入休眠/延时状态.
  此后事件发生时,系统直接根据消息号从向量表中找到等待它的进程的task_id,然后将其唤醒.整个过程中并没有真正的消息在传递.

  使用这机的方式实现消息,执行效率较高,但有一些限制,使用时应注意并避过:
  1.进程必须在进入休眠/延时后才能收到消息
  2.进程虽可同时等待多个消息,但由于无法知道消息的内容,所以除非在事件发生处额外作标记(定义变量)供进程辨认,否则不要同时等待多个消息
*/

typedef void (*task_func)();
//注册指定消息.当该消息发生时,系统将唤醒注册者.
#define event_replace(eid) event_vector[eid] = task_id
//清除指定消息
#define event_clear(eid) event_vector[eid] = -1
//保存指定消息到reg中(unsigned char类型)的原注册者,并监听该消息.
#define event_reg(eid, reg) reg = event_vector[eid], event_vector[eid] = task_id
//从reg中(unsigned char类型)恢复指定消息的原注册者
#define event_unreg(eid, reg) event_vector[eid] = reg
//发送消息(严格地说,是唤醒监听者)
#define event_push(eid) { if(event_vector[eid] != 0xFF) task_wakeup(event_vector[eid]); }
//初始化
void aos_init();
//启动任务调度.从最先添加的任务开始执行.
void aos_start();
//退出当前任务.如该任务注册了信号,则必须在退出前恢复/清理
void aos_task_exit();
//立即释放CPU,并在执行过其它全部未休眠的进程后回到释放点
void aos_task_switch();
//装载进程.如果任务槽满,则延时两个定时器中断周期,直到有空槽为止
unsigned char aos_task_load(unsigned int fn);
//设置指定的进程为休眠状态.
#define task_setsuspend(tid) task_sleep[tid] = 0xFF;
//设置指定的进程为延时状态
#define task_setsleep(tid, timer) task_sleep[tid] = timer
//唤醒指定的进程.
#define task_wakeup(tid) task_sleep[tid] = 0
//进程立即进入延时
#define task_sleep(timer) task_sleep[task_id] = timer, task_switch()
//进程立即进入休眠
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
//结束指定的进程
/* #define task_delete(tid) task_sp[tid] = 0 */

#endif
