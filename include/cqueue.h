#pragma once

#include <stdlib.h>
#include <stdbool.h>

typedef struct cqu cqu_t;

struct cqu {
    void**  items;
    void  (*rmitem)(); // function to clear memory for an item
    size_t  maxsize;
    size_t  size;
    ssize_t front;
    ssize_t rear;
};

cqu_t* cqu_create(size_t maxsize, void (*rmitem)());

size_t cqu_size(cqu_t* queue);

bool cqu_is_empty(cqu_t* queue);

void* cqu_front(cqu_t* queue);

void cqu_enqueue(cqu_t* queue, void* item);

void cqu_dequeue(cqu_t* queue);

void cqu_destroy(cqu_t* queue);