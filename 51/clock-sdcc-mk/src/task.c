#include "task.h"

#define task_len 20

typedef struct _Task {
    unsigned char is_vaild_;
    unsigned int over_flow_count_;
    unsigned int count_;
    task_func task_func_;
    unsigned char ready_;
    unsigned char repeat_;
} Task;

typedef struct _MsgTask {
    unsigned int msg_;
    task_func msg_func_;
    unsigned char ready_;
} MsgTask;

Task task_list[task_len];
unsigned char msg_queue[task_len];
MsgTask msg_task_list[task_len];

unsigned char AddTask(unsigned int over_flow_count, task_func tsk, unsigned char repeat)
{
    unsigned char i = 1;
    for (; i < task_len; ++i) {
        if (!task_list[i].is_vaild_) {
            task_list[i].count_ = 0;
            task_list[i].over_flow_count_ = over_flow_count;
            task_list[i].task_func_ = tsk;
            task_list[i].ready_ = 0;
            task_list[i].repeat_ = repeat;
            //设置is_vaild_标志必须放到最后，防止函数指针和其他信息还没有设置，定时器都已经开始++count_了
            task_list[i].is_vaild_ = 1; 
            return i;
        }
    }

    return 0;
}

void RemoveTask(unsigned char task_id)
{
    task_list[task_id].is_vaild_ = 0;
}

unsigned char AddMsgTask(unsigned char msg, task_func tsk)
{
    unsigned char i = 0;
    for (; i < task_len; ++i) {
        if (!msg_task_list[i].msg_) {
             msg_task_list[i].msg_ = msg;
             msg_task_list[i].msg_func_ = tsk;
             return 1;
        }
    }
    return 0;
}

unsigned char PushMsg(unsigned char msg)
{
    unsigned char i = 0;
    for (; i < task_len; ++i) {
        if (!msg_task_list[i].msg_) {
             msg_task_list[i].msg_ = msg;
             return 1;
        }
    }
    return 0;
}

void ProcessTask()
{
    unsigned char i = 0;
    for (; i < task_len; ++i) {
        if (task_list[i].is_vaild_ && task_list[i].ready_) {
            
            if (!task_list[i].repeat_) {
                //这个is_vaild_状态设置必须放到下面的task_list[i].task_func_();前面，
                //因为在task_func_()中有可能刚添加一个非周期任务，
                //如果放到task_func_()的前面，就会把刚添加的这个非周期任务设置成无效的，
                //导致这个非周期任务添加了也不会执行
                task_list[i].is_vaild_ = 0;
            }
            task_list[i].ready_ = 0;
            task_list[i].task_func_();
        }
    }

    for (; i < task_len; ++i) {
        if (msg_task_list[i].msg_ && msg_task_list[i].ready_) {
            msg_task_list[i].ready_ = 0;
            msg_task_list[i].msg_func_();
        }
    }
}

void CheckTask()
{
    unsigned char i = 0;
    unsigned char j = 0;

    //check task
    for (i = 1; i < task_len; ++i) {
        if (task_list[i].is_vaild_) {
            ++task_list[i].count_;
            if (task_list[i].count_ >= task_list[i].over_flow_count_) {
                task_list[i].count_ = 0;
                task_list[i].ready_ = 1;
            }
        }
    }

    //check msg task
    for (i = 0; i < task_len; ++i) {
        if (msg_queue[i]) {
            for (; j < task_len; ++j) {
                if (msg_task_list[i].msg_ == msg_queue[i]) {
                    msg_task_list[i].ready_ = 1;
                }
            }
        }
    }
}
