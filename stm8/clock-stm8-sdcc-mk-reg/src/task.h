//https://www.bilibili.com/video/BV1v54y1U7P3?p=5
#ifndef _TASK_H_
#define _TASK_H_

#include <stdint.h>

extern uint8_t loop_task_flag;
extern uint8_t once_task_flag;
extern uint8_t msg_task_flag;

typedef void (*task_func)(void* data);
typedef void (*task_func2)();
uint8_t AddLoopTask(uint8_t over_flow_count, void* tsk, void* data);
uint8_t AddOnceTask(uint8_t over_flow_count, void* tsk, void* data);
uint8_t AddMsgTask(uint8_t msg, task_func2 tsk);
uint8_t PushMsg(uint8_t msg);

void ProcessLoopTask();
void ProcessOnceTask();
void ProcessMsgTask();

#endif
