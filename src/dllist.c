#include <stdlib.h>

#define MAX_DLLIST_SIZE 4096

#include "../include/dllist.h"

// Doubly-linked list with O(n/2) worst-case time complexity to add/remove/find an item
// Each node occupies 24b of memory, so a fully loaded list occupies 96kb of memory

dll_t* dll_create(void)
{
    dll_t* dll = malloc(sizeof(dll_t));
    dll->null  = malloc(sizeof(node));
    dll->head  = dll->null;
    dll->tail  = dll->null;
    dll->size  = 0;

    return dll;
}

static void dll_add_only_item(dll_t* dll, Item item)
{
    if (!dll)
        return;

    dll->head = malloc(sizeof(node));
    dll->tail = dll->head;

    dll->head->next = dll->null;
    dll->head->prev = dll->null;
    dll->head->item = item;

    dll->size = 1;
}

static void dll_rm_only_item(dll_t* dll)
{
    if (!dll)
        return;
    
    free(dll->head);

    dll->head = dll->null;
    dll->tail = dll->null;
    dll->size = 0;
}

void dll_insert_last(dll_t* dll, Item item)
{
    if (!dll)
        return;
    
    if (dll->size == 0) {
        dll_add_only_item(dll, item);
        return;
    }
    
    if (dll->size == MAX_DLLIST_SIZE) {
        dll_delete_last(dll);
        return;
    }

    dll->tail->next       = malloc(sizeof(node));
    dll->tail->next->next = dll->null;
    dll->tail->next->prev = dll->tail;
    dll->tail->next->item = item;

    dll->tail = dll->tail->next;

    (dll->size)++;
}

void dll_insert_first(dll_t* dll, Item item)
{
    if (!dll)
        return;
    
    if (dll->size == 0) {
        dll_add_only_item(dll, item);
        return;
    }
    
    if (dll->size == MAX_DLLIST_SIZE) {
        dll_delete_last(dll);
        return;
    }

    dll->head->prev       = malloc(sizeof(node));
    dll->head->prev->prev = dll->null;
    dll->head->prev->next = dll->head;
    dll->head->prev->item = item;

    dll->head = dll->head->prev;

    (dll->size)++;
}

void dll_delete_last(dll_t* dll)
{
    if (!dll || dll->size == 0)
        return;

    if (dll->tail->prev == dll->null) {
        dll_rm_only_item(dll);
        return;
    }
    
    node* temp = dll->tail;

    dll->tail  = dll->tail->prev;
    dll->tail->next = dll->null;
    free(temp);

    (dll->size)--;
}

void dll_delete_first(dll_t* dll)
{
    if (!dll || dll->size == 0)
        return;

    if (dll->head->next == dll->null) {
        dll_rm_only_item(dll);
        return;
    }
    
    node* temp = dll->head;

    dll->head  = dll->head->next;
    dll->head->prev = dll->null;
    free(temp);

    (dll->size)--;
}

void dll_delete_nth_item(dll_t* dll, size_t pos)
{
    if (!dll || dll->size == 0 || pos <= 0 || pos > dll->size)
        return;
    
    if (dll->head->next == dll->null) {
        dll_rm_only_item(dll);
        return;
    }
    
    if (pos == dll->size) {
        dll_delete_last(dll);
        return;
    }
    
    if (pos == 1) {
        dll_delete_first(dll);
        return;
    }
    
    node* iter;
    size_t idx;
    
    if (pos < (dll->size >> 1))
        for(iter = dll->head, idx = 1; idx < pos; iter = iter->next, idx++);
    else
        for(iter = dll->tail, idx = dll->size; idx > pos; iter = iter->prev, idx--);
    
    iter->prev->next = iter->next;
    iter->next->prev = iter->prev;
    free(iter);

    (dll->size)--;
}

void dll_insert_nth_item(dll_t* dll, size_t pos, Item item)
{
    if (!dll || pos < 0 || pos > dll->size + 1)
        return;
    
    if (dll->size == 0) {
        dll_add_only_item(dll, item);
        return;
    }
    
    if (pos == dll->size + 1) {
        dll_insert_last(dll, item);
    }
    
    if (pos == 0) {
        dll_insert_first(dll, item);
    }
    
    node* iter;
    size_t idx;
    
    if (pos < (dll->size >> 1))
        for(iter = dll->head, idx = 1; idx < pos; iter = iter->next, idx++);
    else
        for(iter = dll->tail, idx = dll->size; idx > pos; iter = iter->prev, idx--);
    
    node* new  = malloc(sizeof(node));

    iter->prev->next = new;
    new->prev = iter->prev;

    iter->prev = new;
    new->next = iter;

    (dll->size)++;
}

char* dll_to_str(dll_t* dll)
{
    if (!dll || dll->size == 0)
        return NULL;

    char* buffer = malloc(sizeof(char) * (dll->size + 1));
    
    node* iter;
    size_t idx;

    for (iter = dll->head, idx = 0; idx < dll->size; iter = iter->next, idx++)
        buffer[idx] = (char) iter->item;
    
    buffer[idx] = '\0';
    return buffer;
}