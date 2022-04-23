#include <cqueue.h>

// Circular Queue implemented with an array, O(1) time complexity
// for getting the front, size, or dequeuing / enqueuing

cqu_t* cqu_create(size_t maxsize, void (*rmitem)(void *))
{
    cqu_t* queue = malloc(sizeof(cqu_t));
    queue->items = malloc(maxsize * sizeof(void *));

    queue->rmitem  = rmitem;
    queue->maxsize = maxsize;
    queue->front   = 0;
    queue->rear    = -1;
    queue->size    = 0;

    return queue;
}

size_t cqu_size(cqu_t* queue)
{
    return queue->size;
}

bool cqu_is_empty(cqu_t* queue)
{
    return !cqu_size(queue);
}

void* cqu_front(cqu_t* queue)
{
    return cqu_is_empty(queue) ? NULL : queue->items[queue->front];
}

void cqu_enqueue(cqu_t* queue, void* item)
{
    if (cqu_size(queue) == queue->maxsize)
        return;
    
    queue->rear = (queue->rear + 1) % queue->maxsize;
    queue->items[queue->rear] = item;
    (queue->size)++;
}

void cqu_dequeue(cqu_t* queue)
{
    if (cqu_is_empty(queue))
        return;

    queue->rmitem(queue->items[queue->front]);

    queue->front = (queue->front + 1) % queue->maxsize;
    (queue->size)--;
}

void cqu_destroy(cqu_t* queue)
{
    while (!cqu_is_empty(queue))
        cqu_dequeue(queue);

    free(queue->items);
    free(queue);
}