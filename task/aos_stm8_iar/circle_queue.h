#ifndef _CIRCLE_QUEUE_H_
#define _CIRCLE_QUEUE_H_

#include <stdint.h>

#define ELEMENT_TYPE uint8_t
#define QUEUE_LEN 10

typedef struct {
    uint8_t front;
    uint8_t end;
    ELEMENT_TYPE array[QUEUE_LEN];
} CircleQueue;

void init(CircleQueue* queue);
void push(CircleQueue* queue, ELEMENT_TYPE* data);
uint8_t pop(CircleQueue* queue, ELEMENT_TYPE* data);
uint8_t full(CircleQueue* queue);
uint8_t empty(CircleQueue* queue);
uint8_t size(CircleQueue* queue);

#endif
