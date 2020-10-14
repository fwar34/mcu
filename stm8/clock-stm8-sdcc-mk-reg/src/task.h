#ifndef _TASK_H_
#define _TASK_H_

typedef void (*task_func)();

unsigned char AddTask(unsigned int over_flow_count, task_func tsk, unsigned char repeat);
void RemoveTask(unsigned char task_id);
unsigned char AddMsgTask(unsigned char msg, task_func tsk);
unsigned char PushMsg(unsigned char msg);

void ProcessTask();
void CheckTask();

#endif
