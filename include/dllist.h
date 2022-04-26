#pragma once

#define MAX_DLLIST_SIZE 4096

typedef int Item;

typedef struct lnode lnode;

struct lnode {
    Item   item;
    lnode* next;
    lnode* prev;
};

typedef struct dll dll_t;

struct dll {
    lnode*  head;
    lnode*  tail;
    lnode*  null;
    size_t  size;
};

dll_t* dll_create(void);

void dll_delete_last(dll_t* dll);

void dll_delete_first(dll_t* dll);

void dll_insert_last(dll_t* dll, Item item);

void dll_insert_first(dll_t* dll, Item item);

void dll_delete_nth_item(dll_t* dll, size_t pos);

void dll_insert_nth_item(dll_t* dll, size_t pos, Item item);

void dll_destroy(dll_t** dll);

void dll_print(dll_t* dll);

void dllcat(dll_t* dest, dll_t* src);

void dll_print_ascii(dll_t* dll);