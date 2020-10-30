#ifndef _CIRCLE_QUEUE_H_
#define _CIRCLE_QUEUE_H_

#include <stdint.h>

#define ELEMENT_TYPE uint8_t
#define QUEUE_LEN 10

typedef struct {
    uint8_t front; //第一个元素的索引是front + 1
    uint8_t end; //最后一个元素的所以是end
    ELEMENT_TYPE array[QUEUE_LEN + 1]; //要存QUEUE_LEN个元素数组必须是QUEUE_LEN + 1大小,因为front + 1才是第一个元素
} CircleQueue;

void init(CircleQueue* queue);
void push(CircleQueue* queue, ELEMENT_TYPE* data);
uint8_t pop(CircleQueue* queue, ELEMENT_TYPE* data);
uint8_t full(CircleQueue* queue);
uint8_t empty(CircleQueue* queue);
uint8_t size(CircleQueue* queue);

#endif
