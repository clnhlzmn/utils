
#include <stdio.h>
#include <assert.h>
#include "../slist.h"

#define CONTAINER_OF(ptr, type, field_name) ((type *)(((char *)ptr) - offsetof(type, field_name)))

struct my_list_element {
    struct slist_element element;
    int value;
};

struct slist my_list;

struct slist my_list2;

int main(void) {
    //initialize
    assert(slist_init(&my_list) == 0);
    slist_init(&my_list2);
    
    //check empty
    bool is_empty;
    assert(slist_is_empty(&my_list, &is_empty) == 0);
    assert(is_empty);
    
    //create element
    struct my_list_element e0;
    assert(slist_element_init(&e0.element) == 0);
    e0.value = 0;
    
    //prepend to my_list
    assert(slist_prepend(&my_list, &e0.element) == 0);
    assert(slist_is_empty(&my_list, &is_empty) == 0);
    assert(!is_empty);
    
    //another element
    struct my_list_element e1;
    slist_element_init(&e1.element);
    e1.value = 1;
    assert(slist_append(&my_list, &e1.element) == 0);
    
    //iterator
    struct slist_iterator my_iterator;
    assert(slist_iterator_init(&my_iterator, &my_list) == 0);
    
    //get first element
    struct slist_element *current;
    assert(slist_iterator_next(&my_iterator, &current) == 0);
    struct my_list_element *element = CONTAINER_OF(current, struct my_list_element, element);
    assert(element->value == 0);
    
    //get second element
    assert(slist_iterator_next(&my_iterator, &current) == 0);
    element = CONTAINER_OF(current, struct my_list_element, element);
    assert(element->value == 1);
    
    //no more elements
    assert(slist_iterator_next(&my_iterator, &current) != 0);
    
    //remove element (end element)
    assert(slist_remove(&my_list, &e1.element) == 0);

    //recheck list
    assert(slist_iterator_init(&my_iterator, &my_list) == 0);
    assert(slist_iterator_next(&my_iterator, &current) == 0);
    element = CONTAINER_OF(current, struct my_list_element, element);
    assert(element->value == 0);
    
    //remove another element (first element)
    assert(slist_remove(&my_list, &e0.element) == 0);
    
    //recheck list
    assert(slist_iterator_init(&my_iterator, &my_list) == 0);
    assert(slist_iterator_next(&my_iterator, &current) != 0);
    
    //try to remove again
    assert(slist_remove(&my_list, &e0.element) != 0);
    
    //add items to list again
    slist_prepend(&my_list2, &e1.element);
    slist_prepend(&my_list2, &e0.element);
    
    //remove head
    struct slist_element *head;
    //should be e0
    assert(slist_remove_head(&my_list2, &head) == 0);
    element = CONTAINER_OF(head, struct my_list_element, element);
    assert(element->value == 0);
    //should be e1
    assert(slist_remove_head(&my_list2, &head) == 0);
    element = CONTAINER_OF(head, struct my_list_element, element);
    assert(element->value == 1);
    //no head
    assert(slist_remove_head(&my_list2, &head) != 0);
    
    printf("tests passed\r\n");
    return 0;
}