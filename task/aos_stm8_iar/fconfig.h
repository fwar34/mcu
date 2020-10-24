#ifndef _FCONFIG_H_
#define _FCONFIG_H_

#define MAX_TASKS 3
#define MAX_TASK_STACK_LENGTH 32 //最大栈深.最低不得少于2个,保守值为12.

//消息号在此处定义.不得重复.
#define EVENT_RF_PULS_SENT	0
#define EVENT_RF_PULS_RECV	1

#define MAX_EVENT_VECTOR 8//向量表的尺寸.必须 >= 最大消息号 +1 .

#endif
