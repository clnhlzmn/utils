# list

A single header implementation of an intrusive circular doubly linked list.

## example

```c
#include <stdio.h>
#include "list.h"

#define CONTAINER_OF(ptr, type, field_name) ((type *)(((char *)ptr) - offsetof(type, field_name)))

struct list my_list;

struct my_list_element {
    int data;
    struct list_element elem;
};

struct my_list_element e0;
struct my_list_element e1;

int main(void) {
    //initialize list
    list_init(&my_list);
    
    //add elements
    eo.data = 0;
    list_element_init(&e0.elem);
    list_append(&my_list, &e0.elem);
    e1.data = 1;
    list_element_init(&e1.elem);
    list_append(&my_list, &e1.elem);
    
    //iterate
    struct list_iterator it;
    list_iterator_init(&it, &my_list);
    struct list_element *current;
    while (list_iterator_next(&it, &current) == 0) {
        struct my_list_element *current_elem = CONTAINER_OF(current, struct my_list_element, elem);
        printf("element with data %d\r\n", current_elem->data);
    }
    return 0;
}

```