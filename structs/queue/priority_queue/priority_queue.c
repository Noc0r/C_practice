#include "priority_queue.h"
#include <stdlib.h>

typedef struct prior_queue
{
    vector *heap;
    int (*priority)(void *, void *);
} prior_queue;

static void pop(prior_queue *obj);
static void clear(prior_queue *obj);
static void insert(prior_queue *obj, void *data);
static void *top(prior_queue *obj);
static prior_queue *create_prior_queue(int (*priority)(void *, void *));
static void up(prior_queue *obj, unsigned int pos);
static void down(prior_queue *obj, unsigned int pos);
static unsigned int father(unsigned int pos);
static unsigned int left_son(unsigned int pos);
static unsigned int right_son(unsigned int pos);
static int max_prior(void *first, void *second, int (*compare)(void *, void *));

static unsigned int father(unsigned int pos)
{
    if (pos % 2 == 0)
        pos--;
    return pos / 2;
}

static unsigned int left_son(unsigned int pos)
{
    return 2 * pos + 1;
}

static unsigned int right_son(unsigned int pos)
{
    return 2 * pos + 2;
}

static int max_prior(void *first, void *second, int (*compare)(void *, void *))
{
    if (first && second)
    {
        return compare(first, second);
    }
    if (first)
        return 1;
    if (second)
        return -1;
    return 0;
}

static void up(prior_queue *obj, unsigned int pos)
{
    vector_lib *library = create_vector_library();
    unsigned int root = father(pos);
    while (obj->priority(library->get_by_index(obj->heap, pos), library->get_by_index(obj->heap, root)) >= 0)
    {
        library->swap(obj->heap, pos, root);
        pos = root;
        root = father(pos);
    }
    free(library);
}

static void down(prior_queue *obj, unsigned int pos)
{
    vector_lib *library = create_vector_library();
    void *left = library->get_by_index(obj->heap, left_son(pos));
    void *right = library->get_by_index(obj->heap, right_son(pos));
    while (left || right)
    {
        void *cur = library->get_by_index(obj->heap, pos);
        if (max_prior(left, right, obj->priority) >= 0)
        {
            if (max_prior(cur, left, obj->priority) >= 0)
                break;
            library->swap(obj->heap, pos, left_son(pos));
            pos = left_son(pos);
        }
        else
        {
            if (max_prior(cur, right, obj->priority) >= 0)
                break;
            library->swap(obj->heap, pos, right_son(pos));
            pos = right_son(pos);
        }
        left = library->get_by_index(obj->heap, left_son(pos));
        right = library->get_by_index(obj->heap, right_son(pos));
    }

    free(library);
}

static void pop(prior_queue *obj)
{
    vector_lib *library = create_vector_library();
    if (library->count(obj->heap) != 0)
    {
        library->set_by_index(obj->heap, 0, library->get_by_index(obj->heap, library->count(obj->heap) - 1));
        library->pop_back(obj->heap);
        down(obj, 0);
    }
    free(library);
}

static void clear(prior_queue *obj)
{
    vector_lib *library = create_vector_library();
    library->clear(obj->heap);
    free(library);
}

static void insert(prior_queue *obj, void *data)
{
    vector_lib *library = create_vector_library();
    library->push_back(obj->heap, data);
    up(obj, library->count(obj->heap) - 1);
    free(library);
}

static void *top(prior_queue *obj)
{
    vector_lib *library = create_vector_library();
    void *result = library->get_by_index(obj->heap, 0);
    free(library);
    return result;
}

static prior_queue *create_prior_queue(int (*priority)(void *, void *))
{
    vector_lib *library = create_vector_library();
    prior_queue *new_heap = (prior_queue *)malloc(sizeof(prior_queue));
    const unsigned int start_size = 20;
    new_heap->heap = library->create_vector(start_size);
    new_heap->priority = priority;
    free(library);
    return new_heap;
}

prior_queue_lib *create_queue_library()
{
    prior_queue_lib *library = (prior_queue_lib *)malloc(sizeof(prior_queue_lib));
    library->clear = clear;
    library->create_prior_queue = create_prior_queue;
    library->insert = insert;
    library->pop = pop;
    library->top = top;
    return library;
}
