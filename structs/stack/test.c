#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    //STACK TESTS START
    stack_lib *stack_func = create_stack_library();
    stack *test_stack = stack_func->create_stack();
    for (int i = 0; i < 100; i++)
    {
        int *k = (int *)malloc(sizeof(int));
        *k = i;
        stack_func->push_front(test_stack, k);
    }
    printf("%d\n", *(int *)stack_func->top(test_stack));
    stack_func->pop_front(test_stack);
    stack_func->pop_front(test_stack);
    stack_func->pop_front(test_stack);
    stack_func->pop_front(test_stack);
    printf("%d\n", *(int *)stack_func->top(test_stack));
    free(stack_func);
    //STACK TESTS END
    return 0;
}