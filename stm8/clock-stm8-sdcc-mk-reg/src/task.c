#include "task.h"
#include "uart_sdcc.h"

#define task_len 20

uint8_t loop_task_flag = 0;
uint8_t once_task_flag = 0;
uint8_t msg_task_flag = 0;

typedef struct _Task {
    uint8_t is_vaild_;
    uint16_t over_flow_count_;
    uint16_t count_;
    void* task_func_;
    void* data_;
} Task;

typedef struct _MsgTaskList {
    uint8_t msg_queue_[task_len];
    uint8_t msg_[task_len];
    task_func2 msg_func_[task_len];
} MsgTaskList;

Task loop_task_list[task_len];
Task once_task_list[task_len];
MsgTaskList msg_task_list;

uint8_t AddLoopTask(uint8_t over_flow_count, void* tsk, void* data)
{
    uint8_t i = 0;
    for (; i < task_len; ++i) {
        if (!loop_task_list[i].is_vaild_) {
            loop_task_list[i].is_vaild_ = 1;
            loop_task_list[i].count_ = 0;
            loop_task_list[i].over_flow_count_ = over_flow_count;
            loop_task_list[i].task_func_ = tsk;
            loop_task_list[i].data_ = data;
            return 1;
        }
    }
    return 0;
}

uint8_t AddOnceTask(uint8_t over_flow_count, void* tsk, void* data)
{
    uint8_t i = 0;
    for (; i < task_len; ++i) {
        if (!once_task_list[i].is_vaild_) {
            once_task_list[i].is_vaild_ = 1;
            once_task_list[i].count_ = 0;
            once_task_list[i].over_flow_count_ = over_flow_count;
            once_task_list[i].task_func_ = tsk;
            once_task_list[i].data_ = data;
            return 1;
        }
    }
    return 0;
}

uint8_t AddMsgTask(uint8_t msg, task_func2 tsk)
{
    uint8_t i = 0;
    for (; i < task_len; ++i) {
        if (!msg_task_list.msg_[i]) {
             msg_task_list.msg_[i] = msg;
             msg_task_list.msg_func_[i] = tsk;
             return 1;
        }
    }
    return 0;
}

uint8_t PushMsg(uint8_t msg)
{
    uint8_t i = 0;
    for (; i < task_len; ++i) {
        if (!msg_task_list.msg_queue_[i]) {
             msg_task_list.msg_queue_[i] = msg;
             return 1;
        }
    }
    return 0;
}

void ProcessLoopTask()
{
    if (!loop_task_flag) {
        return;
    }
    loop_task_flag = 0;

    uint8_t i = 0;
    for (; i < task_len; ++i) {
        if (loop_task_list[i].is_vaild_) {
            ++loop_task_list[i].count_;
            /* if (i == 5) { */
            /*     uart_send_hex(i); */
            /*     uart_send_string(":"); */
            /*     uart_send_hex((loop_task_list[i].count_) >> 8); */
            /*     uart_send_hex((uint8_t)(loop_task_list[i].count_)); */
            /* } */
            if (loop_task_list[i].count_ >= loop_task_list[i].over_flow_count_) {
                loop_task_list[i].count_ = 0;
                if (loop_task_list[i].data_) {
                    task_func func = (task_func)(loop_task_list[i].task_func_);
                    func(loop_task_list[i].data_);
                } else {
                    task_func2 func = (task_func)(loop_task_list[i].task_func_);
                    func();
                }
            }
        } else {
            return;
        }
    }
}

void ProcessOnceTask()
{
    if (!once_task_flag) {
        return;
    }
    once_task_flag = 0;

    uint8_t i = 0;
    for (; i < task_len; ++i) {
        if (once_task_list[i].is_vaild_) {
            if (++once_task_list[i].count_ >= loop_task_list[i].over_flow_count_) {
                once_task_list[i].is_vaild_ = 0;
                if (loop_task_list[i].data_) {
                    task_func func = (task_func)(once_task_list[i].task_func_);
                    func(once_task_list[i].data_);
                } else {
                    task_func2 func = (task_func)(once_task_list[i].task_func_);
                    func();
                }
            }
        }
    }
}

void ProcessMsgTask()
{
    if (!msg_task_flag) {
        return;
    }
    msg_task_flag = 0;

    uint8_t i = 0;
    uint8_t j = 0;
    for (; i < task_len; ++i) {
        if (msg_task_list.msg_queue_[i]) {
            for (; j < task_len; ++j) {
                if (msg_task_list.msg_queue_[i] == msg_task_list.msg_[j]) {
                    msg_task_list.msg_func_[j]();
                }
            }
        }
    }
}
