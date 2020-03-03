
#include <stdio.h>
#include <assert.h>
#include "../list.h"

#define CONTAINER_OF(ptr, type, field_name) ((type *)(((char *)ptr) - offsetof(type, field_name)))

struct my_list_element {
    struct list_element element;
    int value;
};

struct list my_list = LIST_INIT(my_list);

struct list my_list2;

int main(void) {
    //initialize
    assert(list_init(&my_list2) == 0);
    
    //check empty
    bool is_empty;
    assert(list_is_empty(&my_list, &is_empty) == 0);
    assert(is_empty);
    
    //create element
    struct my_list_element e0;
    assert(list_element_init(&e0.element) == 0);
    e0.value = 0;
    
    //should not be in a list yet
    bool in_list;
    assert(list_element_in_list(&e0.element, &in_list) == 0);
    assert(!in_list);
    
    //prepend to my_list
    assert(list_prepend(&my_list, &e0.element) == 0);
    assert(list_prepend(&my_list, &e0.element) != 0);
    assert(list_element_in_list(&e0.element, &in_list) == 0);
    assert(in_list);
    assert(list_is_empty(&my_list, &is_empty) == 0);
    assert(!is_empty);
    
    
    //another element
    struct my_list_element e1;
    list_element_init(&e1.element);
    e1.value = 1;
    assert(!list_contains(&my_list, &e1.element));
    assert(list_append(&my_list, &e1.element) == 0);
    assert(list_append(&my_list, &e1.element) != 0);
    
    //list contains
    assert(list_contains(&my_list, &e0.element));
    assert(list_contains(&my_list, &e1.element));
    
    //iterator
    struct list_iterator my_iterator;
    assert(list_iterator_init(&my_iterator, &my_list) == 0);
    
    //get first element
    struct list_element *current;
    assert(list_iterator_next(&my_iterator, &current) == 0);
    struct my_list_element *element = CONTAINER_OF(current, struct my_list_element, element);
    assert(element->value == 0);
    
    //get second element
    assert(list_iterator_next(&my_iterator, &current) == 0);
    element = CONTAINER_OF(current, struct my_list_element, element);
    assert(element->value == 1);
    
    //get first element (list_iterator_previous)
    assert(list_iterator_previous(&my_iterator, &current) == 0);
    element = CONTAINER_OF(current, struct my_list_element, element);
    assert(element->value == 0);
    
    //can't go back further
    assert(list_iterator_previous(&my_iterator, &current) != 0);
    
    //remove element
    assert(list_remove(&my_list, &e1.element) == 0);

    //recheck list
    assert(list_iterator_init(&my_iterator, &my_list) == 0);
    assert(list_iterator_next(&my_iterator, &current) == 0);
    element = CONTAINER_OF(current, struct my_list_element, element);
    assert(element->value == 0);
    
    //remove another element
    assert(list_remove(&my_list, &e0.element) == 0);
    
    //recheck list
    assert(list_iterator_init(&my_iterator, &my_list) == 0);
    assert(list_iterator_next(&my_iterator, &current) != 0);
    
    //try to remove again
    assert(list_remove(&my_list, &e0.element) != 0);
    
    list_append(&my_list, &e0.element);
    list_append(&my_list, &e1.element);
    
    assert(list_clear(&my_list) == 0);
    list_is_empty(&my_list, &is_empty);
    assert(is_empty == true);
    
    printf("tests passed\r\n");
    return 0;
}