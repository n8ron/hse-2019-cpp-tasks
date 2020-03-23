#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>
#include "point_list.h"
#include "clist.h"

#define container_of(ptr, type, member) (type*)((char*)(ptr) - offsetof(type, member))

point_node * get_point(intrusive_node * node) {
    assert(node != NULL);
    return container_of(node, point_node, node);
}

int match_point(intrusive_node *node, int x, int y) {
    assert(node != NULL);
    point_node *pnode = get_point(node);
    return pnode->x == x && pnode->y == y;
}

void delete_point(intrusive_node *node) {
    assert(node != NULL);
    remove_node(node);
    free(get_point(node));
}

void print_point(intrusive_node *node) {
    assert(node != NULL);
    point_node *pnode = get_point(node);
    printf("(%d, %d)", pnode->x, pnode->y);
}

void remove_point(intrusive_list *list, int x, int y) {
    assert(list != NULL);
    intrusive_node *head = &list->head;
    intrusive_node *node = head->next;
    while (node != head) {
        intrusive_node *next = node->next;
        if (match_point(node, x, y))
            delete_point(node);
        node = next;
    }
}

void add_point(intrusive_list *list, int x, int y) {
    assert(list != NULL);
    point_node *pnode = malloc(sizeof(point_node));
    pnode->x = x;
    pnode->y = y;
    add_node(list, &pnode->node);
}

void show_all_points(intrusive_list *list) {
    assert(list != NULL);
    intrusive_node *head = &list->head;
    intrusive_node *node = head->next;
    printf("%d: ", get_length(list));
    for (int i = 0; node != head; i++, node = node->next) {
        if (i) printf(" ");
        print_point(node);
    }
    printf("\n");
}

void remove_all_points(intrusive_list *list) {
    assert(list != NULL);
    while (list->head.next != &list->head)
        delete_point(list->head.next);
}
