#include "vector.h"
#define RESIZE_CONSTANT 0.75

typedef struct vector
{
    void *array;
    unsigned int max_size;
    unsigned int size;
    unsigned int element_size;
} vector;

vector *create_vector(unsigned int element_size, unsigned int max_size)
{
    vector *new_vect = (vector *)malloc(sizeof(vector));
    new_vect->max_size = max_size;
    new_vect->size = 0;
    new_vect->element_size = element_size;
    new_vect->array = (void*)malloc(new_vect->max_size * new_vect->element_size);
    return new_vect;
}

