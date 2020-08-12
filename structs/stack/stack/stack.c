#include "stack.h"

typedef struct stack
{
    list *stack;
} stack;

static void pop_front(stack *obj);
static void clear(stack *obj);
static void push_front(stack *obj, void *data);
static void *top(stack *obj);
static stack *create_stack();

static void pop_front(stack *obj)
{
    list_lib *lib_list = create_list_library();
    lib_list->pop_front(obj->stack);
    free(lib_list);
}

static void clear(stack *obj)
{
    list_lib *lib_list = create_list_library();
    lib_list->clear(obj->stack);
    free(lib_list);
}

static void push_front(stack *obj, void *data)
{
    list_lib *lib_list = create_list_library();
    lib_list->push_front(obj->stack, data);
    free(lib_list);
}

static void *top(stack *obj)
{
    list_lib *lib_list = create_list_library();
    void *result = lib_list->get_by_index(obj->stack, 0);
    free(lib_list);
    return result;
}

static stack *create_stack()
{
    stack *new_stack = (stack *)malloc(sizeof(stack));
    list_lib *lib_list = create_list_library();
    new_stack->stack = lib_list->create_list(false);
    free(lib_list);
    return new_stack;
}

stack_lib *create_stack_library()
{
    stack_lib *library = (stack_lib *)malloc(sizeof(stack_lib));
    library->clear = clear;
    library->create_stack = create_stack;
    library->pop_front = pop_front;
    library->push_front = push_front;
    library->top = top;
    return library;
}