#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


#include "../include/stack.h"


static node_t* stack_init_node(uint8_t data) {
    node_t* node = (node_t*)malloc(sizeof(node_t));


    if (node == NULL) {
        return NULL;
    }

    node->data = data;
    node->next = NULL;

    return node;
}

void stack_push(stack_t* stk, uint8_t data) {
    node_t* node = stack_init_node(data);

    node->next = stk->head;
    stk->head = node;
    stk->size++;
}

uint8_t stack_pop(stack_t* stk) {
    if (stk->size == 0) {
        fprintf(stderr, "[ERROR] Try to pop from empty stack\n");
        return 0;
    }
    uint8_t data = stk->head->data;

    node_t* old = stk->head;
    stk->head = stk->head->next;

    free(old);
    stk->size--;

    return data;
}

uint8_t stack_peek(stack_t* stk) {
    if (stk->size == 0) {
        fprintf(stderr, "[ERROR] Try to peek empty stack\n");
        return 0;
    }
    return stk->head->data;
}

int stack_is_empty(stack_t* stk) {
    return stk->size == 0;
}

void stack_free(stack_t* stk) {
    while (stk->head) {
        (void)stack_pop(stk);
    }
}

void stack_print(stack_t* stk) {
    printf("Stack (size %ld): ", stk->size);

    node_t* node = stk->head;
    while (node) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}
