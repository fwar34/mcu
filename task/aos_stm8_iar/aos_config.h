#ifndef _FCONFIG_H_
#define _FCONFIG_H_

#define MAX_TASKS 3
#define MAX_TASK_STACK_LENGTH 64 //最大栈深.最低不得少于2个,保守值为12.

//每个任务支持8个事件，1bit一个
#define EVENT_RF_PULS_SENT 1
#define EVENT_RF_PULS_RECV 2

#define MAX_EVENT_VECTOR 10//向量表的尺寸.最大消息号

#endif
