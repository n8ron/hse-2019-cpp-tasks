#include <malloc.h>
#include <flite.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "clist.h"

struct point{
    int x, y;
    struct  intrusive_node node;
};

cst_voice *register_cmu_us_kal(const char *voxdir);


void add_point(struct intrusive_list * list, int x, int y) {
    assert(list != NULL);
    struct  point * added_point = malloc(sizeof(struct point));
    added_point->x = x;
    added_point->y = y;
    add_node(list, &added_point->node); 
}

void remove_point(struct intrusive_list * list, int x, int y) { // removes all (x, y) pairs
    assert(list != NULL);
    struct intrusive_node * current_node = list->head;
    struct point * match;
    struct intrusive_node * next_node; 
    while (current_node != NULL) {
        match = container_of(current_node, struct point, node);
        next_node = current_node->next;
        if ((match->x == x) && (match->y == y)) {
            remove_node(list, current_node);
            free(match);
        }
        current_node = next_node;
    }
}

void show_all_points(struct intrusive_list * list) {
    assert(list != NULL);
    cst_voice *v;
    flite_init();
    v = register_cmu_us_kal(NULL);
    char * result = malloc(100000);
    struct intrusive_node * counter = list->head;
    struct point * p; 
    char * s = malloc(4);
    while (counter != NULL) {
        p = container_of(counter, struct point, node);
        sprintf(s,"%d", p->x);
      //  strcat(result, "x is");
        strcat(result, s);

      //  sprintf(s,"%d", p->x);
        strcat(result, "KATYA lokhyshka");
     //   strcat(result, s);
      //  printf("(%d %d) ", p->x, p->y);
        counter = counter->next;
    }

    flite_text_to_speech(result, v, "play");
    free(result);
    free(s);
}

void remove_all_points(struct intrusive_list * list) {
    assert(list != NULL);
    struct intrusive_node * current_node = list->head;
    struct point * match;
    struct intrusive_node * next_node;  
    while (current_node != NULL) {
        match = container_of(current_node, struct point, node);
        next_node = current_node->next;
        remove_node(list, current_node);
        free(match);
        current_node = next_node;
    }
}

int main() {
    int x, y;
    struct intrusive_list * list = malloc(sizeof(struct intrusive_list));
    init_list (list);
    char * command = malloc(240*sizeof(char));
    command[239] = '\0';
    while (1) {
        scanf("%239s", command);
        if (strcmp(command, "add") == 0) {
            scanf("%d%d", &x, &y);
            add_point(list, x, y);
        }
        else if (strcmp(command, "rm") == 0) {
            scanf("%d%d", &x, &y);
            remove_point(list, x, y);
        }
        else if (strcmp(command, "print") == 0) {
            show_all_points(list);
        }
        else if (strcmp(command, "rma") == 0) {
            remove_all_points(list);
        }
        else if (strcmp(command, "len") == 0) {
            printf("%d", get_length(list));
            printf("\n");
        }
        else if (strcmp(command, "exit") == 0) {
            break;  
        }
        else {
            printf("%s", "Unknown command\n");
        }   
    }
    remove_all_points(list);
    free(list);
    free(command);
    return 0;
}