#if !defined(STACK_H)
#define STACK_H

#include <stdint.h>
#include <stdlib.h>


typedef struct node {
    uint8_t data;
    struct node* next;
} node_t;

typedef struct stack {
    size_t size;
    struct node* head;
} stack_t;


void stack_push(stack_t* stk, uint8_t data);
uint8_t stack_pop(stack_t* stk);
uint8_t stack_peek(stack_t* stk);
int stack_is_empty(stack_t* stk);

void stack_print(stack_t* stk);

void stack_free(stack_t* stk);

#endif /* STACK_H */