#include <stdlib.h>
#include <stdio.h>
#include "lib.h"

node * init() {
    return NULL;
};

int push(node *current, int info) {
    node *new_node;
    new_node = (node *) malloc(1*sizeof(node));
    if (new_node != NULL) {
        new_node->info = info;
        new_node->next = new_node->prev = init();
        if (current != NULL)
            new_node->prev = current;
            new_node->next = current->next;
            current->next = new_node;
    } else {
        return 0;
    }

    return 1;
};

int pop(node *current) {
    if (current->prev != NULL) {
        current->prev->next = current->next;
    }
    if (current->next != NULL) {
        current->next->prev = current->prev;
    }
    free(current);
    return 1;
};

void print(node *head) {
    node *test = init();
    test = head;
    do {
        printf("[%x] = %d, ", test, test->info);
        test = test->next;
    } while (test != NULL);
    printf("\n");
};
