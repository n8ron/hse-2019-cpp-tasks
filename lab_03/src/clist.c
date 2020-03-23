#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "clist.h"

bool is_node_presented(struct intrusive_list * list, struct  intrusive_node * node) {
    assert(node != NULL);
    assert(list != NULL);
    struct intrusive_node * check_node = list->head;
    while (check_node != NULL) {
        if (check_node == node) {
            return true;
        }
        check_node = check_node->next;
    }
    return false;
}

void init_list (struct intrusive_list * list) {
	assert(list != NULL);
    list->head = NULL;
}

void add_node (struct intrusive_list * list, struct intrusive_node * node) {
	assert(node != NULL);
	assert(list != NULL);
	assert(!is_node_presented(list, node));
    node->next = list->head;
    node->prev = NULL;
    if (list->head != NULL) {
        list->head->prev = node;
    }
    list->head = node;
}

void remove_node (struct intrusive_list * list, struct  intrusive_node * node) {
    assert(node != NULL);
    assert(list != NULL);
    assert(is_node_presented(list, node));
    if (node == list->head)  {
        if (node->next != NULL) { // удаляем голову, список состоит не только из нее
            node->next->prev = NULL;
        } 
        list->head = node->next;
    }
    else {
        if (node->next == NULL) { //удаляем хвост
            node->prev->next = NULL;
        }
        else { //удаляем элемент из центра
            node->next->prev = node->prev;
            node->prev->next = node->next;
        }
    }    
}

int get_length (struct intrusive_list * list) {
	assert(list != NULL);
    int numb_of_elem = 0;
    struct intrusive_node * counter = list->head;
    while (counter != NULL) {
        numb_of_elem++;
        counter = counter->next;
    }
    return numb_of_elem;
}
