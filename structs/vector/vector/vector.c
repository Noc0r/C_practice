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

bool need_resize(unsigned int current_size, unsigned int max_size)
{
    if (max_size * RESIZE_OPTIMAL_CONSTANT < current_size)
        return true;
    return false;
}

void update(vector *vect)
{
    if (need_resize(vect->size, vect->max_size))
        resize(vect, vect->max_size * RESIZE_SIZE_MULTIPLY);
}

vector *create_vector(unsigned int max_size)
{
    vector *new_vect = (vector *)malloc(sizeof(vector));
    new_vect->max_size = max_size;
    new_vect->size = 0;
    new_vect->array = (element *)malloc(new_vect->max_size * sizeof(element));
    return new_vect;
}

unsigned int count(vector *vect)
{
    return vect->size;
}

void *get_by_index(vector *vect, unsigned int index)
{
    if (index < vect->size)
        return (vect->array[index]).data;
    return NULL;
}

void set_by_index(vector *vect, unsigned int index, void *new_data)
{
    if (index < vect->size)
        (vect->array[index]).data = new_data;
}

void resize(vector *vect, unsigned int new_size)
{
    if (!need_resize(vect->size, new_size))
    {
        vect->max_size = new_size;
        vect->array = realloc(vect->array, vect->max_size * sizeof(element));
    }
}

void pop_back(vector *vect)
{
    vect->size--;
}

void clear(vector *vect)
{
    while (vect->size)
    {
        pop_back(vect);
    }
}

void push_back(vector *vect, void *data)
{
    vect->array[vect->size].data = data;
    vect->size++;
    update(vect);
}

void insert_element(vector *vect, unsigned int pos, void *data)
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

bool remove_element(vector *vect, void *element, int (*compare)(void *, void *))
{
    unsigned int pos = 0;
    while (compare(vect->array[pos].data, element) && pos < vect->size)
    {
        pos++;
    }
    return remove_index(vect, pos);
}

bool remove_index(vector *vect, unsigned int pos)
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