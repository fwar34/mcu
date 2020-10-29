#include "circle_queue.h"

void init(CircleQueue* queue)
{
    queue->front = 0;
    queue->end = 0;
}

void push(CircleQueue* queue, ELEMENT_TYPE* data)
{
    if (++queue->end % QUEUE_LEN == 0) {
        queue->end = 0;
    }

    if (queue->end == queue->front) {
        if (++queue->front % QUEUE_LEN == 0) {
            queue->front = 0;
        }
    }

    queue->array[queue->end] = *data;
}

uint8_t pop(CircleQueue* queue, ELEMENT_TYPE* data)
{
    if (queue->end == queue->front) {
        return 0;
    }

    if (++queue->front % QUEUE_LEN == 0) {
        queue->front = 0;
    }

    *data = queue->array[queue->front];
    queue->array[queue->front] = 0;
    return 1;
}

uint8_t full(CircleQueue* queue)
{
    if (queue->end + 1 % QUEUE_LEN == 0) {
        queue->end = 0;
    }
    return queue->end == queue->front;
}

uint8_t empty(CircleQueue* queue)
{
    return queue->end == queue->front;
}

uint8_t size(CircleQueue* queue)
{
    if (full(queue)) {
        return QUEUE_LEN;
    }

    if (empty(queue)) {
        return 0;
    }

    if (queue->front < queue->end) {
        return queue->end - queue->front;
    } else {
        return QUEUE_LEN - queue->front + queue->end;
    }
}
