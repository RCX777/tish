typedef int Item;

typedef struct node node;

struct node {
    Item  item;
    node* next;
    node* prev;
};

typedef struct dll dll_t;

struct dll {
    node*  head;
    node*  tail;
    node*  null;
    size_t size;
};

dll_t* dll_create(void);

void dll_insert_last(dll_t* dll, Item item);

void dll_insert_first(dll_t* dll, Item item);

void dll_delete_last(dll_t* dll);

void dll_delete_first(dll_t* dll);

void dll_delete_nth_item(dll_t* dll, size_t pos);

void dll_insert_nth_item(dll_t* dll, size_t pos, Item item);

char* dll_to_str(dll_t* dll);

