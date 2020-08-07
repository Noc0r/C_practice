#include "vector.h"
#include <stdlib.h>
#define RESIZE_OPTIMAL_CONSTANT 0.75
#define RESIZE_SIZE_MULTIPLY 2

typedef struct element
{
    void *data;
} element;

typedef struct vector
{
    element *array;
    unsigned int max_size;
    unsigned int size;
} vector;

static unsigned int count(vector *vect);
static void *get_by_index(vector *vect, unsigned int index);
static void set_by_index(vector *vect, unsigned int index, void *new_data);
static void resize(vector *vect, unsigned int new_size);
static void pop_back(vector *vect);
static void clear(vector *vect);
static void push_back(vector *vect, void *data);
static void insert_element(vector *vect, unsigned int pos, void *data);
static bool remove_element(vector *vect, void *element, int (*compare)(void *, void *));
static bool remove_index(vector *vect, unsigned int pos);
static void swap(vector *vect, unsigned int first, unsigned int second);
static vector *create_vector(unsigned int max_size);
static bool need_resize(unsigned int current_size, unsigned int max_size);
static void update(vector *vect);

static bool need_resize(unsigned int current_size, unsigned int max_size)
{
    if (max_size * RESIZE_OPTIMAL_CONSTANT < current_size)
        return true;
    return false;
}

static void update(vector *vect)
{
    if (need_resize(vect->size, vect->max_size))
        resize(vect, vect->max_size * RESIZE_SIZE_MULTIPLY);
}

static vector *create_vector(unsigned int max_size)
{
    vector *new_vect = (vector *)malloc(sizeof(vector));
    new_vect->max_size = max_size;
    new_vect->size = 0;
    new_vect->array = (element *)malloc(new_vect->max_size * sizeof(element));
    return new_vect;
}

static unsigned int count(vector *vect)
{
    return vect->size;
}

static void *get_by_index(vector *vect, unsigned int index)
{
    if (index < vect->size)
        return (vect->array[index]).data;
    return NULL;
}

static void set_by_index(vector *vect, unsigned int index, void *new_data)
{
    if (index < vect->size)
        (vect->array[index]).data = new_data;
}

static void resize(vector *vect, unsigned int new_size)
{
    if (!need_resize(vect->size, new_size))
    {
        vect->max_size = new_size;
        vect->array = realloc(vect->array, vect->max_size * sizeof(element));
    }
}

static void pop_back(vector *vect)
{
    vect->size--;
}

static void clear(vector *vect)
{
    while (vect->size)
    {
        pop_back(vect);
    }
}

static void push_back(vector *vect, void *data)
{
    vect->array[vect->size].data = data;
    vect->size++;
    update(vect);
}

static void insert_element(vector *vect, unsigned int pos, void *data)
{
    if (pos >= vect->size)
        push_back(vect, data);
    else
    {
        for (size_t i = vect->size; i != pos; i--)
            vect->array[i].data = vect->array[i - 1].data;
        vect->array[pos].data = data;
        update(vect);
    }
}

static bool remove_element(vector *vect, void *element, int (*compare)(void *, void *))
{
    unsigned int pos = 0;
    while (compare(vect->array[pos].data, element) && pos < vect->size)
    {
        pos++;
    }
    return remove_index(vect, pos);
}

static bool remove_index(vector *vect, unsigned int pos)
{
    if (pos < vect->size)
    {
        if (pos == vect->size - 1)
        {
            pop_back(vect);
        }
        else
        {
            for (size_t i = pos; i < vect->size; i++)
                vect->array[i].data = vect->array[i + 1].data;
            vect->size--;
        }
        return true;
    }
    vect->size--;
    return false;
}

static void swap(vector *vect, unsigned int first, unsigned int second)
{
    if (first < vect->size && second < vect->size)
    {
        void *tmp = vect->array[first].data;
        vect->array[first].data = vect->array[second].data;
        vect->array[second].data = tmp;
    }
}

vector_lib *create_vector_library()
{
    vector_lib *library = (vector_lib *)malloc(sizeof(vector_lib));
    library->clear = clear;
    library->count = count;
    library->create_vector = create_vector;
    library->get_by_index = get_by_index;
    library->insert_element = insert_element;
    library->pop_back = pop_back;
    library->push_back = push_back;
    library->remove_element = remove_element;
    library->remove_index = remove_index;
    library->resize = resize;
    library->set_by_index = set_by_index;
    library->swap = swap;
    return library;
}