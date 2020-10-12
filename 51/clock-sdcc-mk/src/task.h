//https://www.bilibili.com/video/BV1v54y1U7P3?p=5
#ifndef _TASK_H_
#define _TASK_H_

typedef void (*task_func)();
unsigned char AddLoopTask(unsigned char over_flow_count, task_func tsk);
unsigned char AddOnceTask(unsigned char over_flow_count, task_func tsk);
unsigned char AddMsgTask(unsigned char msg, task_func tsk);
unsigned char PushMsg(unsigned char msg);

void ProcessTask();
void CheckTask();

#endif
