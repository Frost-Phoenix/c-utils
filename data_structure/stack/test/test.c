#include <stdio.h>
#include <criterion/criterion.h>

#include "../include/stack.h"


stack_t stk = {
    .size = 0,
    .head = NULL,
};


void setup(void) {
    stk = (stack_t){
        .size = 0,
        .head = NULL,
    };
}

void teardown(void) {
    stack_free(&stk);
}


Test(stack, test, .init = setup, .fini = teardown) {
    stack_push(&stk, 10);
    stack_push(&stk, 20);
    stack_push(&stk, 30);
    
    cr_expect(stk.size == 3);
    cr_expect(stack_peek(&stk) == 30);

    cr_expect(stack_pop(&stk) == 30);
    cr_expect(stack_pop(&stk) == 20);

    cr_expect(stk.size == 1);
    cr_expect(stack_peek(&stk) == 10);

    cr_expect(stack_pop(&stk) == 10);

    cr_expect(stk.size == 0);
    cr_expect(stk.head == NULL);
}
