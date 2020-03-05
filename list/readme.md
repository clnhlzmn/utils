# list

An implementation of an intrusive circular doubly linked list and an intrusive singly linked list.

## how to use

### list

1. Include `list.h` and compile `list.c`.
2. Embed a member of type `struct list_element` in your struct that will be a member of a list. To store an object in more than one list at a time it should have another `struct list_element` member for each list. If an object will only be in one list at a time then it needs only one `struct list_element`.
3. Create instances of `struct list` to represent lists.
4. Use `list_append` and/or `list_prepend` to add `struct list_element`s to your list(s).
5. Use `struct list_iterator` and `list_iterator_init`/`list_iterator_next` to traverse your lists.

### slist

1. Include `slist.h` and compile `slist.c`.
2. Embed a member of type `struct slist_element` in the struct that will be a member of a list.
3. Create an instance of `struct slist`.
4. Add elements to the list with `slist_append` and `slist_prepend`. Remove with `slist_remove`.
5. Use `struct slist_iterator` and `slist_iterator_init`/`slist_iterator_next` to traverse your lists.

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
    e0.data = 0;
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

See `test/test_slist.h` for an example of slist.
