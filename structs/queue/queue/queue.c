#include <stdlib.h>
#include "queue.h"

typedef struct queue
{
    list *queue;
} queue;

static void pop_front(queue *obj);
static void clear(queue *obj);
static void push_back(queue *obj, void *data);
static void *top(queue *obj);
static queue *create_queue();

static void pop_front(queue *obj)
{
    list_lib *lib_list = create_list_library();
    lib_list->pop_front(obj->queue);
    free(lib_list);
}

static void clear(queue *obj)
{
    list_lib *lib_list = create_list_library();
    lib_list->clear(obj->queue);
    free(lib_list);
}

static void push_back(queue *obj, void *data)
{
    list_lib *lib_list = create_list_library();
    lib_list->push_back(obj->queue, data);
    free(lib_list);
}

static void *top(queue *obj)
{
    list_lib *lib_list = create_list_library();
    lib_list->get_by_index(obj->queue, 0);
    free(lib_list);
}

static queue *create_queue()
{
    queue *new_queue = (queue *)malloc(sizeof(queue));
    list_lib *lib_list = create_list_library();
    new_queue->queue = lib_list->create_list(false);
    free(lib_list);
}

queue_lib *create_queue_library()
{
    queue_lib *library = (queue_lib *)malloc(sizeof(queue_lib));
    library->clear = clear;
    library->create_queue = create_queue;
    library->pop_front = pop_front;
    library->push_back = push_back;
    library->top = top;
}