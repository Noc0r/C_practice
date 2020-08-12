#ifndef QUEUE
#define QUEUE
#include "../../list/list/list.h"
#include <stdlib.h>

/**
 * Default queue implementation based on list
 * @author Senatrev Ruslan
 * @param queue          pointer to the list
*/

typedef struct queue queue;

typedef struct queue_library
{
    /**
    * Remove first element from the queue
    * @param obj       pointer to the queue
    * @return              
    */
    void (*pop_front)(queue *obj);

    /**
    * Remove all elements from the queue
    * @param obj       pointer to the queue
    * @return              
    */
    void (*clear)(queue *obj);

    /**
    * Insert new element to the end of the queue
    * @param obj           pointer to the queue
    * @param data          data of new element       
    * @return              
    */
    void (*push_back)(queue *obj, void *data);

    /**
     * Get the top element in the queue
     * @param obj      pointer to the queue
    */
    void *(*top)(queue *obj);

    /**
    * Create new empty queue
    * @return              pointer to the new queue
    */
    queue *(*create_queue)();
} queue_lib;

queue_lib *create_queue_library();
#endif /* QUEUE */