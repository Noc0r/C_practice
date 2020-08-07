#ifndef PRIOR_QUEUE
#define PRIOR_QUEUE
#include "../../vector/vector/vector.h"

/**
 * Default binary heap realization based on vector
 * @author Senatrev Ruslan
 * @param queue          pointer to the list
*/

typedef struct prior_queue prior_queue;

typedef struct prior_queue_library
{
    /**
    * Remove first element from the heap
    * @param obj       pointer to the heap
    * @return              
    */
    void (*pop)(prior_queue *obj);

    /**
    * Remove all elements from the heap
    * @param obj       pointer to the heap
    * @return              
    */
    void (*clear)(prior_queue *obj);

    /**
    * Insert new element to the end of the heap
    * @param obj           pointer to the heap
    * @param data          data of new element       
    * @return              
    */
    void (*insert)(prior_queue *obj, void *data);

    /**
     * Get the top element in the heap
     * @param obj      pointer to the heap
    */
    void *(*top)(prior_queue *obj);

    /**
    * Create new empty binary heap
    * @param priority      pointer to the compare objects function
    * @return              pointer to the new heap
    */
    prior_queue *(*create_prior_queue)(int (*priority)(void *, void *));
} prior_queue_lib;

prior_queue_lib *create_queue_library();
#endif /* PRIOR_QUEUE */