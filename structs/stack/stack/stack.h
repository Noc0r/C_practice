#ifndef STACK
#define STACK
#include "../../list/list/list.h"
#include <stdlib.h>

/**
 * Default stack implementation based on list
 * @author Senatrev Ruslan
 * @param stack          pointer to the list
*/

typedef struct stack stack;

typedef struct stack_library
{
    /**
    * Remove first element from the stack
    * @param obj       pointer to the stack
    * @return              
    */
    void (*pop_front)(stack *obj);

    /**
    * Remove all elements from the stack
    * @param obj       pointer to the stack
    * @return              
    */
    void (*clear)(stack *obj);

    /**
    * Insert new element to the end of the stack
    * @param obj           pointer to the stack
    * @param data          data of new element       
    * @return              
    */
    void (*push_front)(stack *obj, void *data);

    /**
     * Get the top element in the stack
     * @param obj      pointer to the stack
    */
    void *(*top)(stack *obj);

    /**
    * Create new empty stack
    * @return              pointer to the new stack
    */
    stack *(*create_stack)();
} stack_lib;

stack_lib *create_stack_library();
#endif /* STACK */